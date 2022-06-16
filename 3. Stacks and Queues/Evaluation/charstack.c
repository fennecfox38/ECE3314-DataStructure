/************************************************************************************************************************
 * File Name            : charstack.c
 * Author               : Kang, Jun Gu
 * Date                 : 2022.03.31
 * Operating System     : Ubuntu 20.04.4 LTS
 * Compiler             : gcc 9.4.0
 * Build/Host/Target    : x86_64-linux-gnu
 ************************************************************************************************************************
 * version      : 1.0.0
 * description  : Define the sub-function (or method) of struct 'charstack' declared in "charstack.h"
 * functions    : void initStack(charstack *pstack, int capacity);
 *                void freeStack(charstack *pstack);
 *                void resizeStack(charstack* pstack, int capacity);
 *                int isEmptyStack(charstack* pstack);
 *                int isFullStack(charstack* pstack);
 *                void pushStack(charstack* pstack, char c);
 *                char popStack(charstack* pstack);
 *                char peekStack(charstack* pstack);
 ************************************************************************************************************************/

#include <stdlib.h>
#include "charstack.h"

/************************************************************************************************************************
 * function     : void initStack(charstack *pstack, int capacity);
 * description  : The function that initialize the given charstack.
 ************************************************************************************************************************
 * Input        : charstack *pstack (the address of stack structure that needs to be initialized.)
 *                int capacity      (the size of allocated space, not size of stack)
 * Output       : void
 ************************************************************************************************************************/
void initStack(charstack *pstack, int capacity){
    pstack->base=(char*)malloc(capacity*sizeof(char));      // Allocate the given capacity of memeory to 'pstack->base'
    pstack->bound=(pstack->base)+capacity-1;                // Save the end of address of allocated memeory
    pstack->top=(pstack->base)-1;                           // The top of stack: initially points base-1
}

/************************************************************************************************************************
 * function     : void freeStack(charstack *pstack);
 * description  : The function that deallocate memory that allocated to the given charstack.
 ************************************************************************************************************************
 * Input        : charstack *pstack (the address of stack structure that needs to be free.)
 * Output       : void
 ************************************************************************************************************************/
void freeStack(charstack *pstack){
    free(pstack->base);                                     // Free the memory that allocated to 'pstack->base'
    pstack->base=NULL;
    pstack->bound=NULL;                                     // Set the value of all pointer as 'NULL'
    pstack->top=NULL;
}

/************************************************************************************************************************
 * function     : void resizeStack(charstack *pstack, int capacity);
 * description  : The function that resize the memory allocated to stack with the given capacity.
 ************************************************************************************************************************
 * Input        : charstack *pstack (the address of stack structure that needs to be resized.)
 *                int capacity      (the size of allocated space, not the size of stack)
 * Output       : void
 ************************************************************************************************************************/
void resizeStack(charstack* pstack, int capacity){
    int offset=(pstack->top)-(pstack->base);    // Preserve the offset of top from base,  in case the base address changes.
    pstack->base=(char*)realloc(pstack->base,capacity*sizeof(char));    // Reallocation
    pstack->bound=(pstack->base)+capacity-1;                            // Calculate the end of allocated memory.
    pstack->top=(pstack->base)+offset;                                  // restore top address by preserved offset.
}

/************************************************************************************************************************
 * function     : int isEmptyStack(charstack* pstack);
 * description  : The function that check and return whether stack is empty.
 ************************************************************************************************************************
 * Input        : charstack *pstack (the address of stack structure that needs to be tested.)
 * Output       : int               (return 1 if it is empty;  return 0 otherwise)
 ************************************************************************************************************************/
int isEmptyStack(charstack* pstack){
    return ((pstack->top)<(pstack->base));              // Return 1 if the address of thop is lower than base address.
}

/************************************************************************************************************************
 * function     : int isFullStack(charstack *pstack);
 * description  : The function that check and return whether stack is full.
 ************************************************************************************************************************
 * Input        : charstack *pstack (the address of stack structure that needs to be tested.)
 * Output       : int               (return 1 if it is full;  return 0 otherwise)
 ************************************************************************************************************************/
int isFullStack(charstack* pstack){
    return ((pstack->top)==(pstack->bound));
}

/************************************************************************************************************************
 * function     : void pushStack(charstack* pstack, char c);
 * description  : The function that push character into the stack given. (resize the stack if it is full)
 ************************************************************************************************************************
 * Input        : charstack *pstack (the address of stack structure that accepts the element.)
 * Output       : void
 ************************************************************************************************************************/
void pushStack(charstack* pstack, char c){
    if(isFullStack(pstack))                                         // Check if stack is full and resize if it is full.
        resizeStack(pstack, 2*((pstack->bound)-(pstack->base)+1));  // Resize by twice of original capacity.
    *(++(pstack->top))=c;                                           // increase the top address by 1 and store element.
}

/************************************************************************************************************************
 * function     : char popStack(charstack* pstack);
 * description  : The function that needs to be popped.
 ************************************************************************************************************************
 * Input        : charstack *pstack (the address of stack structure that accepts the element.)
 * Output       : char              (the value of popped element that was top previously; return -1 if empty)
 ************************************************************************************************************************/
char popStack(charstack* pstack){
    if(isEmptyStack(pstack)) return -1;                     // Check if the stack is empty and return -1 if empty.
    return *(pstack->top)--;                                // Return the top element and decrease the top address by 1.
}

/************************************************************************************************************************
 * function     : char peekStack(charstack *pstack);
 * description  : The function that simply return the value of top element of the stack given.
 ************************************************************************************************************************
 * Input        : charstack *pstack (the address of stack structure)
 * Output       : char              (the top element of the stack; return -1 if the stack is empty)
 ************************************************************************************************************************/
char peekStack(charstack* pstack){
    if(isEmptyStack(pstack)) return -1;                     // Check if the stack is empty and return -1 if empty.
    return *(pstack->top);                                  // Returen the top element.
}