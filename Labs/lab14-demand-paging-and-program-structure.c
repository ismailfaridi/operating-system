/*
Lab 14: Demand Paging and Program Structure in C

Write a c program to declare and initialize two 2-Dimensional arrays (or matrices); one by column-major order and other by row-major order. Demand paging is designed to be transparent to the user program. However, in some cases system performance can be improved if the programmer has an awareness of the underlying demand paging and execution environment of the language used in the program.
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Program to demonstrate Demand Paging Performance and Program Structure");
    // Code 1: Column-major order causing 1024x1024 page faults
    int A[1024][1024];
    for (int j = 0; j < 1024; j++)
    {
        for (int i = 0; i < 1024; i++)
        {
            A[i][j] = 0;
        }
    }
    printf("\n\nMatrix initialization in column-major order causing 1024x1024 page faults...");

    // Code 2: Row-major order causing 1024 page faults only
    int B[1024][1024];
    for (int i = 0; i < 1024; i++)
    {
        for (int j = 0; j < 1024; j++)
        {
            B[i][j] = 0;
        }
    }
    printf("\n\nMatrix initialization in row-major order causing 1024 page faults...");

    system("pause");
}