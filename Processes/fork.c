/*
  Author:   Muhammad Ismail
  Website:  https://ismailfaridi.com
  Linkedin: https://www.linkedin.com/in/ismailfaridi/
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include <unistd.h>
void my_fork() {
  pid_t pid;
  // int pid;

  pid = fork();
  // pid = fork(); // Parent, Parent, Child, Child

  if(pid == -1) {
    printf("Fork Failed\n");
    exit(1); // program terminated unsuccessfully
  }

  if(pid == 0) {
    printf("Child\n");
    printf("=> Child PID: %d\n", getpid());
    printf("=> Child Parent PID: %d\n", getppid());
    exit(0); // program terminated successfully
  }
  else {
    printf("Parent\n");
    printf("-> Parent PID: %d\n", getpid());
    printf("-> Child PID: %d\n", pid);
    exit(0);
  }
}

#include <sys/wait.h>
void fork_wait() {
  int pid, status;

  pid = fork();

  if(pid == -1) {
    printf("Fork Failed\n");
    exit(1);
  }

  if(pid == 0) {
    printf("Child\n");
    exit(0);
  }
  else {
    wait(&status); // store child process exit information.
    printf("Parent\n");
    exit(0);
  }
}

// #include <unistd.h>
void my_execlp() {
  int pid, status;

  pid = fork();

  if(pid == -1) {
    printf("Fork Failed\n");
    exit(1);
  }

  if(pid == 0) {
    printf("Before execlp\n");
    
    // Replace child process memory space with ls program.
    if(execlp("/bin/ls", "ls", NULL) < 0) {
      printf("execlp failed");
      exit(1);
    }
    
    printf("After execlp\n"); // not executed
  }
  else {
    wait(&status);
    printf("Parent\n");
    exit(0);
  }
}

int main() {
  // my_fork();   // Parent, Child
  // fork_wait(); // Child, Parent
  // my_execlp(); // Before execlp, <ls execute>, Parent

  return 0;
}