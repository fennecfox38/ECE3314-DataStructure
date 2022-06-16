#include <stdio.h>
#include <stdlib.h>

typedef struct edge{
    char from;
    char to;
    struct edge *next;
} edge;

// Create a node
edge *newEdge(char from, char to){
    edge *temp = (struct edge *)malloc(sizeof(edge));
    temp->from = from;
    temp->to = to;
    temp->next = NULL;
    return temp;
}

int countTrees(edge *first, int size){
    // Step 1: get all parents
    char  *list = (char*)malloc(size*sizeof(char));
    int index;
    int count;
    edge *temp = first;
    for(index=0;temp!=NULL;temp=temp->next){
        list[index++] = temp->from;
        // Step 2: Exclude repeated parent
        for(int i=0;i<index-1;++i)
            if(temp->from == list[i])
                --index;
    }
    
    // Step 3: Exclude parents which are listed as children
    count = index;
    for(temp=first;temp!=NULL;temp=temp->next){
        for(int i=0;i<index;++i){
            if(temp->to == list[i]){
                --count;
                break;
            }
        }
    }
    free(list);
    return count;
}

int main(void){
    int size = 6;
    char from[]={'A','A','A','E','G','G'};
    char to[]={'B','C','D','F','H','I'};

    edge *first = newEdge(from[0],to[0]);
    edge *temp = first;

    for(int i=1;i<size;++i){
        temp->next = newEdge(from[i],to[i]);
        temp=temp->next;
    }

    temp = first;
    for(int i=0;i<size;++i){
        printf("Edge[%d]: %c -> %c\n",i,temp->from,temp->to);
        temp = temp->next;
    }

    int count = countTrees(first,size);
    printf("Number of trees: %d\n",count);

    return 0;
}