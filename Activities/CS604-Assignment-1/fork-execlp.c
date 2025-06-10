/*
  Write a C/C++ program where:
  •	The parent process creates two child processes using fork().
  •	Each child process prints its PID and PPID.
  •	Each child calls exit(0) after printing a message.
  •	The parent process uses wait() to wait for both children.
  •	Print a confirmation from the parent after both children terminate.

  Now Modify the above program so that:
  •	One of the children (e.g., the first one) uses execlp() to execute the ls command.
  •	Handle failure of execlp() using appropriate error messages.
  •	Remove wait() from the parent process and use a sleep delay to inspect zombie behavior using commands like ps.
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
    
    // Execute 'ls' Command
    if( execlp("/bin/ls", "ls", NULL) < 0 ) {
      perror("execlp failed");
      exit(1);
    }
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
  printf("Parent Process: Sleeping to observe zombie behavior... (ps aux | grep 'Z')\n");
  sleep(10); // 10 seconds
  printf("Parent Process: Well done Childrens\n");
  
  return 0;
}