/*
  Write a C/C++ program where:
  •	The parent process creates two child processes using fork().
  •	Each child process prints its PID and PPID.
  •	Each child calls exit(0) after printing a message.
  •	The parent process uses wait() to wait for both children.
  •	Print a confirmation from the parent after both children terminate.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  pid_t pid1, pid2;
  
  // First Child Process
  pid1 = fork();
  
  if(pid1 < 0) {
    perror("Fork Failed");
    exit(1);
  }
  else if(pid1 == 0) {
    printf("Child Process 1: PID = %d, PPID = %d\n", getpid(), getppid());
    exit(0);
  }
  
  // Second Child Process
  pid2 = fork();
  
  if(pid2 < 0) {
    perror("Fork Failed");
    exit(1);
  }
  else if(pid2 == 0) {
    printf("Child Process 2: PID = %d, PPID = %d\n", getpid(), getppid());
    exit(0);
  }

  // Parent Process
  for(int i=0; i<2; i++) {
    wait(NULL);
  }
  
  printf("Parent Process: Well done Childrens\n");
  
  return 0;
}