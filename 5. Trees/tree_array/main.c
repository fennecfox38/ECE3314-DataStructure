#include <stdio.h>

#define TREE_SIZE 20

char tree[]={'\0','H','D','L','B','\0','J','N','A','C','\0','\0','I','K','\0','O','\0','\0','\0','\0'};

int getRightChildOf(int index){
    if(tree[index]!='\0' && (index*2+1)<TREE_SIZE)
        return (index*2+1);
    else return -1;
}

int getLeftChildOf(int index){
    if(tree[index]!='\0'&&(index*2+1)<TREE_SIZE)
        return (index*2);
    else return -1;
}

void preOrderTraversalFor(int index){
    if(index>0 && index<TREE_SIZE && tree[index]!='\0'){
        printf(" %c, ",tree[index]);
        preOrderTraversalFor(getLeftChildOf(index));
        preOrderTraversalFor(getRightChildOf(index));
    }
}

void postOrderTraversalFor(int index){
    if(index>0 && index<TREE_SIZE && tree[index]!='\0'){
        postOrderTraversalFor(getLeftChildOf(index));
        postOrderTraversalFor(getRightChildOf(index));
        printf(" %c, ",tree[index]);
    }
}

void inOrderTraversalFor(int index){
    if(index>0 && index<TREE_SIZE && tree[index]!='\0'){
        inOrderTraversalFor(getLeftChildOf(index));
        printf(" %c, ",tree[index]);
        inOrderTraversalFor(getRightChildOf(index));
    }
}

void addNode(char node, int root){
    if(tree[root]=='\0') tree[root]==node;
    else{
        if(node<tree[root]) addNode(node,root*2);
        else addNode(node,root*2+1);
    }
}

int findIndexOf(char node, int root){
    if(tree[root]==node) return root;
    else{
        if(node<tree[root]) return findIndexOf(node,root*2);
        else return findIndexOf(node,root*2+1);
    }
}

int findRightmostOf(int index){
    if(index*2<TREE_SIZE || tree[index*2]!='\0'){
        int childIndex=index*2;
        if(childIndex*2+1 < TREE_SIZE && tree[childIndex*2+1] != '\0')
            return childIndex*2+1;
    }
    return -1;
}

int findLeftmostOf(int index){
    if(index*2+1<TREE_SIZE || tree[index*2+1]!='\0'){
        int childIndex=index*2+1;
        if(childIndex*2 < TREE_SIZE && tree[childIndex*2] != '\0')
            return childIndex*2;
    }
    return -1;
}

void deleteNode(char node, int root){
    int index=findIndexOf(node,root);
    int rightMost=findRightmostOf(index);
    int leftMost=findLeftmostOf(index);

    if(rightMost!=-1){
        tree[index]=tree[rightMost];
        tree[rightMost]='\0';
    }
    else if(leftMost!=-1){
        tree[index]=tree[leftMost];
        tree[leftMost]='\0';
    }
    else tree[index]='\0';
}

int main(void){
    printf("\n\n");

    printf("Pre-Order Traversal: ");
    preOrderTraversalFor(1);
    printf("\n\n");

    printf("Post-Order Traversal: ");
    postOrderTraversalFor(1);
    printf("\n\n");

    printf("In-Order Traversal: ");
    inOrderTraversalFor(1);
    printf("\n\n");

    addNode('F',1);
    addNode('M',1);
    deleteNode('L',1);

    printf("\n *** After inserting F, M, and delete L: \n\n");

    printf("Pre-Order Traversal: ");
    preOrderTraversalFor(1);
    printf("\n\n");

    printf("Post-Order Traversal: ");
    postOrderTraversalFor(1);
    printf("\n\n");

    printf("In-Order Traversal: ");
    inOrderTraversalFor(1);
    printf("\n\n");

    printf("\n *** Index of Element K: %d\n\n",findIndexOf('K',1));

    return 0;
}