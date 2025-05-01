/*
 * Program: Server creates FIFO1 (read) and FIFO2(write). Client writes to FIFO1, read from FIFO2.
            Server reads client msg, replies via FIFO2. Both display messages, then terminate.
*/

#include <stdio.h>	// perror(), BUFSIZ
#include <stdlib.h>	// exit()
#include <string.h>	// strlen()
#include <sys/errno.h>	// errno, EEXIST
#include <unistd.h>	// unlink()
#include <fcntl.h>	// open()
#include <sys/stat.h>	// mknod(), mkfifo()

extern int	errno;  // errno is global variable defined somewhere else.

#define FIFO1	  "/tmp/fifo.1"
#define FIFO2	  "/tmp/fifo.2"
#define PERMS	  0666
#define MESSAGE1  "Hello, world!\n"
#define MESSAGE2  "Hello, class!\n"

int main() {
  char buff[BUFSIZ];
  int readfd, writefd, n_bytes, size;
  
  // CRETAE FIFO's
  if( (mknod(FIFO1, S_IFIFO | PERMS, 0) < 0) && (errno != EEXIST) ) { // Handles errors other than 'file already exists'.
    perror("mknod FIFO1");
    exit(1);
  }

  if( (mkfifo(FIFO2, PERMS) < 0) && (errno != EEXIST) ) { // mknode() can also be used.
    unlink(FIFO1); 		 		  	  // Delete the FIFO1.
    perror("mknod FIFO2");
    exit(1);
  }

  // OPEN FIFO's for READING & WRITING
  if( (readfd = open(FIFO1, 0/*O_RDONLY*/)) < 0 ) {
    perror("open FIFO1");
    exit(1);
  }
  
  if( (writefd = open(FIFO2, 1/*O_WRONLY*/)) < 0) {
    perror("open FIFO2");
    exit(1);
  }
  
  // SERVER READ MSG1 FROM FIFO1 AND DISPLAY ON STDOUT, also WRITE MSG2 TO FIFO2
  size = strlen(MESSAGE1) + 1;

  if( (n_bytes = read(readfd, buff, size)) < 0 ) {
    perror("server read");
    exit(1);
  }

  if( write(1 /*stdout fd*/, buff, n_bytes) < n_bytes ) { // Handel partial writes and errors.
    perror("server write1");
    exit(1);
  }
  
  size = strlen(MESSAGE2) + 1;

  if( write(writefd, MESSAGE2, size) != size ) { // Handel partial writes and errors.
    perror("server write2");
    exit(1);
  }
  
  close(readfd);
  close(writefd);
  
  return 0;
}
