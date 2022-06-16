#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 6

int intArray[MAX];
int front = 0;
int rear = -1;
int itemCount=0;

int queuePeek(){
    return intArray[front];
}

bool isQueueEmpty(){
    return itemCount==0;
}

bool isQueueFull(){
    return itemCount==MAX;
}

int queueSize(){
    return itemCount;
}

void enQueue(int data){
    if(!isQueueFull()){
        if(rear==MAX-1){
            rear=-1;
        }
        intArray[++rear]=data;
        ++itemCount;
    }
}

int deQueue(){
    int data = intArray[front++];
    if(front==MAX){
        front=0;
    }
    --itemCount;
    return data;
}

int main(){
    enQueue(3);
    enQueue(5);
    enQueue(9);
    enQueue(1);
    enQueue(12);
    enQueue(15);

    if(isQueueFull())
        puts("Queue is full!");

    int num=deQueue();
    printf("Element removed: %d\n",num);

    enQueue(16);

    enQueue(17);
    enQueue(18);

    printf("Element at front: %d\n",queuePeek());
    puts("------------------");
    puts("index : 5 4 3 2 1 0");
    puts("------------------");
    puts("Queue: ");

    while(!isQueueEmpty()){
        int n=deQueue();
        printf("%d ",n);
    }
}