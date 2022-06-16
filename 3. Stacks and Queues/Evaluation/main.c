/************************************************************************************************************************
 * File Name            : main.c
 * Author               : Kang, Jun Gu
 * Date                 : 2022.04.03
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
#include "postfix.h"
#define BUF_SIZ 64                                              // Size of I/O buffer

int main(int argc, char* argv []){                              // Expected command: "./a.out infix.txt postfix"
    FILE *read, *write;                                         // read: input (file) stream | write: output (file) stream
    charstack stack;                                            // stack defined in main : to reuse
    char input[BUF_SIZ], output[BUF_SIZ];                       // I/O Buffer: faster than direct file stream access.
    
    if(argc==3){                                                // if argument count is 3, try to open files as txt.
        if((read=fopen(argv[1],"r"))==NULL) return 0;           // try to open 1st file (terminate if fail)
        if((write=fopen(argv[2],"w"))==NULL){                   // try to open 2nd file 
            fclose(read); return 0;                             // (if fail, terminate after close 1st file)
        }
    }
    else {                                                      // if argument count is not 3
        read=stdin;                                             // Use stdin as input stream.
        write=stdout;                                           // Use stdout as output stream.
    }

    initStack(&stack,BUF_SIZ/2);                                // initialize the stack: half of buffer size is enough
    while(fgets(input,BUF_SIZ,read)!=NULL && *input!='\n'){     // Terminate loop if 'EOF' or no expression but only '\n' entered.
        if(postfix(input,output,&stack))                        // convert to postfix.
            fputs(output,write);                                // print result only if succeed.
    }
    freeStack(&stack);                                          // free stack: stack is no longer used.

    if(argc==3){                                                // Condition required
        fclose(read);                                           // (fclose(stdin) or fclose(stdout) is not proper)
        fclose(write);                                          // Close the file opened.
    }
    return 0;
}