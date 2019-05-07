/*
    Name: Anthony Cortes
    Serial Number: 12
    Assign Num: 5
    Due: 4/24/2019
*/

#include <stdio.h>

int main () {
  printf("Directory and File Manipulation\n\n");
  printf("The content of the current Directory:-\n");

  // display content of current directory
  system("ls");

  // Verify if Zold.c exists
  FILE *ptr = fopen("Zold.c", "r");
  if (!ptr) {
    printf("\n[ERROR] File \'Zold.c\' does not exist\n");
    return -1;
  }
  fclose(ptr);

  // copy Zold.c to Znew.txt
  system("cp Zold.c Znew.txt");
  printf("\n\"Znew.txt\" is created:\n\n");

  // display content of Znew.txt
  printf("The content of Znew.txt\n");
  system("cat Znew.txt");
  printf("\n");
  
  // Display size of Znew.txt
  system("ls -l Znew.txt | awk '{print \"The size of Znew.txt(in bytes): \" $5}'");
  printf("\n");

  // Count and Dispaly number of words in Znew.txt
  system("wc Znew.txt | awk '{print \"Number of words in Znew.txt: \" $2}'");
  printf("\n");

  // count and display number of characters in Znew.txt
  system("wc -m Znew.txt | awk '{print \"Number of characters in Znew.txt: \" $1}'");
  printf("\n");
  
  // count and display number of lines 
  system("wc Znew.txt | awk '{print \"Number of lines in Znew.txt: \" $1}'");
  printf("\n");
  
  // count and display number of lines ending with ; in Znew.txt
  system("cat Znew.txt | grep \";\" | wc | awk '{print \"Number of lines ending with ; Znew.txt: \" $1}'");
  printf("\n");
  
  // delete Znew.txt
  system("rm Znew.txt");
  printf("Znew.txt file deleted successfully\n\n");
  printf("Implemented by Anthony Cortes\n\n4 - 24 - 2019\n");
  return 0;
}
