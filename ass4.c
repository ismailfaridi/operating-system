#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

// Thread 1: Reads integers from input.txt, calculates sum, writes to output.txt & console
void *thread1_function(void *arg)
{
    FILE *inFile = fopen("input.txt", "r");
    if (inFile == NULL)
    {
        perror("Error opening input.txt");
        pthread_exit(NULL);
    }
    int sum = 0, number;

    // Read 5 integers from file
    for (int i = 0; i < 5; i++)
    {
        if (fscanf(inFile, "%d", &number) != 1)
        {
            printf("Error reading integer from input.txt\n");
            fclose(inFile);
            pthread_exit(NULL);
        }
        sum += number;
    }

    fclose(inFile);

    // Print sum to console
    printf("Sum calculated by Thread T1: %d\n", sum);

    // Write sum to output.txt
    FILE *outFile = fopen("output.txt", "w");
    if (outFile == NULL)
    {
        perror("Error opening output.txt");
        pthread_exit(NULL);
    }

    fprintf(outFile, "Sum: %d\n", sum);
    fclose(outFile);

    pthread_exit(NULL);
}

// Thread 2: Takes user name input, replaces vowels, prints and appends to output.txt
void *thread2_function(void *arg)
{
    char input[MAX_LENGTH];
    printf("Enter your full name: ");
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
    printf("Modified String by Thread T2: %s\n", input);

    // Append modified string to output.txt
    FILE *outFile = fopen("output.txt", "a");
    if (outFile == NULL)
    {
        perror("Error opening output.txt");
        pthread_exit(NULL);
    }

    fprintf(outFile, "Modified Name: %s\n", input);
    fclose(outFile);

    pthread_exit(NULL);
}

int main()
{
    pthread_t t1, t2;
    // Check if input.txt exists, create if it doesn't
    FILE *checkFile = fopen("input.txt", "r");
    if (checkFile == NULL)
    {
        checkFile = fopen("input.txt", "w");
        if (checkFile != NULL)
        {
            // Write 5 integers to file
            fprintf(checkFile, "10\n20\n30\n40\n50\n");
            printf("Created input.txt with default values.\n");
            fclose(checkFile);
        }
        else
        {
            perror("Unable to create input.txt");
            return 1;
        }
    }
    else
    {
        fclose(checkFile);
    }

    // Create and run Thread 1
    pthread_create(&t1, NULL, thread1_function, NULL);
    pthread_join(t1, NULL); // Wait for Thread 1 to finish

    // Create and run Thread 2
    pthread_create(&t2, NULL, thread2_function, NULL);
    pthread_join(t2, NULL); // Wait for Thread 2 to finish

    return 0;
}