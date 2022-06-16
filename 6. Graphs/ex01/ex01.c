#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

// stack implementation
int stack[MAX];
int top = -1;

// stack functions

void push(int item){
    stack[++top] = item;
}

int pop(){
    return stack[top--];
}

int peek(){
    return stack[top];
}

bool isStackEmpty(){
    return top == -1;
}


// queue implementation

int queue[MAX];
int rear = -1;
int front = 0;
int queueItemCount = 0;

// queue functions

void enqueue(int data){
    queue[++rear] = data;
    queueItemCount++;
}

int dequeue(){
    queueItemCount--;
    return queue[front++];
}

bool isQueueEmpty(){
    return queueItemCount == 0;
}

// graph representation
struct Vertex{
    int data;
    bool visited;
};

// array of vertices
struct Vertex *lstVertices[MAX];

// adjacency matrix
int adjMatrix[MAX][MAX];

// vertex count
int vertexCount = 0;

void addVertex(int data){
    struct Vertex *vertex = (struct Vertex*) malloc(sizeof(struct Vertex));
    vertex->data = data;
    vertex->visited=false;
    lstVertices[vertexCount++]=vertex;
}

void addEdge(int start, int end){
    adjMatrix[start][end]=1;
    adjMatrix[end][start]=1;
}

void displayVertex(int vertexIndex){
    printf("%d, ",lstVertices[vertexIndex]->data);
}

void displayAdjMatrix(){
    int i,j;
    printf("   ");
    for(i=0;i<MAX;++i)
        printf("%d ",lstVertices[i]->data);
    putchar('\n');
    for(i=0;i<MAX;++i){
        printf("%d ",lstVertices[i]->data);
        for(j=0;j<MAX;++j)
            printf("%d  ",adjMatrix[i][j]);
        putchar('\n');
    }
}

// Depth first search algorithm

// get the adjacent unvisited vertex
int getAdjUnvisitedVertex(int vertexIndex){
    int i;
    for(i=0;i<vertexCount;++i){
        if(adjMatrix[vertexIndex][i]==1 && lstVertices[i]->visited==false)
            return i;
    }
    return -1;
}

void depthFirstSearch(){
    int i;
    lstVertices[0]->visited=true;
    displayVertex(0);
    push(0);
    while(!isStackEmpty()){
        int unvisitedVertex=getAdjUnvisitedVertex(peek());
        if(unvisitedVertex==-1) pop();
        else{
            lstVertices[unvisitedVertex]->visited=true;
            displayVertex(unvisitedVertex);
            push(unvisitedVertex);
        }
    }
    for(i=0;i<vertexCount;++i)
        lstVertices[i]->visited=false;
}


// Breadth first search algorithm
void breadthFirstSearch(){
    int i;
    lstVertices[0]->visited=true;
    displayVertex(0);
    enqueue(0);
    int unvisitedVertex;
    while(!isQueueEmpty()){
        int tempVertex=dequeue();
        while((unvisitedVertex=getAdjUnvisitedVertex(tempVertex))!=-1){
            lstVertices[unvisitedVertex]->visited=true;
            displayVertex(unvisitedVertex);
            enqueue(unvisitedVertex);
        }
    }
    for(i=0;i<vertexCount;++i)
        lstVertices[i]->visited=false;
}

int main() {
    // initialzie the graph here
    int i,j;
    for(i=0;i<MAX;++i)
        for(j=0;j<MAX;++j)
            adjMatrix[i][j]=0;

    addVertex(10);
    addVertex(15);
    addVertex(20);
    addVertex(25);
    addVertex(30);
    addVertex(35);
    addVertex(40);
    addVertex(45);
    addVertex(50);
    addVertex(55);

    addEdge(0,1);
    addEdge(0,8);
    addEdge(0,7);
    addEdge(2,1);
    addEdge(2,3);
    addEdge(8,9);
    addEdge(6,7);
    addEdge(6,5);
    addEdge(4,3);
    addEdge(4,9);
    addEdge(4,5);
    
    displayAdjMatrix();

    printf("Depth First Search: ");
    depthFirstSearch();

    printf("\nBreadth First Search: ");
    breadthFirstSearch();

    return 0;
}

