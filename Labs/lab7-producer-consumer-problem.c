/*
# Producer consumer problem for Process synchronization
- Write a C program to implement Producer consumer problem for process synchronization.  A producer process produces information that is consumed by a consumer process. You have to implement the producer-consumer problem by using shared memory like buffer that is shared by the producer and consumer processes. A producer can produce one item while the consumer is consuming another item. The producer and consumer must be synchronized, so that the consumer does not try to consume an item that has not yet been produced. 
- In a program, the user will take size of buffer from user and then producer process will produce items in buffer and consumer process will consume items from buffer and display its values on screen.
*/

#include <stdio.h>

int main()
{
    int bufsize, in, out, produce = 0, consume = 0, counter = 0;
    in = 0; out = 0;

    printf("Please enter the size of buffer: ");
    scanf("%d", &bufsize);

    int buffer[bufsize];

    char choice;

    printf("Enter 'p' to produce an item in buffer.\n");
    printf("Enter 'c' to consume an item from buffer.\n");
    printf("Enter 'q' to Quit.\n");
    printf("Enter your choice: ");

    do
    {
        scanf("%c", &choice);

        switch(choice)
        {
            // producer
            case 'p':
                if (counter == bufsize)
                    printf("Buffer is Full\n");
                else
                {
                    printf("Enter the value: ");
                    scanf("%d", &produce);
                    buffer[in] = produce;
                    in = (in + 1) % bufsize;
                    counter++;
                }
                break;

            // consumer
            case 'c':
                if (counter == 0)
                    printf("Buffer is Empty\n");
                else
                {
                    consume = buffer[out];
                    printf("The consumed value is %d\n", consume);
                    out = (out + 1) % bufsize;
                    counter--;
                }
                break;
            }
    } while (choice != 'q');
}