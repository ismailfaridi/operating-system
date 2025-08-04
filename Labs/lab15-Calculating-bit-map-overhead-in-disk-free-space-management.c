/*
Lab 15: Calculating Bit Map Overhead in Disk Free-Space Management in C

Write a c program to calculate the Overhead of Bit Map (or Bit Vector) in Free-Space Management. Frequently, the free space list is implemented as a bit map or bit vector. Each block is represented by 1 bit. If the block is free, the bit is 1; if it is allocated, the bit is 0. This approach is relatively simple and efficient in finding the first free block or n consecutive free blocks on the disk.
*/

#include <stdlib.h>
#include <stdio.h>

int main()
{
    double blockSize, diskSize, overhead;
    printf("Calculating Overhead of Bit-Map in Free-Space Management");
    printf("\nEnter block size (in KB): ");
    scanf("%lf", &blockSize);

    printf("\nEnter disk size (in GB): ");
    scanf("%lf", &diskSize);

    diskSize = diskSize * 1024 * 1024; // disk size in KB=disk size in GB×1024×1024
    overhead = (diskSize / blockSize) / (8 * 1024);

    printf("\nTotal Overhead (in KB): %lf", overhead);

    printf("\n\n");
    system("pause");
}