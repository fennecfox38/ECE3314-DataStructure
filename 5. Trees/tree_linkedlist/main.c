#include <stdio.h>

typedef struct Node{
    char data;
    struct Node *left, *right;
} Node;

int addNode(Node **proot, Node *node){
    if(*proot==NULL){
        *proot=node;
        return 1;
    }
    else{
        if(node->data < (*proot)->data) return addNode(&((*proot)->left),node);
        else return addNode((&(*proot)->right),node);
    }
    return 0;
}

int main(){
    Node *root=NULL;
    Node rootNode;
    rootNode.data='H';
    rootNode.left=NULL;
    rootNode.right=NULL;
    
    addNode(&root,&rootNode);
    
    printf("Data: %c\n",root->data);
}