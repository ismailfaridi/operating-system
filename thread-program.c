/**********************************************************************
 *   A "hello world" Pthreads program which demonstrates another safe way
 *   to pass arguments to threads during thread creation.  In this case,
 *   a structure is used to pass multiple arguments.
 **********************************************************************/

#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 8

char *messages[NUM_THREADS]; // array of strings to store different messages in different languages.

struct thread_data
{
    int thread_id;
    int sum;
    char *message;
};

struct thread_data thread_data_array[NUM_THREADS]; // hold data for each thread.

void *PrintHello(void *threadarg)
{
    int taskid, sum;
    char *hello_msg;
    struct thread_data *my_data;

    sleep(1); // pause for 1 second.
    my_data = (struct thread_data *)threadarg;
    taskid = my_data->thread_id;
    sum = my_data->sum;
    hello_msg = my_data->message;

    printf("Thread %d: %s  Sum=%d\n", taskid, hello_msg, sum);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS]; // hold the thread IDs
    int *taskids[NUM_THREADS];
    int rc, t, sum;
    sum = 0;

    messages[0] = "English: Hello World!";
    messages[1] = "French: Bonjour, le monde!";
    messages[2] = "Spanish: Hola al mundo";
    messages[3] = "Klingon: Nuq neH!";
    messages[4] = "German: Guten Tag, Welt!";
    messages[5] = "Russian: Zdravstvytye, mir!";
    messages[6] = "Japan: Sekai e konnichiwa!";
    messages[7] = "Latin: Orbis, te saluto!";

    for (t = 0; t < NUM_THREADS; t++)
    {
        sum = sum + t;
        thread_data_array[t].thread_id = t;
        thread_data_array[t].sum = sum;
        thread_data_array[t].message = messages[t];

        printf("Creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)&thread_data_array[t]);

        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    
    pthread_exit(NULL);
}