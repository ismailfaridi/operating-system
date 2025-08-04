/*
Implementing Round Robin scheduling algorithm in C

Write a program in C to implement Round Robin scheduling algorithm. The time slice for each process is 5 units. Given the list of Processes and their CPU burst time, calculate waiting time and turnaround time for each process. You also have to calculate average waiting and average turnaround time and display their values on screen.


For example, the list of processes and their CPU burst time are as follows:

Processes  	Burst Time
P0 		     12
P1 		     9
P2  		 4
P3 		     6

Time slice = 5 units

Assume that all the processes arrive at time 0 in sequence P0, P1, P2 P3
*/

#include <stdio.h>

int main()
{
    int n = 4;
    int avgWTime = 0, avgTTime = 0;
    int timeSlice = 5;
    int tSlice[4];
    int bTime[4];
    int tATime[4];
    int wTime[4];
    int count[4];

    bTime[0] = 12;
    bTime[1] = 9;
    bTime[2] = 4;
    bTime[3] = 6;
    int value[4];

    for (int i = 0; i < n; i++)
    {
        count[i] = 0;
        value[i] = 0;
    }

    int flag;
    int counter = 0;

    do
    {
        flag = 0;
        for (int i = 0; i < n; i++)
        {
            if (bTime[i] < timeSlice || bTime[i] == 0)
                tSlice[i] = bTime[i];
            else
                tSlice[i] = timeSlice;
                
            for (int j = 0; j < tSlice[i]; j++)
            {
                bTime[i]--;
                counter++;
            }

            tSlice[i] = bTime[i];
            if (value[i] != 1)
            {
                count[i] = counter;
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (bTime[i] != 0)
            {
                flag = 1;
            }
            else
                value[i] = 1;
        }

    } while (flag != 0);

    bTime[0] = 12;
    bTime[1] = 9;
    bTime[2] = 4;
    bTime[3] = 6;

    for (int i = 0; i < n; i++)
    {
        wTime[i] = count[i] - bTime[i];
    }

    printf("\n");

    // for loop to display turnaround time for each process
    for (int i = 0; i < n; i++)
    {
        printf("Turnaround Time: %i\n", count[i]);
    }

    // for loop to display wait time for each process
    for (int i = 0; i < n; i++)
    {
        printf("Waiting Time: %i\n", wTime[i]);
    }

    // for loop to calculate average wait time
    for (int i = 0; i < n; i++)
    {
        avgWTime = avgWTime + wTime[i];
    }

    // for loop to calculate average turnaround time
    for (int i = 0; i < n; i++)
    {
        avgTTime = avgTTime + count[i];
    }

    printf("Average Turnaround Time: %i\n", avgTTime / n);
    printf("Average Waiting Time: %i\n", avgWTime / n);
}