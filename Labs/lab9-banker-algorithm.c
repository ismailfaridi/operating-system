/*
Lab 9: Implementing Banker’s Algorithm for Deadlock avoidance in C

In this algorithm, when a new process enters the system, it must declare the maximum number of instances of each resource type that it may need, i.e., each process must a priori claim maximum use of various system resources. This number may not exceed the total number of instances of resources in the system, and there can be multiple instances of resources. When a process requests a set of resources, the system must determine whether the allocation of these resources will leave the system in a safe state. If it will, the resources are allocated; otherwise the process must wait until some other process releases enough resources. We say that a system is in a safe state if all of the processes in the system can be executed to termination in some order; the order of process termination is called safe sequence. When a process gets all its resources, it must use them and return them in a finite amount of time. Let n be the number of processes in the system and m be the number of resource types. We need the following data structures in the Banker’s algorithm:

Available: A vector of length m. It shows number of available resources of each type. If Available[i] = k, then k instances of resource Ri are available.
Max: An n×m matrix that contain maximum demand of each process. If Max[i,j] = k, then process Pi can request maximum k instances of resource type Rj.
Allocation: An n×m matrix that contain number of resources of each type currently allocated to each process. If Allocation[i,j] = k, then Pi is currently allocated k instances of resource type Rj.
Need: An n×m matrix that shows the remaining resource need of each process. If Need[i,j] = k, then process Pi may need k more instances of resource type Rj to complete the task.
*/

#include <stdlib.h>
#include <stdio.h>

int current[5][5], maximum_claim[5][5], available[5];
int allocation[5] = {0, 0, 0, 0, 0};
int maxres[5], running[5], safe = 0;
int counter = 0, i, j, exec, resources, processes, k = 1;

int main()
{
    printf("\nEnter number of processes: ");
    scanf("%d", &processes);

    for (i = 0; i < processes; i++)
    {
        running[i] = 1;
        counter++;
    }

    printf("\nEnter number of resources: ");
    scanf("%d", &resources);

    printf("\nEnter Claim Vector:");
    for (i = 0; i < resources; i++)
    {
        scanf("%d", &maxres[i]);
    }

    printf("\nEnter Allocated Resource Table:\n");
    for (i = 0; i < processes; i++)
    {
        for (j = 0; j < resources; j++)
        {
            scanf("%d", &current[i][j]);
        }
    }

    printf("\nEnter Maximum Claim Table:\n");
    for (i = 0; i < processes; i++)
    {
        for (j = 0; j < resources; j++)
        {
            scanf("%d", &maximum_claim[i][j]);
        }
    }

    printf("\nThe Claim Vector is: ");
    for (i = 0; i < resources; i++)
    {
        printf("\t%d", maxres[i]);
    }

    printf("\nThe Allocated Resource Table:\n");
    for (i = 0; i < processes; i++)
    {
        for (j = 0; j < resources; j++)
        {
            printf("\t%d", current[i][j]);
        }
        printf("\n");
    }

    printf("\nThe Maximum Claim Table:\n");
    for (i = 0; i < processes; i++)
    {
        for (j = 0; j < resources; j++)
        {
            printf("\t%d", maximum_claim[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < processes; i++)
    {
        for (j = 0; j < resources; j++)
        {
            allocation[j] += current[i][j];
        }
    }

    printf("\nAllocated resources:");
    for (i = 0; i < resources; i++)
    {
        printf("\t%d", allocation[i]);
    }

    for (i = 0; i < resources; i++)
    {
        available[i] = maxres[i] - allocation[i];
    }

    printf("\nAvailable resources:");
    for (i = 0; i < resources; i++)
    {
        printf("\t%d", available[i]);
    }
    printf("\n");

    while (counter != 0)
    {
        safe = 0;
        for (i = 0; i < processes; i++)
        {
            if (running[i])
            {
                exec = 1;
                for (j = 0; j < resources; j++)
                {
                    if (maximum_claim[i][j] - current[i][j] > available[j])
                    {
                        exec = 0;
                        break;
                    }
                }
                if (exec)
                {
                    printf("\nProcess%d is executing\n", i + 1);
                    running[i] = 0;
                    counter--;
                    safe = 1;

                    for (j = 0; j < resources; j++)
                    {
                        available[j] += current[i][j];
                    }
                    break;
                }
            }
        }
        if (!safe)
        {
            printf("\nThe processes are in unsafe state.\n");
            break;
        }
        else
        {
            printf("\nThe process is in safe state");
            printf("\nAvailable vector:");

            for (i = 0; i < resources; i++)
            {
                printf("\t%d", available[i]);
            }

            printf("\n");
        }
    }
    system("pause");
}