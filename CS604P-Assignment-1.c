/*
    Write a C program that creates two threads (T1 and T2) with the following functionality:
    Thread T1:
        1. Reads integers from a file named input.txt (create this file with 5 integers, one per line).
        2. Calculates the sum of these integers.
        3. Writes the sum to a new file output.txt.
        4. Prints the sum to the console.
    Thread T2:
        1. Takes a string input from the user (e.g., "HelloOOS"). [Student needs to input their
        Full Name here].
        2. Replaces all vowels (a, e, i, o, u) with * (e.g., "H*ll***S").
        3. Prints the modified string to the console and appends it to output.txt.
    Requirements:
        • Use pthread_create() and pthread_join().
        • Students Should create a Folder with name as your Student ID and all the files input.txt,
        output.txt, program.c and program.o should be placed in that folder. Also, input student
        name as modified string input to replace the vowels. For example, input string should
        be as “Shakeel” and modified string written in the output file and in program screen
        shot should be “Sh*k**l”

    Program behavior:
    1. The main program creates `input.txt` with numbers 10, 20, 30, 40, 50 (if it doesn't exist)
    2. Thread T1:
        - Reads numbers from `input.txt`
        - Calculates the sum (150)
        - Writes the sum to `output.txt`
        - Prints the sum to console
    3. Thread T2:
        - Asks for user input (e.g., "HelloOS") or Student Name
        - Replaces vowels with * (e.g., "H*ll**S")
        - Prints the modified string to console
        - Appends the modified string to `output.txt`
    The “output.txt” file will contain both the sum from T1 and the modified string from T2.
*/

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
