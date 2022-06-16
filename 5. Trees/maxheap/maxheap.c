/************************************************************************************************************************
 * File Name            : maxheap.c
 * Author               : Kang, Jun Gu
 * Date                 : 2022.05.06
 * Operating System     : Ubuntu 20.04.4 LTS
 * Compiler             : gcc 9.4.0
 * Build/Host/Target    : x86_64-linux-gnu
 ************************************************************************************************************************
 * version      : 1.0.0
 * description  : subroutine (or methods) for the MaxHeap data structure.
 ************************************************************************************************************************/
#include "maxheap.h"            // Definition of Max-Heap & Prototype of its functions
#include "pairheap.h"           // Priority Queue that supports a pairs of integer.
#include <stdlib.h>             // to use dynamic memory allocation: malloc() and free()

#define HEAP_FULL(heap) ((heap)->size==((heap)->capacity-1))    // Macro function returns 1 only if heap is full.
#define HEAP_EMPTY(heap) (!((heap)->size))                      // Macro function returns 1 only if heap is empty.
#define LEFT(idx) ((idx)*2)                                     // Macro funciton returns left child index of given index
#define RIGHT(idx) ((idx)*2+1)                                  // Macro funciton returns right child index of given index

int searchHeap(MaxHeap *heap, int i);

/************************************************************************************************************************
 * function     : int initHeap(MaxHeap *heap, int capacity);
 * description  : Initialize the max-heap
 *                allocate memory to 'int *data' and initialize 'int size' as 0 and 'int capacity' as givnen.
 *                return FAIL if it fails to allocate the memory to 'int *data'
 ************************************************************************************************************************
 * Input        : MaxHeap *heap         (the address of max-heap that needs to be initialize)
 *                int capacity          (the size of memory needs to be alloceated to max-heap)
 * Output       : int                   (return 1 if succeed to allocate, return 0 if failed.)
 ************************************************************************************************************************/
int initHeap(MaxHeap *heap, int capacity){              // Initialize the Max-Heap
    heap->data=(int*)malloc(capacity*sizeof(int));      // Allocate the memory that has size of capacity*4byte
    heap->size=0;                                       // Initialize size as 0 since no valid data is in it.
    heap->capacity=capacity;                            // Initialize capacity: indicating the size of memory allocated
    return ((heap->data)!=NULL?SUCCESS:FAIL);           // return if succeed or fail.
}

/************************************************************************************************************************
 * function     : int freeHeap(MaxHeap *heap);
 * description  : free the max-heap
 *                deallocate the memory that is allocated to 'int *data'
 *                reset 'int size' and 'int capacity' as 0
 ************************************************************************************************************************
 * Input        : MaxHeap *heap         (the address of max-heap that needs to be free.)
 * Output       : void
 ************************************************************************************************************************/
void freeHeap(MaxHeap *heap){                           // free the max-heap
    if(heap->data) free(heap->data);                    // free the memory if it is allocated on 'heap->data'
    heap->size=heap->capacity=0;                        // reset size and capacity as 0
}

/************************************************************************************************************************
 * function     : int resizeHeap(MaxHeap *heap, int capacity);
 * description  : resize the max-heap: re-allocate the memory allocated to 'int *data', and set capacity as given.
 ************************************************************************************************************************
 * Input        : MaxHeap *heap         (the address of max-heap that needs reallocation)
 *                int capacity          (the size of memory needs to be re-alloceated to max-heap)
 * Output       : int                   (return 1 if succeed to re-allocate, return 0 if failed.)
 ************************************************************************************************************************/
int resizeHeap(MaxHeap *heap, int capacity){
    int *temp=realloc(heap->data,capacity*sizeof(int)); // reallocate the memory to temporary pointer.s
    heap->capacity=capacity;                            // set capacity as given.
    if(temp==NULL) return FAIL;                         // if realloc returned NULL, it failed to realloc
    heap->data=temp;                                    // copy the address to heap->data if succeed.
    return SUCCESS;                                     // return SUCCEESS if succeed.
}

/************************************************************************************************************************
 * function     : int insertHeap(MaxHeap *heap, int item);
 * description  : insert new value into max-heap (it must search the proper place before inserting)
 ************************************************************************************************************************
 * Input        : MaxHeap *heap         (the address of the target max-heap)
 *                int item              (the value need to be inserted.)
 * Output       : int                   (return 1 if succeed to insert, return 0 if failed.)
 ************************************************************************************************************************/
int insertHeap(MaxHeap *heap, int item){
    int i;                                              // target integer value to be inserted
    if(HEAP_FULL(heap))                                 // If heap is full
        if(!resizeHeap(heap,(heap->capacity)*2))        // Try to resize as twice.
            return FAIL;                                // Return FAIL if it is full but fail to resize.
    // If it is not full, Find the proper place to insert.
    i=++(heap->size);                                   // Increase the size by 1 and start from the last element
    while((i!=1) && (item > (heap->data)[i/2])){        // Iterate until it reaches to root or is larger than its parent
        (heap->data)[i]=(heap->data)[i/2];              // Move parent to child
        i=i/2;                                          // and move index to parent
    }                                                   // The loop will be terminated if i gets correct index to insert item

    (heap->data)[i]=item;                               // insert item into correct place
    return SUCCESS;                                     // return SUCCESS
}

/************************************************************************************************************************
 * function     : int deleteHeap(MaxHeap *heap, int i);
 * description  : find the index of ith max value and delete corresponding element
 *                size must be decreased by 1, therefore shrink the size first,
 *                then determine where to put the element that was placed at the end
 ************************************************************************************************************************
 * Input        : MaxHeap *heap         (the address of the target max-heap)
 *                int i                 (the target order: ith max value to be deleted)
 * Output       : int                   (return 1 if succeed to delete, return 0 if failed to find the element.)
 ************************************************************************************************************************/
int deleteHeap(MaxHeap *heap, int i){
    int item;                                           // temporary variable: will store the last element
    int parent, child;                                  // the index of parent and child seeking currently.
    if(HEAP_EMPTY(heap)) return FAIL;                   // If the heap is empty, then return FAIL

    parent= i==1 ? 1 : searchHeap(heap,i);              // find the index of ith max value
    if(parent==FAIL) return FAIL;                       // if searchHeap returned FAIL, return the FAIL
    child=LEFT(parent);                                 // set child as parent's left as default
    
    item=(heap->data)[(heap->size)--];                  // save the value of last element to 'item' and decrease size by 1
    // find the proper place to insert the last element 'item'
    while(child<=(heap->size)){                         // iterate until index child reaches to the end.
        if( (child<(heap->size)) && ((heap->data)[child]<(heap->data)[child+1]) )
            ++child;                                    // traverse through the right child if right child is bigger
        if(item >= (heap->data)[child]) break;          // 'item' is bigger than child. => right place to insert 'item' (break)
        (heap->data)[parent]=(heap->data)[child];       // move child's value to parent
        parent=child;                                   // then change the index parent to previous child
        child=LEFT(parent);                             // update child as parent's left child
    }                                                   // (seeking top to bottom while moving data upward.)
    (heap->data)[parent]=item;                          // (after loop terminated) insert item into parent.
    return SUCCESS;                                     // return SUCCESS
}

/************************************************************************************************************************
 * function     : int findHeap(MaxHeap *heap, int i);
 * description  : return the ith max value of the heap (using searchHeap to find its index)
 *                if the index not found (may be out of range), return -1
 ************************************************************************************************************************
 * Input        : MaxHeap *heap         (the address of the target max-heap)
 *                int i                 (the target order: ith max value to be found)
 * Output       : int                   (return ith max value, return -1 if failed to find the element.)
 ************************************************************************************************************************/
int findInHeap(MaxHeap *heap, int i){                   // return the ith max value
    int index = i==1 ? 1 : searchHeap(heap,i);          // get the index of ith max value
    return (index ? (heap->data)[index] : -1);          // return ith max value, (return -1 if not found)
}

/************************************************************************************************************************
 * function     : int printHeap(MaxHeap *heap);
 * description  : print all the elements of the max-heap in level order (from root to node)
 *                if the index not found (may be out of range), return -1
 ************************************************************************************************************************
 * Input        : MaxHeap *heap         (the address of the target max-heap)
 * Output       : void
 ************************************************************************************************************************/
void printHeap(MaxHeap *heap){                          // print all the elements of the max-heap
    int i;
    if(HEAP_EMPTY(heap)){                               // if the max-heap is empty
        puts("error");                                  // print 'error'
        return;                                         // then return
    }
    // print in level order: access the heap array in ascending order
    for(i=1;i<=(heap->size);++i)                        // iterate i: 1 ~ heap->size
        printf("%d ",(heap->data)[i]);                  // print to output
    putchar('\n');                                      // put the new line '\n'
}

/************************************************************************************************************************
 * function     : int searchHeap(MaxHeap *heap, int i);
 * description  : find the index of ith max value and return it (index)
 *                if the index not found (may be out of range), return FAIL
 ************************************************************************************************************************
 * Input        : MaxHeap *heap         (the address of the target max-heap)
 *                int i                 (the target order: ith max value to be found)
 * Output       : int                   (return ith max value, return FAIL if failed to find the element.)
 ************************************************************************************************************************/
int searchHeap(MaxHeap *heap, int i){                   // return the index of ith max value
    pair parent,left,right;
    pairHeap pqueue={0,0};                              // another priority queue is needed to find index
    if(i==1) return 1;                                  // return 1 if i==1 (max value is always at root in max-heap)
    if(i<1 || i>(heap->size)) return FAIL;              // return FAIL if integer i is not in valid range

    initPairHeap(&pqueue,i*2+1);                        // initialize pqueue (reserve 2i+1; maximum size needed)
    insertPairHeap(&pqueue,setPair((heap->data)[1],1)); // put the 1 (index of root) into priority queue 

    for(i-=1;i>0;--i){                                  // iterate i-1 times: pop max value i-1 times
        parent=deletePairHeap(&pqueue);                 // pop the max value (no longer needed)
        left=setPair((heap->data)[LEFT(parent.index)],LEFT(parent.index));      // get parent's left child
        right=setPair((heap->data)[RIGHT(parent.index)],RIGHT(parent.index));   // get parent's right child
        if(left.index<=(heap->size))                    // if left child is in valid range
            insertPairHeap(&pqueue,left);               // insert the index of left child into priority queue
        if(right.index<=(heap->size))                   // if right child is in valid range
            insertPairHeap(&pqueue,right);              // insert the index of right child into priority queue
    }
                                                        // Now the index of ith max value is at the top of priority queue
    i=deletePairHeap(&pqueue).index;                    // get the index of ith max value from the top
    freePairHeap(&pqueue);                              // free the priority queue before return 
    return i;                                           // return the index of ith max value
}