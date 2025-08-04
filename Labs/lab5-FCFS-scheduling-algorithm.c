/*
Implementing FCFS scheduling algorithm in C

Write a program in C to implement FCFS scheduling algorithm. Given the list of Processes and their burst time, calculate waiting time and turnaround time for each process. Also calculate average waiting time and average turnaround time. For example, the list of processes and their CPU burst time are as follows:

Processes  	Burst Time
P0 		     10
P1 		     4
P2  		 6
P3 		     8

Assume that all the processes arrive at time 0 in sequence P0, P1, P2 P3
*/

#include <stdio.h>

int main()
{
    int n = 4;     // number of processes
    int bTime[4];  // array for storing burst time for each process
    int wTime[4];  // array for storing wait time for each process
    int tATime[4]; // array for storing turnaround time for each process

    bTime[0] = 10;
    bTime[1] = 4;
    bTime[2] = 6;
    bTime[3] = 8;

    int avgWTime = 0;
    int avgtATime = 0;

    wTime[0] = 0;
    // loop for calculating waiting time for each process
    for (int i = 1; i < n; i++)
    {
        wTime[i] = wTime[i - 1] + bTime[i - 1]; // calculating wait time for each process
        avgWTime = avgWTime + wTime[i];
    }

    // loop for calculating turnaround time for each process
    for (int i = 0; i < n; i++)
    {
        tATime[i] = wTime[i] + bTime[i]; // calculating turnaround time for each process
        avgtATime = avgtATime + tATime[i];
    }

    avgWTime = avgWTime / n;   // calculating average waiting time
    avgtATime = avgtATime / n; // calculating average turnaround time

    // loop for displaying waiting time and turnaround times
    for (int i = 0; i < n; i++)
    {
        printf("P%i: ", i);
        printf("Wait Time: %i\t", wTime[i]);        // printing wait time for each process
        printf("Turnaroung Time: %i\n", tATime[i]); // printing turnaround time for each process
    }

    // displaying average waiting time and average turnaround time
    printf("\nAverage Wait time: %i\n", avgWTime);
    printf("\nAverage Wait time: %i\n\n", avgtATime);
}