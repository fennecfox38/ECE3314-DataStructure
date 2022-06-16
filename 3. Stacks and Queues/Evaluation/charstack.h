/************************************************************************************************************************
 * File Name            : charstack.h
 * Author               : Kang, Jun Gu
 * Date                 : 2022.03.31
 * Operating System     : Ubuntu 20.04.4 LTS
 * Compiler             : gcc 9.4.0
 * Build/Host/Target    : x86_64-linux-gnu
 ************************************************************************************************************************
 * version      : 1.0.0
 * description  : Declare the struct 'charstack' and the prototype of its functions (or methods).
 *                charstack is struct that contains pointers memeory will be allocated to, and points the top of stack.
 *                Memory management or any other stack operation may be performed through its methods.
 ************************************************************************************************************************/


#ifndef __CHARSTACK_H__

#define __CHARSTACK_H__

typedef struct{
    char *base;         // Memory will be allocated on base
    char *bound;        // End of address of allocated memeory
    char *top;          // Current top of stack (pointer)
}charstack;

void initStack(charstack *pstack, int capacity);        // Initialize stack: allocate give capacity of memory to stack
void freeStack(charstack *pstack);                      // Free stack: deallocate the memory allocated to stack and clear.
void resizeStack(charstack* pstack, int capacity);      // Resize Capacity: resize the memory allocated to the stack.
int isEmptyStack(charstack* pstack);                    // Check and return whether stack is empty. (return 1 for empty)
int isFullStack(charstack* pstack);                     // Check and return whether stack is full. (return 1 for full)
void pushStack(charstack* pstack, char c);              // Push element c into stack (Resize if needed)
char popStack(charstack* pstack);                       // Pop the top of stack and return the poped element. (return -1 if the stack is empty)
char peekStack(charstack* pstack);                      // Just return the top of stack. (return -1 if the stack is empty)

#endif