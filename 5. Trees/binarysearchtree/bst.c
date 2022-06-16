// Data Structure Lab 11 (Tree: Part 2)
// Dynamic Binary Search Tree implementation using linked list

#include <stdio.h>
#include <stdlib.h>

struct node
{
  int data;
  struct node *left;
  struct node *right;
};

// Create a node
struct node *newNode(int item)
{
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->data = item;
  temp->left = temp->right = NULL;
  return temp;
}

void preOrderTraversal(struct node *root)
{
  if (root != NULL)
  {
    printf("%d, ", root->data);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
  }
}

void postOrderTraversal(struct node *root)
{
  if (root != NULL)
  {
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printf(" %d, ", root->data);
  }
}

void inOrderTraversal(struct node *root)
{
  if (root != NULL)
  {
    inOrderTraversal(root->left);
    printf(" %d, ", root->data);
    inOrderTraversal(root->right);
  }
}

// Insert a node
struct node *insert(struct node *node, int key)
{
  if (node == NULL)
    return newNode(key);

  if (key < node->data)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  return node;
}

struct node *getRightMost(struct node* node){
    struct node *current = node;
    while(current && current->right != NULL)
        current = current->right;
    return current;
}

/*
struct node *getLeftMost(struct node* node){
    struct node *current = node;
    while(current && current->left != NULL)
        current = current->left;
    return current;
}
*/

// Deleting a node
struct node *delete (struct node *root, int key)
{
  if(root==NULL) return NULL;

  if(key < root->data)
    root->left = delete(root->left,key);
  else if(key > root->data)
    root->right = delete(root->right,key);
  else{
      if(root->left == NULL){
          struct node *temp = root->right;
          free(root);
          return temp;
      }
      else if(root->right == NULL){
          struct node *temp = root->left;
          free(root);
          return temp;
      }
      
      struct node *temp = getRightMost(root->left);
      root->data = temp->data;
      root->left = delete(root->left, temp->data);
      /*
      struct node *temp = getLeftMost(root->right);
      root->data = temp->data;
      root->right = delete(root->right, temp->data);
      */
  }
  return root;
}

int main()
{
  struct node *root = NULL;
  root = insert(root, 30);
  root = insert(root, 5);
  root = insert(root, 40);
  root = insert(root, 2);
  root = insert(root, 35);
  root = insert(root, 80);

  printf("Inorder traversal: ");
  inOrderTraversal(root);

  puts("\nAfter deleting 40");

  root = delete(root, 40);
  printf("Inorder traversal: ");
  inOrderTraversal(root);
}