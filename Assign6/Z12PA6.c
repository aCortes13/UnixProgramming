/* 
 *  Name: Anthony Cortes CS 4350 – Unix Systems Programming
 *  Serial Number: 12
 *  Assignment number: 6
 *  Due Date: 5/1/2019
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

int sumArr = 0;
int randints[50];

void swap(int *xp, int *yp) { 
  int temp = *xp; 
  *xp = *yp; 
  *yp = temp; 
}

void bubblesort(int n, int* arr) {
  int i, j; 
  for (i = 0; i < n-1; i++) { 
    for (j = 0; j < n-i-1; j++) {
      if ( *(arr + j) > *(arr + (j+1)) )
        swap( (arr + j), (arr + (j+1)) );
    }
  }
}

void randomintgenerator(int num, int arr[]) {
  int i = 0;
  for (; i < num; i++) 
    arr[i] = 1 + (rand() % 2500);
}

void *sum(void *vargp) {
  int *limit = vargp;
  int i;
  for (i = *limit; i < *limit + 25; i++) 
    __sync_fetch_and_add(&sumArr, randints[i]);
}

int main(int argc, char *argv[]) {

  if (argc != 4) {
    printf("Usage: %s <int> <int> <int>\n", argv[0]);
    exit(-1);
  }

  printf("Welcome to Anthony Cortes' Program\n\n");
  printf("This program will do the following:\n\n");
  printf("\u2022 Opens two pipes, one to the ls command and the other to sort. Displays the output on the screen.\n");
  printf("\u2022 Takes the three positive integers m, n and r from its commend line arguments,\n");
  printf("    using fork, create three child processes, wait for them to complete, and exit.\n");
  printf("    The first process sorts m random integers using the bubble sort,\n");
  printf("    the second computes the factorial of n, and the third process\n");
  printf("    computes hailstone sequence.\n");
  printf("\u2022 Using threads, parallelize a sequential program to compute the sum of an array of size 50 of integers from 1 to 2500.\n\n");
  
  /*** perform ls | sort ***/
  printf("1- Performing ls | sort\n");
  int pipe1[2];
  int pid, i;

  if (pipe(pipe1) < 0) {
    perror("ERROR creating a pipe\n"); 
    exit(-1);
  }
  if (argv[1] < 0 || argv[2] < 0 || argv[3] < 0) {
    printf("Command line arguments must be positive integers. \n");
  }

  /* begin forks for ls | sort */
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(-1);
  }
  
  if (pid == 0) {
    dup2(pipe1[1], STDOUT_FILENO); // redirect stdout to write end of pipe
    close(pipe1[1]); //close write end
    close(pipe1[0]); // close read end
    execlp("ls", "ls", NULL); // run ls

    /* only reach here if execlp fails */
    perror("execlp ls");
    exit(-1);

  }
  else {
    pid = fork();
    
    if (pid == 0) {
      dup2(pipe1[0], STDIN_FILENO); // redirect stdin to read end of pipe
      close(pipe1[1]); // close write end
      close(pipe1[0]); // close read end
      execlp("sort", "sort", NULL); // run sort

      /* only reach here if execlp fails */
      perror("execlp sort");
      exit(-1);
    }
    else {
      int status;
      close(pipe1[0]); // close read end
      close(pipe1[1]); // close write end
      waitpid(pid, &status, 0); // wait for children 
    }
  }
  /* end ls | sort */

  /*** command line argument computations ***/
  int bubbleNum = atoi(argv[1]);
  int factorialNum = atoi(argv[2]);
  int hailstoneNum = atoi(argv[3]);
  int* bubbleArray;

  printf("\n2- Bubble Sort Process Started\n");    
  pid = fork();

  if (pid == 0) {
    printf("Input number: %d\n", bubbleNum); 
    printf("%d generated random numbers:\n", bubbleNum);
    
    // allocate memory for bubble sort
    bubbleArray = calloc(bubbleNum, sizeof(int));
    
    // generate rand nums
    for (i = 0; i < bubbleNum; i++) {
      *(bubbleArray + i) = rand() % 2500;
      printf("%d ", *(bubbleArray + i));
    }
    printf("\n");
    // sort
    bubblesort(bubbleNum, bubbleArray);
    
    printf("Sorted sequence:\n");
    for (i = 0; i < bubbleNum; i++)
      printf("%d ", *(bubbleArray + i));
    printf("\n");
    
    // free allocated memory
    free(bubbleArray);
    printf("Bubble sort process exits\n\n");
    exit(0);
  }
  else {
      int status;
      waitpid(pid, &status, 0); // wait for children 
  } 
 
  printf("Factorial Process Started\n");

  pid = fork();
  if (pid == 0) {
    unsigned long long factorial = 1;
    for (i = 1; i <= factorialNum; i++)
      factorial *= i;
    printf("Factorial number f(%d) is %llu\n",factorialNum, factorial);
    printf("Factorial Process Exits\n\n");
    exit(0);
  }
  else {
    int status;
    waitpid(pid, &status, 0);
  }
  

  printf("Hailstone Process Started\n");

  pid = fork();
  if (pid == 0) {
    printf("Input Number: %d\n", hailstoneNum);
    printf("Hailstone sequence of %d is : ", hailstoneNum);
    int n = hailstoneNum;
    while (n != 1) {
      printf("%d, ", n);
      n = n % 2 ? 3 * n + 1 : n / 2;
    }
    printf("%d\n", n);
    printf("Hailstone Process Exits\n\n");
    exit(0);
  }
  else {
    int status;
    waitpid(pid, &status, 0);
  }

  /*** compute sum of 50 random ints ***/ 
  pthread_t tid[2]; 
  int threadArgs[2];

  // generate 50 random numbers
  srand(time(0)); 
  printf("3- Performing int[50] sum using two threads...\n");
  randomintgenerator(50, randints);
 
  // launch threads to compute sum
  for (i = 0; i < 2; i++) {
    threadArgs[i] = i * 25;
    pthread_create(&tid[i], NULL, sum, (void *) &threadArgs[i]);
  }

  // wait
  for (i = 0; i < 2; i++)
    pthread_join(tid[0], NULL); 

  printf("The total sum is %d\n", sumArr);
  printf("\nProgram by Anthony Cortes\n");
  return 0;
}
