/************************************************************************************************************************
 * File Name            : hanoi.c
 * Author               : Kang, Jun Gu
 * Student ID           : 1218XXXX
 * Date                 : 2022.03.19
 * Operating System     : Ubuntu 20.04.4 LTS
 * Compiler             : gcc 9.4.0
 * Build/Host/Target    : x86_64-linux-gnu
 ************************************************************************************************************************
 * version      : 1.0.0
 * description  : Calculate and Print the procedure to move all of the disks in proper ways
 *                (following the rule of 'Towers of Hanoi')
 * functions    : int main(void);
 *                void hanoi(int n, char from, char to, char tmp);
 ************************************************************************************************************************/

#include <stdio.h>

void hanoi(int n, char from, char to, char tmp);

int main(void){
    int n;
    printf("Input n : ");
    scanf("%d",&n);             // Get the size of a stack of sorted disks to move.

    hanoi(n,'A','C','B');       // Move n-size of a stack of sorted disks from A to C using B as temporary
    return 0;
}

/************************************************************************************************************************
 * function     : void hanoi(int n, char from, char to, char tmp);
 * description  : Calculate and print a message that tells which disk should be moved from where to where in what order.
 ************************************************************************************************************************
 * Input        : int n (The size of the stack of sorted disks)
 *                char from (The character of a bar where the stack to move is)
 *                char to (The character of a bar that the stack should be moved to)
 *                char tmp (The character of a bar that can be used as a temporary space in the moving process)
 * Output       : void
 ************************************************************************************************************************/

void hanoi(int n, char from, char to, char tmp){
    static int cnt=0;       // Count the number of times disks have been moved.
                            // Type 'static' is used to accumulate the count throughout the whole lifetime of the program.

    /************************************the case if the size of disk stack is 1************************************/
    if(n==1){                                   // Move a disk simply if the size of disk stack is 1 and return.
        printf("%d: Move disk %d from tower %c to tower %c\n",++cnt,n,from,to);
        return;	
    }

    /**********************************the case if the size of disk stack is not 1**********************************/
    hanoi(n-1,from,tmp,to);                                 // Move upper (n-1) size of disk stack to tmp first.
    printf("%d: Move disk %d from tower %c to tower %c\n",++cnt,n,from,to);     // Move nth disk to destination.
    hanoi(n-1,tmp,to,from);                                 // Move (n-1) size of disk stack to destination 'to'.
}