/************************************************************************************************************************
 * File Name            : maxheap.h
 * Author               : Kang, Jun Gu
 * Date                 : 2022.05.06
 * Operating System     : Ubuntu 20.04.4 LTS
 * Compiler             : gcc 9.4.0
 * Build/Host/Target    : x86_64-linux-gnu
 ************************************************************************************************************************
 * version      : 1.0.0
 * description  : Declare the struct 'pairHeap' and the prototype of its functions (or methods).
 *                pairHeap is struct that contains pointer indicating array for the heap, its size, and size of valid data.
 *                Memory management or any other heap operation may be performed through its methods declared here.
 ************************************************************************************************************************/
typedef struct{
    int key;
    int index;
} pair;

typedef struct{
    pair *data;
    int size;
} pairHeap;

pair setPair(int key, int index);
int initPairHeap(pairHeap* heap, int capacity); // allocate the memory and initialize size as 0 and capacity as given.
void freePairHeap(pairHeap* heap);              // deallocate the memory and reset member variables (size=capacity=0)
void insertPairHeap(pairHeap* heap, pair item); // insert pair item in proper place. return FAIL if fail to resize.
pair deletePairHeap(pairHeap* heap);            // delete ith max value from the maxheap. return FAIL if empty.
