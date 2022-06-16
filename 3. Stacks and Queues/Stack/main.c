#include <stdio.h>

int MAXSIZE = 10;
int stack[10];
int top = -1;

int isStackEmpty(){
    if(top==-1) return 1;
    else return 0;
}

int isStackFull(){
    if(top==MAXSIZE) return 1;
    else return 0;
}

int stackPeek(){
    if(isStackEmpty()) return 0;
    return stack[top];
}

int stackPop(){
    int data;
    if(!isStackEmpty()){
        data=stack[top];
        --top;
        return data;
    }
    else{
        puts("Stack is empty!");
        return -1;
    }
}

void stackPush(int data){
    if(!isStackFull()){
        ++top;
        stack[top]=data;
    }
    else{
        puts("Stack is full!");
    }
}

int main(){
    stackPush(3);
    stackPush(5);
    stackPush(9);
    stackPush(1);
    stackPush(12);
    stackPush(15);

    printf("Element at top of the stack: %d\n",stackPeek());
    printf("Elements: \n");

    while(!isStackEmpty()){
        int data=stackPop();
        printf("%d\n",data);
    }

    printf("Stack full: %s\n",isStackFull()?"true":"false");
    printf("Stack empty: %s\n",isStackEmpty()?"true":"false");
}