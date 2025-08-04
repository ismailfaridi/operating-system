/*
Lab 8: Implementing Dining Philosophers Problem in C
 
Write a C program that solves Dining philosopher’s problem. Suppose there are five Philosophers whose work is just thinking and eating. They sat at a round table for dinner. To complete dinner each must need two chopsticks (or forks). But there are only five chopsticks available (chopsticks always equal to number of philosophers) on table. They take in such a manner that, first take left fork and next right fork. But problem is they try to take at same time. Since they are trying at same time, Fork 1, 2, 3, 4, 5 taken by Philosopher 1, 2, 3, 4, 5 respectively (since they are left side of each). And each one tries to take right side Fork. But no one found available Fork. Moreover, each one thinks that someone will release the Fork and then I can eat. This continuous waiting leads to Deadlock situation. 
To solve this deadlock situation, Last philosopher (any one can do this) first try to take right side fork and then left side fork. I.e. in our example 5th person tries to take 4th Fork instead of 5th one. Since 4th Fork already taken by 4th the person, he gets nothing. But he left 5th Fork. Now the first person will take this 5th Fork and complete dinner and make 1st and 5th available for remaining people. Next 2nd person takes 1st fork and completes and releases 1st and 2nd. This continues until all finishes dinner. In Operating System, this concept is used in process synchronization. Same problem but instead of Philosophers processes are there and instead of Forks, Resources are there. We follow above solution to avoid deadlock condition.
*/

#include <stdlib.h>
#include <stdio.h>
#define n 4

int compltedPhilo = 0, i;

struct fork
{
    int taken;
} ForkAvil[n];

struct philosp
{
    int left;
    int right;
} Philostatus[n];

void goForDinner(int philID)
{
    if (Philostatus[philID].left == 10 && Philostatus[philID].right == 10)
        printf("Philosopher %d completed his dinner\n", philID + 1);
    // if already completed dinner
    else if (Philostatus[philID].left == 1 && Philostatus[philID].right == 1)
    {
        // if just taken two forks
        printf("Philosopher %d completed his dinner\n", philID + 1);

        Philostatus[philID].left = Philostatus[philID].right = 10;
        int otherFork = philID - 1;

        if (otherFork == -1)
            otherFork = (n - 1);

        ForkAvil[philID].taken = ForkAvil[otherFork].taken = 0;
        printf("Philosopher %d released fork %d and fork %d\n", philID + 1, philID + 1, otherFork + 1);
        compltedPhilo++;
    }
    else if (Philostatus[philID].left == 1 && Philostatus[philID].right == 0)
    {
        if (philID == (n - 1))
        {
            if (ForkAvil[philID].taken == 0)
            {
                ForkAvil[philID].taken = Philostatus[philID].right = 1;
                printf("Fork %d taken by philosopher %d\n", philID + 1, philID + 1);
            }
            else
            {
                printf("Philosopher %d is waiting for fork %d\n", philID + 1, philID + 1);
            }
        }
        else
        {
            int dupphilID = philID;
            philID -= 1;

            if (philID == -1)
                philID = (n - 1);

            if (ForkAvil[philID].taken == 0)
            {
                ForkAvil[philID].taken = Philostatus[dupphilID].right = 1;
                printf("Fork %d taken by Philosopher %d\n", philID + 1, dupphilID + 1);
            }
            else
            {
                printf("Philosopher %d is waiting for Fork %d\n", dupphilID + 1, philID + 1);
            }
        }
    }
    else if (Philostatus[philID].left == 0)
    { // nothing taken yet
        if (philID == (n - 1))
        {
            if (ForkAvil[philID - 1].taken == 0)
            {
                ForkAvil[philID - 1].taken = Philostatus[philID].left = 1;
                printf("Fork %d taken by philosopher %d\n", philID, philID + 1);
            }
            else
            {
                printf("Philosopher %d is waiting for fork %d\n", philID + 1, philID);
            }
        }
        else
        { // except last philosopher case
            if (ForkAvil[philID].taken == 0)
            {
                ForkAvil[philID].taken = Philostatus[philID].left = 1;
                printf("Fork %d taken by Philosopher %d\n", philID + 1, philID + 1);
            }
            else
            {
                printf("Philosopher %d is waiting for Fork %d\n", philID + 1, philID + 1);
            }
        }
    }
    else
    {
    }
}

int main()
{
    for (i = 0; i < n; i++)
        ForkAvil[i].taken = Philostatus[i].left = Philostatus[i].right = 0;

    while (compltedPhilo < n)
    {
        for (i = 0; i < n; i++)
            goForDinner(i);
        printf("\nTill now num of philosophers completed dinner are %d\n\n", compltedPhilo);
    }

    system("pause");
}