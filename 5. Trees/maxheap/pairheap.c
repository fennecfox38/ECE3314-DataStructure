/************************************************************************************************************************
 * File Name            : pairheap.c
 * Author               : Kang, Jun Gu
 * Date                 : 2022.05.06
 * Operating System     : Ubuntu 20.04.4 LTS
 * Compiler             : gcc 9.4.0
 * Build/Host/Target    : x86_64-linux-gnu
 ************************************************************************************************************************
 * version      : 1.0.0
 * description  : subroutine (or methods) for the pairHeap data structure.
 ************************************************************************************************************************/
#include "pairheap.h"           // Priority Queue supports a pairs of integer.
#include <stdlib.h>             // to use dynamic memory allocation: malloc() and free()
#define SUCCESS 1                               // Macro constant reserved for status 'SUCCESS'
#define FAIL 0                                  // Macro constant reserved for status 'FAIL'

pair setPair(int key, int index){
    pair temp;
    temp.key=key;
    temp.index=index;
    return temp;
}

/************************************************************************************************************************
 * function     : int initHeap(pairHeap *heap, int capacity);
 * description  : Initialize the max-heap
 *                allocate memory to 'pair *data' and initialize 'int size' as 0.
 *                return FAIL if it fails to allocate the memory to 'pair* data'
 ************************************************************************************************************************
 * Input        : pairHeap *heap         (the address of pairHeap that needs to be initialize)
 *                int capacity          (the size of memory needs to be alloceated to pairHeap)
 * Output       : int                   (return 1 if succeed to allocate, return 0 if failed.)
 ************************************************************************************************************************/
int initPairHeap(pairHeap *heap, int capacity){             // Initialize the pairHeap
    heap->data=(pair*)malloc(capacity*sizeof(int));     // Allocate the memory that has size of capacity*8byte
    heap->size=0;                                       // Initialize size as 0 since no valid data is in it.
    return ((heap->data)!=NULL?SUCCESS:FAIL);           // return if succeed or fail.
}

/************************************************************************************************************************
 * function     : int freeHeap(pairHeap *heap);
 * description  : free the pairHeap
 *                deallocate the memory that is allocated to 'pair *data'
 *                reset 'int size' as 0
 ************************************************************************************************************************
 * Input        : pairHeap *heap         (the address of pairHeap that needs to be free.)
 * Output       : void
 ************************************************************************************************************************/
void freePairHeap(pairHeap *heap){                      // free the pairHeap
    if(heap->data) free(heap->data);                    // free the memory if it is allocated on 'heap->data'
    heap->size=0;                                       // reset size and capacity as 0
}

/************************************************************************************************************************
 * function     : void insertPairHeap(pairHeap *heap, pair item);
 * description  : insert new value into pairHeap (it must search the proper place before inserting)
 ************************************************************************************************************************
 * Input        : pairHeap *heap        (the address of the target pairHeap)
 *                pair item             (the value need to be inserted.)
 * Output       : void
 ************************************************************************************************************************/
void insertPairHeap(pairHeap *heap, pair item){
    int i;                                              // target integer value to be inserted
    // If it is not full, Find the proper place to insert.
    i=++(heap->size);                                   // Increase the size by 1 and start from the last element
    while((i!=1) && (item.key > (heap->data)[i/2].key)){// Iterate until it reaches to root or is larger than its parent
        (heap->data)[i]=(heap->data)[i/2];              // Move parent to child
        i=i/2;                                          // and move index to parent
    }                                                   // The loop will be terminated if i gets correct index to insert item

    (heap->data)[i]=item;                               // insert item into correct place
}

/************************************************************************************************************************
 * function     : pair deleteHeap(MaxHeap *heap, int i);
 * description  : find the index of ith max value and delete corresponding element
 *                size must be decreased by 1, therefore shrink the size first,
 *                then determine where to put the element that was placed at the end
 ************************************************************************************************************************
 * Input        : MaxHeap *heap         (the address of the target pairHeap)
 * Output       : pair                  (return the maximum element.)
 ***********************************************************************************************************************/
pair deletePairHeap(pairHeap *heap){
    pair item,temp;                                     // temporary variable: will store the last element
    int parent, child;                                  // the index of parent and child seeking currently.

    item=(heap->data)[1];                               // get the root (max element)
    parent=1;                                           // parent 
    child=parent*2;                                     // set child as parent's left as default
    
    temp=(heap->data)[(heap->size)--];                  // save the value of last element to 'temp' and decrease size by 1
    // find the proper place to insert the last element 'temp'
    while(child<=(heap->size)){                         // iterate until index child reaches to the end.
        if( (child<(heap->size)) && ((heap->data)[child].key<(heap->data)[child+1].key) )
            ++child;                                    // traverse through the right child if right child is bigger
        if(temp.key >= (heap->data)[child].key) break;  // 'temp' is bigger than child. => right place to insert 'temp' (break)
        (heap->data)[parent]=(heap->data)[child];       // move child's value to parent
        parent=child;                                   // then change the index parent to previous child
        child=parent*2;                                 // update child as parent's left child
    }                                                   // (seeking top to bottom while moving data upward.)
    (heap->data)[parent]=temp;                          // (after loop terminated) insert item into parent.
    return item;                                        // return item (max-element)
}