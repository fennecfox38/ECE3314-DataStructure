/************************************************************************************************************************
 * File Name            : main.c
 * Author               : Kang, Jun Gu
 * Date                 : 2022.05.06
 * Operating System     : Ubuntu 20.04.4 LTS
 * Compiler             : gcc 9.4.0
 * Build/Host/Target    : x86_64-linux-gnu
 ************************************************************************************************************************
 * version      : 1.0.0
 * description  : The main function reads line from input stream, pass it to function 'postfix' and get the postfix
 *                expression, then print it to output stream.
 *                The input and output stream can be file given through the arguments from command line or stdio.
 *                The function main also provide input, output buffer and character stack to function 'postfix' (to reuse)
 * functions    : int main(int argc, char* argv[]);
 ************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "maxheap.h"
#define ISEOS(c) ((c)=='\n'||(c)=='\0')             // Macro function returns 1 if character is end of string
#define ISDIGIT(c) ((c)>='0' && (c)<='9')           // Macro function returns 1 if character is ASCII Digit
#define BUF_SIZ 64                                  // Size of I/O buffer

int stoi(char *a);                                  // char array (string) to non-negative integer

/************************************************************************************************************************
 * function     : int main(void);
 * description  : It read the max-heap command from input file stream and output the result to output file stream.
 *                It classifies the command and call the proper max-heap function to process.
 *                It also handle the exception for illegal command or value.
 ************************************************************************************************************************
 * Input        : void
 * Output       : int               (Return 0 for proper termination, return 1 for abnormal termination)
 ************************************************************************************************************************/

int main(void){
    MaxHeap heap={0,0,0};                           // Max-Heap with initializing all member as 0.
    char line[BUF_SIZ];                             // input Buffer: faster than direct file stream access.
    int i;                                          // Integer variable: might be either data or index.

    if(initHeap(&heap,16)==FAIL) exit(1);           // initialize the maxheap (size=0)
    while(fgets(line,BUF_SIZ,stdin)!=NULL && !ISEOS(*line)){// Terminate loop if 'EOF' or no expression but only '\n' entered.
        if(ISEOS(line[1])) i=1;                     // if input is only one character regard i as 1. (point the root)
        else if(line[1]==' ') i=stoi(line+2);       // if therer a
        else i=-1;                                  // it is illegal if 2nd charecter is neither EOS nor space ' '

        if(i<0){                                    // Handle illegal case exception.
            fprintf(stderr,"Negative number or character is not allowed.\n");// print the exception message
            freeHeap(&heap);                        // call the close: ready to terminate the program
            exit(1);                                // terminate with failed code 1
        }
        switch(*line){                              // Classify the command using first character.
            case 'I':                               // try to insert into heap and print error if it is not resizable
                puts(insertHeap(&heap,i)!=FAIL?"done":"error"); break; 
            case 'D':                               // try to delete ith max value from heap and print error if fail.
                puts(deleteHeap(&heap,i)!=FAIL?"done":"error"); break; 
            case 'T':                               // try to find ith max value from heap
                i=findInHeap(&heap,i);              // get the ith max value
                if(i<0) puts("error");              // print error if fail to find (out of range)
                else printf("%d\n",i);              // print ith max value
                break;
            case 'P': printHeap(&heap); break;      // output all elemnents in maxheap, in level order.
            default:
                fprintf(stderr,"Unknown Command: %c\n",*line);  // Unknown Command: print error message
                freeHeap(&heap);                    // call the close: ready to terminate the program
                exit(1);                            // terminate with failed code 1
        }
    }
    freeHeap(&heap);                                // call the close: ready to terminate the program
    return 0;                                       // terminate with normal termination code 0
}

/************************************************************************************************************************
 * function     : int stoi(char* a);
 * description  : It parse the given character string and convert to the integer (return the converted integer)
 *                return -1 if any nondigit character is dectected. (Only parse 0 or positive integer)
 ************************************************************************************************************************
 * Input        : char* a   (The argument array that is passed through the command line.)
 * Output       : int       (Return 0 for proper termination, return 1 for abnormal termination)
 ************************************************************************************************************************/
int stoi(char *a){
    int i=0;                                // integer variable that will be accumulated (initialize as 0)
    while(!ISEOS(*a)){                      // Iterate until pointer a reach to the EOS.
        if(!ISDIGIT(*a)) return -1;         // return -1 if detect any nondigit character.
        i=i*10+*(a++)-'0';                  // multiply 10 and add (*a)-'0', the number converted from ASCII Digit
    }                                       // also increase a by 1 to point next character
    return i;                               // return the integer from parsing.
}