#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // pthread_create(), pthread_join(), pthread_exit()
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 50 // max limit of name input

// Thread 1: Reads integers from input.txt, calculates sum, writes to output.txt & console
void *thread1_func(void *arg)
{
    FILE *inFile = fopen("input.txt", "r");

    if (inFile == NULL)
    {
        perror("Error while opening input.txt file.");
        pthread_exit(NULL);
    }

    int sum = 0, num;

    // Read 5 integers from file
    for (int i = 0; i < 5; i++)
    {
        if (fscanf(inFile, "%d", &num) != 1)
        {
            printf("Error while reading integer from input.txt file.\n");
            fclose(inFile);
            pthread_exit(NULL);
        }

        sum += num;
    }

    fclose(inFile);

    // Print sum to console
    printf("T1: Sum of numbers: %d\n", sum);

    // Write sum to output.txt
    FILE *outFile = fopen("output.txt", "w");

    if (outFile == NULL)
    {
        perror("Error while opening output.txt file.");
        pthread_exit(NULL);
    }

    fprintf(outFile, "Sum of numbers: %d\n", sum);
    fclose(outFile);

    pthread_exit(NULL);
}

// Thread 2: Takes user name input, replaces vowels, prints and appends to output.txt
void *thread2_func(void *arg)
{
    char input[MAX_LENGTH];

    printf("T2: Enter a string: ");
    fgets(input, MAX_LENGTH, stdin);

    // Remove newline character if present
    input[strcspn(input, "\n")] = '\0';

    // Replace vowels with '*'
    for (int i = 0; input[i]; i++)
    {
        if (strchr("aeiouAEIOU", input[i]))
        {
            input[i] = '*';
        }
    }

    // Print modified name
    printf("T2: Modified string: %s\n", input);

    // Append modified string to output.txt
    FILE *outFile = fopen("output.txt", "a");

    if (outFile == NULL)
    {
        perror("Error while opening output.txt file.");
        pthread_exit(NULL);
    }

    fprintf(outFile, "Modified string: %s\n", input);
    fclose(outFile);

    pthread_exit(NULL);
}

int main()
{
    pthread_t t1, t2;

    // Check if input.txt exists, create if it doesn't
    FILE *inFile = fopen("input.txt", "r");

    if (inFile == NULL)
    {
        inFile = fopen("input.txt", "w");

        if (inFile != NULL)
        {
            // Write 5 integers to file
            fprintf(inFile, "10\n20\n30\n40\n50\n");
            // printf("Created input.txt with default values.\n");
            fclose(inFile);
        }
        else
        {
            perror("Unable to create the input.txt file.");
            return 1;
        }
    }
    else
    {
        fclose(inFile);
    }

    // Create and run Thread 1
    pthread_create(&t1, NULL, thread1_func, NULL);
    pthread_join(t1, NULL); // Wait for Thread 1 to finish

    // Create and run Thread 2
    pthread_create(&t2, NULL, thread2_func, NULL);
    pthread_join(t2, NULL); // Wait for Thread 2 to finish

    return 0;
}
