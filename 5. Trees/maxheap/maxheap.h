/************************************************************************************************************************
 * File Name            : maxheap.h
 * Author               : Kang, Jun Gu
 * Date                 : 2022.05.06
 * Operating System     : Ubuntu 20.04.4 LTS
 * Compiler             : gcc 9.4.0
 * Build/Host/Target    : x86_64-linux-gnu
 ************************************************************************************************************************
 * version      : 1.0.0
 * description  : Declare the struct 'MaxHeap' and the prototype of its functions (or methods).
 *                MaxHeap is struct that contains pointer indicating array for the heap, its size, and size of valid data.
 *                Memory management or any other heap operation may be performed through its methods declared here.
 ************************************************************************************************************************/
#ifndef __MAXHEAP_H__

#define __MAXHEAP_H__

#include <stdio.h>                              // file structure FILE is defined in <stdio.h>

#define SUCCESS 1                               // Macro constant reserved for status 'SUCCESS'
#define FAIL 0                                  // Macro constant reserved for status 'FAIL'

/************************************************************************************************************************
 * structure    : MaxHeap
 * member       : int *data is a pointer that points the array for the heap.
 *                The memory will be allocated by 'initHeap' and deallocated by 'freeHeap'
 *                int capacity is the size of memory allocated in int *data
 *                int size is the size of valid data in heap array
 * Designed to use data[1] as root, while data[0] is never accessed. This leads to maximum allowable size is capacity-1.
 ************************************************************************************************************************/
typedef struct{                                 // structure MaxHeap Definition
    int *data;                                  // pointer indicating array for the heap. (will be allocated dynamically)
    int size;                                   // size of valid heap data in array.
    int capacity;                               // size of memory allocated in 'int *data'.
} MaxHeap;

int initHeap(MaxHeap* heap, int capacity);      // allocate the memory and initialize size as 0 and capacity as given.
void freeHeap(MaxHeap* heap);                   // deallocate the memory and reset member variables (size=capacity=0)
int insertHeap(MaxHeap* heap, int item);        // insert integer item in proper place. return FAIL if fail to resize.
int deleteHeap(MaxHeap* heap, int i);           // delete ith max value from the maxheap. return FAIL if empty.
int findInHeap(MaxHeap* heap, int i);           // find the ith max value of the maxheap. return FAIL if empty.
void printHeap(MaxHeap* heap);                  // Output all elements of the maxheap in level order

#endif
