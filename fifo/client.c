#include <stdio.h>	// perror(), BUFSIZ
#include <stdlib.h>	// exit()
#include <string.h>	// strlen()
#include <fcntl.h>	// open()
#include <unistd.h>	// read(), write(), close(), unlink()

#define FIFO1	  "/tmp/fifo.1"
#define FIFO2	  "/tmp/fifo.2"
#define MESSAGE1  "Hello, world!\n"

int main() {
  char buff[BUFSIZ];
  int readfd, writefd, n_bytes, size;
  
  // OPEN FIFO's
  if( (writefd = open(FIFO1, 1/*O_WRONLY*/)) < 0 ) {
    perror("client open FIFO1");
    exit(1);
  }

  if( (readfd = open(FIFO2, 0/*O_RDONLY*/)) < 0 ) {
    perror("client open FIFO2");
    exit(1);
  }
  
  // CLIENT WRITE MSG1 TO FIFO1 & READ MSG1 FROM FIFO2 AND PRINT IN STDOUT
  size = strlen(MESSAGE1) + 1;
  
  if( write(writefd, MESSAGE1, size) != size ) { // Handle partial writes and errors.
    perror("client write1");
    exit(1);
  }

  if( (n_bytes = read(readfd, buff, size)) < 0 ) { // If read succeeds, it goes to else block.
    perror("client read");
    exit(1);
  }
  else {
    if( write(1/*STDOUT*/, buff, n_bytes) != n_bytes ) {
      perror("client write2");
      exit(1);
    }
  }
  
  close(readfd);
  close(writefd);
  
  // REMOVE FIFOs
  if(unlink(FIFO1) < 0) {
    perror("client unlink FIFO1");
    exit(1);
  }

  if(unlink(FIFO2) < 0) {
    perror("client unlink FIFO2");
    exit(1);
  }
  
  return 0;
}
