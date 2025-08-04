/*
Lab 12: Demand Paging Performance Program in C

Write a c program to calculate demand paging performance. Demand paging can have a significant effect on the performance of a computer system. To see why, let us compute the effective access time for a demand paged memory. For most computer systems, the memory access time, denoted ma now ranges from 10 to 200 nanoseconds. As long as we have no page faults, the effective access time is equal to the memory access time. If, however a page fault occurs, we must first read the relevant page from disk, and then access the desired word.
*/

#include <stdlib.h>
#include <stdio.h>

int main()
{
    double p, pfo, pst, dirty, ro, eat;
    printf("Calculating Effective Access Time for Demand Paging");

    printf("\nEnter p: ");
    scanf("%lf", &p);
    p = p / 100;

    printf("\nEnter Page Fault Overhead: ");
    scanf("%lf", &pfo);

    printf("\nEnter Page Swipe Time: ");
    scanf("%lf", &pst);

    printf("\nEnter time the page to be replaced (dirty): ");
    scanf("%lf", &dirty);
    dirty = dirty / 100;

    printf("\nEnter Restart Overhead Time: ");
    scanf("%lf", &ro);

    eat = 100 * (1 - p) + (pfo + 2 * ro + (dirty * pst) + (dirty * 2 * pst)) * p;
    printf("\nTotal Effective Access Time for Demand Paging: %lf", eat);

    system("pause");
}