/*
  Write a program for ubuntu and compile it in GNU Compiler which creates 3 child processes from a parent process using fork(). Each child process should:
  •	Print its process ID (PID) and parent process ID (PPID)
  •	Execute a simple calculation (e.g., factorial of a small number)
  •	Print your Student ID and Student Name in a line
  •	Print the result of factorial before exiting
  The parent process should wait for all children to complete and print a summary message.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int factorial(int n) {
  if (n < 1) return 1;
  return n * factorial(n - 1);
}

int main() {
  pid_t pid;
  int max_child = 3;
  int num[] = {3, 4, 5};

  for(int i=0; i<max_child; i++) {
    pid = fork();
    
    if(pid < 0) {
      perror("Fork Failed");
      exit(1); // program terminate unsuccessfully
    }

    // Child Processes
    if(pid == 0) {
      int fac = factorial(num[i]);

      printf("Child PID: %d\n", getpid());
      printf("Parent PID: %d\n", getppid());
      printf("BC220406016 - Muhammad Ismail\n");
      printf("Factorial of %d is %d\n\n", num[i], fac);
      exit(0);
    }
  }
    
  // Parent Process
  for(int i=0; i<max_child; i++) {
    wait(NULL);
  }

  printf("PARENT: All Child Processes are completed\n");

  return 0;
}