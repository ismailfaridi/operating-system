// Write a C program to calculate various paging parameters.
// Paging is a memory management technique that allows a process's physical address space to be noncontiguous. This approach eliminates the problem of fitting varying-sized memory chunks into the backing store, which was a major limitation of earlier memory management strategies.

#include <stdio.h>
#include <math.h>

int main() {
    char student_id[11], student_name[100];
    int logical_address_space, num_pages, total_memory, num_frames;
    int page_size, frame_size;
    int page_bits, frame_bits, offset_bits, logical_bits, physical_bits;

    printf("Enter Your Student ID: ");
    scanf("%s", student_id);

    printf("Enter Your Student Name: ");
    scanf(" %[^\n]%*c", student_name);

    printf("Enter Logical Address Space Information: ");
    scanf("%d", &logical_address_space);

    printf("Enter Number Of Pages: ");
    scanf("%d", &num_pages);

    printf("Enter Total Memory: ");
    scanf("%d", &total_memory);

    printf("Enter Number Of Frames: ");
    scanf("%d", &num_frames);

    // Calculating page size and frame size (assuming uniform size)
    page_size = (logical_address_space * 1024) / num_pages;
    frame_size = (total_memory * 1024) / num_frames;

    // Calculate number of bits using log2
    offset_bits = (int)ceil(log2(page_size));
    page_bits = (int)ceil(log2(num_pages));
    frame_bits = (int)ceil(log2(num_frames));

    logical_bits = page_bits + offset_bits;
    physical_bits = frame_bits + offset_bits;

    // Display output
    printf("\nCalculated Output:\n");
    printf("No. of bits needed for p (page number): %d\n", page_bits);
    printf("No. of bits needed for f (frame number): %d\n", frame_bits);
    printf("No. of bits needed for d (offset): %d\n", offset_bits);
    printf("Logical address size: %d bits\n", logical_bits);
    printf("Physical address size: %d bits\n", physical_bits);

    return 0;
}