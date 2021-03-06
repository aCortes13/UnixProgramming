/*
* Name: Edward Cortes
* Assign: 4
* due: 4/10/2019
* Serial: 12
* Instructor: Husain Gholoom
*/

#include <stdio.h>
#include <stdlib.h>

const char FILENAME[] = "lottofile.txt";

// this struct will be used to hold the value and it's frequency
struct Nums {
  int num;
  int freq;
};

// this struct will be used to count the frequency of lotto numbers for each year
struct Years {
  int year;
  struct Nums num[54];
};

// compare function for qsort -- implemented in descending order
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

// opening message
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

// initialized the num struct array 
void initNumStruct(struct Nums arr[]) {
  for (int i = 0; i < 54; i++) {
    arr[i].num = i + 1;
    arr[i].freq = 0;
  }
}

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
  printf("This program written by Anthony Cortes\n\n");
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
  
  // read in each line of the file and store to the correct array
  char line[256];
  while (fscanf(fp, "%d %d %d %d %d %d %d", &year, &num1, &num2, &num3, &num4, &num5, &num6) != EOF) {
    int yearAccess = year - 1992;

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
  }

  // begin output 
  printf("For each year, the frequency of drawn numbers in the Texas Lotto are as follows [1 - 27] :- \n\n");
  printf("Year -> No");
  for (int i = 1; i < 16; i++) { printf("%3d ", i); }
  printf("\n\n");

  for (int i = 0; i < sizeof(yearCount)/sizeof(yearCount[0]); i++) {
    printf("%d      ", yearCount[i].year);
    for (int j = 0; j < 15; j++) {
      printf("%*d ", 3, yearCount[i].num[j].freq);
    }
    printf("\n\n");
  }

  printf("\nOver All The Data , The Frequency of drawn numbers in the Texas Lotto are [1 - 27] :-\n");
  printf("%-13s ->", "No");
  for (int i = 1; i < 16; i++) { printf("%4d ", i); }
  printf("\n");

  // for correct formatting
  printf("|\n");
  printf("%-13s ->", "Frequency");


  for (int j = 0; j < 15; j++) {
    printf("%4d ", numCount[j].freq);
  }
  printf("\n\n");

  // sort array by largest frequency
  qsort(numCount, 54, sizeof(struct Nums), cmpfunc); 

  printf("The MOST frequent Numbers Drawn in the Texas LOTTO Game from Highest to Lowest [1 - 27] :-\n");
  printf("%-13s ->", "The Number");
  for (int i = 0; i < 15; i++) { printf("%4d ", numCount[i].num); }
  printf("\n");

  // for correct formatting
  printf("|\n");
  printf("%-13s ->", "Was Drawn");

  for (int j = 0; j < 15; j++) {
    printf("%4d ", numCount[j].freq);
  }
  printf("\n\n");

  printf("Total integers read: %d\n", totalInts);
  fclose(fp);
  return 0;  
}
