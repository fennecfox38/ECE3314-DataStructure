#include <stdio.h>

struct node{
    int value;
    struct node *next;
};

void printAll(struct node *p){
    while(p!=NULL){
        printf("%d ", p->value);
        p=p->next;
    }
}

int main(void){
    struct node one, two, three;

    one.value=1;
    two.value=2;
    three.value=3;

    one.next=&two;
    two.next=&three;
    three.next=NULL;

    printf("\nLinked List Items: ");
    printAll(&one);
    printf("\n\n");

    return 0;
}