/************************************************************************************************************************
 * File Name            : postfix.c
 * Author               : Kang, Jun Gu
 * Date                 : 2022.04.02
 * Operating System     : Ubuntu 20.04.4 LTS
 * Compiler             : gcc 9.4.0
 * Build/Host/Target    : x86_64-linux-gnu
 ************************************************************************************************************************
 * version      : 1.0.0
 * description  : Define the function int postfix(char*, char*, charstack*) (declared in "postfix.h") and its subroutine.
 * functions    : int getPre(char c);
 *                int cmpPre(charstack *pstack, char icop);
 *                int isUnary(char *p);
 *                int postfix(char *src, char *dst,  charstack *pstack);
 ************************************************************************************************************************/

#include <stdio.h>      // Standard Input/Ouptut
#include <ctype.h>      // Including int isdigit(int);
#include "postfix.h"

/************************************************************************************************************************
 * function     : int getPre(char c);
 * description  : The function that determines the relative precedence of the operator given.
 ************************************************************************************************************************
 * Input        : char c            (the operator that precedence needs to be determined.)
 * Output       : int               (Predefined relative precedence code corresponding to given character)
 ************************************************************************************************************************/
int getPre(char c){
    switch(c){
        case ')':               return 19;      // ')' must be processed in highest order.
        case '*': case '/':     return 13;      // '*' and '/' have the same precedence.
        case '+': case '-':     return 12;      // '+' and '-' have the same precedence but lower than '*' and '/'
        case '(': case '\0':    return 0;       // '(' is always pushed into stack.
        default:                return -1;      // In case prohibited operator.
    }
}

/************************************************************************************************************************
 * function     : int cmpPre(charstack *pstack, char icop);
 * description  : The function that compares the precedence between operator in top of stack and incoming operator.
 *                Return 1 if the precedence of top of stack is prior or equal to incoming operator. (Cause to pop stack)
 *                Return 0 oterwise. (incoming operator has higher precedence so that preserved on stack.)
 *                It determines the precedence of character using getPre(char c).
 ************************************************************************************************************************
 * Input        : charstack *pstack (the address of stack structure)
 *                char icop         (the character of incomimng operator)
 * Output       : int               (Return 1 if the precedence of top of stack is prior or equal to incoming operator)
 ************************************************************************************************************************/
int cmpPre(charstack *pstack, char icop){
    if(isEmptyStack(pstack)) return 0;                      // Check if stack is empty. (No needs to pop the stack)
    return (getPre(peekStack(pstack))>=getPre(icop));       // determines the precedence using getPre(char c) and compare
}

/************************************************************************************************************************
 * function     : int isUnary(char *p);
 * description  : Simple unary detection function. Unary should be located after another operator or '('
 ************************************************************************************************************************
 * Input        : char *p           (the operator need to be determined)
 * Output       : int               (Return 1 if unary; return 0 if not.)
 ************************************************************************************************************************/
int isUnary(char *p){ return (!isdigit(p[-1])&&p[-1]!=')'); }

/************************************************************************************************************************
 * function     : int postfix(char *src, char *dst,  charstack *pstack);
 * description  : This function read the infix expression from src and write postfix expr to dst using the stack given.
 *                cstring array src and dst is read and written by seeking pointer 'psrc' and 'pdst'
 *                Print the operand directly, and try to push incoming operator into stack
 ************************************************************************************************************************
 * Input        : char *src         (the address of string of infix expression)
 *                char *dst         (the address of string that postfix expression should be written)
 *                charstack *pstack (the address of character type of stack that this function will use.)
 * Output       : int               (Return 1 if succeed; return 0 otherwise.)
 ************************************************************************************************************************/
int postfix(char *src, char *dst, charstack *pstack){
    char *psrc, *pdst=dst;      // psrc will seek all elements of src sequentially. (increase by "++psrc"; in for loop)
                                // pdst will seek all elements of dst sequentially. ("*pdst++=c;"" write c and then increase)
    
    for(psrc=src;*psrc;++psrc){                     // start from src, point next element after iterate, until *psrc=NULL

        if(isdigit(*psrc)){                                 // if incoming character is digit.
            *pdst++=*psrc;                                  // just write it and 
            continue;                                       // seek next.
        }

        switch(*psrc){                                      // If incoming is non-digit charactor (operator or not allowed operand)

            case '(': pushStack(pstack,'('); break;         // Incoming '(' should be pushed into stack always.
            case ')':                                       // When ')' comes in, pop until it reaches to '('.
                while(peekStack(pstack)!='('&&!isEmptyStack(pstack)){
                    *pdst++=' ';
                    *pdst++=popStack(pstack);
                }
                popStack(pstack); break;                    // pop remaining '('

            case '+': case '-':                             // Operation varies from whether it is unary or binary.
                if(isUnary(psrc)){                          // Unary operator detection and process
                    if(*psrc=='+') break;                   // unary '+': delete (do not print and pass)
                    *pdst++=*psrc;                          // unary '-': Attach to number (print but no following ' ')
                    break;                                  // if unary, escape (operation done.)
                }                                           // if binary, fall through to next label (binary operation)

            case '*': case '/':                             // These will be general binary operator.
                while(cmpPre(pstack,*psrc)){                // Determine Precedence 
                    *pdst++=' ';
                    *pdst++=popStack(pstack);               // Pop the stack and print if top of stack is prior
                }
                *pdst++=' ';
                pushStack(pstack,*psrc);                    // Push incoming operator anyway
                break;

            case '\0': case '\n': break;                    // bypass the special character.
            default:                                        // Exception: Prohibitied character
                fprintf(stderr,"Warning: Operand (or operator) '%c' is not allowed!\n",*psrc);
                return 0;                                   // Conversion failed.
        }
    }

    /**********************All characters in infix expression are read by now.**********************/

    while(!isEmptyStack(pstack)){                       // Pop all remained elements from the stack.
        *pdst++=' ';  
        *pdst++=popStack(pstack);
    }
    *pdst++='\n';                                       // insert '\n' at the end of string
    *pdst='\0';                                         // insert NULL: End Of String

    return 1;                                           // conversion succeed.
}