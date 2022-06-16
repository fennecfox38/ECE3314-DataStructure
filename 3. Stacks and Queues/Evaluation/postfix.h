/************************************************************************************************************************
 * File Name            : postfix.h
 * Author               : Kang, Jun Gu
 * Date                 : 2022.04.02
 * Operating System     : Ubuntu 20.04.4 LTS
 * Compiler             : gcc 9.4.0
 * Build/Host/Target    : x86_64-linux-gnu
 ************************************************************************************************************************
 * version      : 1.0.0
 * description  : Declare the function prototype of int postfix(char *src, char *dst, charstack *pstack);
 * The function postfix read the infix expression from src, process using stack, and write it in postfix expression to dst
 ************************************************************************************************************************/

#ifndef __POSTFIX_H__

#define __POSTFIX_H__

#include "charstack.h"
int postfix(char *src, char *dst, charstack *pstack);

#endif