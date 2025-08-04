/*
Lab 11: Calculating Paging Parameters and Paging Performance in C

11.1 Calculating Paging Parameters

Write a c program to calculate various paging parameters. Paging is a memory management scheme that permits the physical address space of a process to be noncontiguous. It avoids the considerable problem of fitting the various sized memory chunks onto the backing store, from which most of the previous memory-management schemes suffered.

The output of program is as shown below:

Enter Logical Address Space Information: 16
Enter number of pages: 16
Enter total memory: 2048
Enter frames: 32

No. of bits needed for p: 4
No. of bits needed for f: 5
No. of bits needed for d: 11
Logical address size: 15
Physical address size: 16
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
    double pages, mem, phyFrames, p, f, d, las, pas;
    printf("Enter Logical Address Space Information");
    printf("\nEnter number of pages: ");
    scanf("%lf", &pages);

    printf("\nEnter total memory: ");
    scanf("%lf", &mem);

    printf("\nEnter frames: ");
    scanf("%lf", &phyFrames);

    p = log2(pages);
    printf("\nNo. of bits needed for p: %lf", ceil(p));

    f = log2(phyFrames);
    printf("\nNo. of bits needed for f: %lf", ceil(f));

    d = log2(mem);
    printf("\nNo. of bits needed for d: %lf", ceil(d));

    las = p + d;
    printf("\nLogical address size: %lf", las);

    pas = f + d;
    printf("\nPhysical address size: %lf", pas);

    printf("\n\n\n");
    system("pause");
}

/*
11.2 Calculating Paging Performance

Write a c program to calculate paging performance. The performance measure of paging is the effective memory access time based upon several parameters.
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
    double Tmem, Ttlb, hRatio, tEffective, mRatio;
    printf("Calculating Effective Memory Access Time");

    printf("\nEnter T(mem): ");
    scanf("%lf", &Tmem);

    printf("\nEnter T(TLB): ");
    scanf("%lf", &Ttlb);

    printf("\nEnter Hit Ratio: ");
    scanf("%lf", &hRatio);

    mRatio = 100 - hRatio;

    tEffective = (hRatio / 100) * (Ttlb + Tmem) + (mRatio / 100) * (Ttlb + 2 * Tmem);
    printf("\nTotal Effective Time for Memory Access: %lf", tEffective);

    printf("\n\n\n");
    system("pause");
}