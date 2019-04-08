/*
* Name: Edward Cortes
* Assign: 4
* due: 4/10/2019
* Serial: 12
* Instructor: Husain Gholoom
*/

#include <stdio.h>
#include <stdlib.h>

struct Nums {
  int num;
  int freq;
};

struct Years {
  int year;
  struct Nums num[54];
};

int cmpfunc (const void *a, const void *b) {
  const struct Nums *numa = a;
  const struct Nums *numb = b;

  if (numa->freq > numb->freq) 
    return -1;
  else if (numa->freq < numb->freq) 
    return 1;
  else
    return 0;
}
void menuMessage() {
  printf("The function of this program is to find the frequency\nof each number that has been drawn in the Texas lotto game.\nThe program\n");
  printf("  1. Calculates and displays the frequency of drawn numbers\n");
  printf("     in Texas Lotto in each year.\n");
  printf("  2. Calculates and displays the overall frequency of each\n"); 
  printf("      number that has been drawn since the lotto started.\n");
  printf("  3. Sorts the frequency numbers in Descending order. Display\n");
  printf("      the sorted list\n");
  printf("  4. Displays total number of integers in the entire file.\n\n");
}

void initNumStruct(struct Nums arr[]) {
  for (int i = 0; i < 54; i++) {
    arr[i].num = i + 1;
    arr[i].freq = 0;
  }
}

const char FILENAME[] = "lottofile.txt";

int main() {
  // pointer for the file 
  FILE *fp;
  fp = fopen(FILENAME, "r");
  
  // check file
  if (fp == NULL) {
    printf("[ERROR] Could not open file.");
    return -1;
  }
  
  // file exists, we can continue 
  menuMessage();
  
  // variables to store the input data 
  int year;
  int num1;
  int num2;
  int num3;
  int num4;
  int num5;
  int num6;
  int totalInts = 0;

  struct Nums numCount[54]; 
  struct Years yearCount[28];
    
  // initialize numCount 
  initNumStruct(numCount);

  // initialize nums in YearCount
  for (int i = 0; i < sizeof(yearCount)/sizeof(yearCount[0]); i++) {
    yearCount[i].year = 1992 + i;
    initNumStruct(yearCount[i].num);
  }

  char line[256];
  while (fscanf(fp, "%d %d %d %d %d %d %d", &year, &num1, &num2, &num3, &num4, &num5, &num6) != EOF) {
    int yearAccess = year - 1992;
    totalInts++;

    if (numCount[num1 - 1].num == num1) {
      numCount[num1 -1].freq += 1;
      yearCount[yearAccess].num[num1-1].freq += 1;
      totalInts++;
    }
    if (numCount[num2 - 1].num == num2) {
      numCount[num2 -1].freq += 1;
      yearCount[yearAccess].num[num2-1].freq += 1;
      totalInts++;
    }
    if (numCount[num3 - 1].num == num3) {
      numCount[num3 -1].freq += 1;
      yearCount[yearAccess].num[num3-1].freq += 1;
      totalInts++;
    }
    if (numCount[num4 - 1].num == num4) {
      numCount[num4 -1].freq += 1;
      yearCount[yearAccess].num[num4-1].freq += 1;
      totalInts++;
    }
    if (numCount[num5 - 1].num == num5) {
      numCount[num5 -1].freq += 1;
      yearCount[yearAccess].num[num5-1].freq += 1;
      totalInts++;
    }
    if (numCount[num6 - 1].num == num6) {
      numCount[num6 -1].freq += 1;
      yearCount[yearAccess].num[num6-1].freq += 1;
      totalInts++;
    }
    //printf("%s", line);
  }

  printf("For each year, the frequency of drawn numbers in the Texas Lotto are as follows [1 - 27] :- \n\n");
  printf("Year -> No");
  for (int i = 1; i < 28; i++) { printf("%3d ", i); }
  printf("\n");


  for (int i = 0; i < sizeof(yearCount)/sizeof(yearCount[0]); i++) {
    year = yearCount[i].year;
    printf("%d      ", year);
    for (int j = 0; j < 27; j++) {
      printf("%*d ", 3, yearCount[i].num[j].freq);
    }
    printf("\n\n");
  }

  printf("For each year, the frequency of drawn numbers in the Texas Lotto are as follows [28 - 54] :- \n");
  printf("Year -> No");
  for (int i = 28; i < 55; i++) { printf("%3d ", i); }
  printf("\n");

  for (int i = 0; i < sizeof(yearCount)/sizeof(yearCount[0]); i++) {
    year = yearCount[i].year;
    printf("%d      ", year);
    for (int j = 27; j < 54; j++) {
      printf("%*d ", 3, yearCount[i].num[j].freq);
    }
    printf("\n\n");
  }

  printf("Over All The Data , The Frequency of drawn numbers in the Texas Lotto are [1 - 27] :-\n");
  printf("Freq. -> No");
  for (int i = 1; i < 28; i++) { printf("%4d ", i); }
  printf("\n");

  // for correct formatting
  printf("           ");

  for (int j = 0; j < 27; j++) {
    printf("%4d ", numCount[j].freq);
  }
  printf("\n\n");

  printf("Over All The Data , The Frequency of drawn numbers in the Texas Lotto are [28 - 54] :-\n");
  printf("Freq. -> No");
  for (int i = 28; i < 55; i++) { printf("%4d ", i); }
  printf("\n");

  // for correct formatting
  printf("           ");

  for (int j = 27; j < 54; j++) {
    printf("%4d ", numCount[j].freq);
  }
  printf("\n\n");

  qsort(numCount, 54, sizeof(struct Nums), cmpfunc); 

  printf("The MOST frequent Numbers Drawn in the Texas LOTTO Game from Highest to Lowest [1 - 27] :-\n");
  printf("Freq. -> No");
  for (int i = 1; i < 28; i++) { printf("%4d ", i); }
  printf("\n");

  // for correct formatting
  printf("           ");

  for (int j = 0; j < 27; j++) {
    printf("%4d ", numCount[j].freq);
  }
  printf("\n\n");

  printf("The MOST frequent Numbers Drawn in the Texas LOTTO Game from Highest to Lowest [28 - 54] :-\n");
  printf("Freq. -> No");
  for (int i = 28; i < 55; i++) { printf("%4d ", i); }
  printf("\n");

  // for correct formatting
  printf("           ");

  for (int j = 27; j < 54; j++) {
    printf("%4d ", numCount[j].freq);
  }
  printf("\n\n");

  fclose(fp);
  return 0;  
}
