/*
Write the C program to create a basic simulation of a disk space management system. The program should manage disk space allocation and de-allocation for files stored on a simulated disk represented by an array. The system needs to allocate contiguous blocks of free space for new files and mark them as allocated. Additionally, it should be able to de-allocate space when files are deleted, marking the corresponding blocks as free for reuse. The program should simulate file creation and deletion by allocating and deallocating space accordingly, with print statements indicating the allocation and de-allocation of disk blocks for each file operation.
*/

#include <stdio.h>

#define TOTAL_BLOCKS 100 // Total number of disk blocks

int disk[TOTAL_BLOCKS] = {0}; // Array to represent disk blocks (0: free, 1: allocated)

// Function to allocate space for a new file
void allocateSpaceForFile(int fileSize)
{
    int startBlock = -1;
    int consecutiveBlocks = 0;

    for (int i = 0; i < TOTAL_BLOCKS; i++)
    {
        if (disk[i] == 0)
        {
            if (startBlock == -1)
            {
                startBlock = i;
            }
            consecutiveBlocks++;
            if (consecutiveBlocks == fileSize)
            {
                for (int j = startBlock; j < startBlock + fileSize; j++)
                {
                    disk[j] = 1;
                }
                printf("Allocated space for file of size %d starting at block %d\n", fileSize, startBlock);
                return;
            }
        }
        else
        {
            startBlock = -1;
            consecutiveBlocks = 0;
        }
    }

    printf("Error: Not enough free space to allocate for file of size %d\n", fileSize);
}

// Function to deallocate space when a file is deleted
void deallocateSpaceForFile(int startBlock, int fileSize)
{
    for (int i = startBlock; i < startBlock + fileSize; i++)
    {
        disk[i] = 0;
    }
    printf("Deallocated space for file starting at block %d\n", startBlock);
}

int main()
{
    // Simulate file creation and deletion
    allocateSpaceForFile(20);
    allocateSpaceForFile(30);
    deallocateSpaceForFile(0, 20);
    allocateSpaceForFile(10);

    return 0;
}