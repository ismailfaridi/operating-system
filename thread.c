#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_func(void *arg) {
  printf("Hello from threadFunc.\n");
  return NULL;
  // pthread_exit(NULL);
}

int main() {
  pthread_t thread_id;
  
  // Create new thread.
  if(pthread_create(&thread_id, NULL, thread_func, NULL) != 0) {
    printf("Failed to create thread.\n");
    return 1;
  }

  // 'main' thread wait for this thread 'thread_id' to finish.
  if(pthread_join(thread_id, NULL) != 0 ) {
    printf("Failed to join thread.\n");
    return 1;
  }

  printf("Main thread existing.\n");

  return 0;
}
