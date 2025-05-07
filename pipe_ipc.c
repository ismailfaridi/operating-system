/*
  Author:   Muhammad Ismail
  Website:  https://ismailfaridi.com
  Linkedin: https://www.linkedin.com/in/ismailfaridi/

 * PIPE
 * - A pipe is a mechanism used for Inter-Process Communication (IPC) between related processes, typically between a parent and its child process.
 * - Pipes are unidirectional, meaning they allow one-way communication only - data flows in a single direction.
 * - Pipe is a bounded buffer with atomic writes up to PIPE_BUF (4096 bytes) in linux, defined in <linux/limits.h> or <linux/param.h>.
 * - `int pipe(int fd[2]);` syscall creates a pipe fills fd[0] (read end) and fd[1] (write end).

 * Program: Parent creates pipe & fork a child. Child writes into the pipe, and parent reads from the pipe.
 
 * Variable	Meaning
 * ------------------------------------------------------
 * pipefd[2] 	hold two file descriptor return by pipe()
 * rc 		hold return value of pipe()
 * nr 		hold number of bytes read from pipe
 * buf[1024] 	store data read from pipe
 * status	store child exit status

 * Read(), Write(), Close() System Calls
 * - ssize_t read(int fd, void *buf, size_t count);        // Read up to count bytes from file descriptor fd into the buffer starting at buf. On success, read() returns the number of bytes read.
 * - ssize_t write(int fd, const void *buf, size_t count); // Write up to count bytes to the file referenced by the file descriptor fd from the buffer starting at buf. On success, write() returns the number of bytes written.
 * - int close(int fd);                                    // Closes  a  file  descriptor,  so  that it no longer refers to any file and may be reused.
*/

#include <stdio.h>	// perror()
#include <stdlib.h>	// exit()
#include <unistd.h>	// pipe(), fork(), read(), write(), close()
#include <sys/wait.h>	// wait()
#include <string.h>	// strlen()

int main() {
  int pipefd[2], pid, n, rc, nr, status;
  char  *testString = "Hello World!\n", buf[1024];

  rc = pipe(pipefd);

  if(rc < 0) {
    perror("pipe");
    exit(1);
  }

  pid = fork();

  if(pid < 0) {
    perror("fork");
    exit(1);
  }

  // Child Code: Write into pipe
  if(pid == 0) {
    close(pipefd[0]); 					// Close unused read end of pipe.
    write(pipefd[1], testString, strlen(testString));	// Write strlen(testString) of bytes to pipefd[1] from the testString.
    close(pipefd[1]); 					// Close write end of pipe.
    exit(0);
  }

  // Parent Code: Read from pipe
  close(pipefd[1]);					// Close unused write end of pipe.
  nr = read(pipefd[0], buf, strlen(testString)); 	// Read strlen(testString) of bytes from pipefd[0] into buf. read() return number of bytes read.
  rc = write(1, buf, nr); 				// Write nr of bytes into stdout from buf.
  wait(&status);
  printf("Good work child!\n");

  return 0;
}
