/************************************************************************************************************************
 * File Name            : main.c
 * Author               : Kang, Jun Gu
 * Date                 : 2022.05.27
 * Operating System     : Ubuntu 20.04.4 LTS
 * Compiler             : gcc 9.4.0
 * Build/Host/Target    : x86_64-linux-gnu
 ************************************************************************************************************************
 * version      : 1.0.0
 * dependency   : graph.h, graph.c
 * description  : Methods (or subfunction) of the graph, set and minheap data structure.
 ************************************************************************************************************************/
#include <stdio.h>      // Standard Input / Output Stream
#include <stdlib.h>     // in order to use 'int atoi(char a[])'
#include "graph.h"      // 
#define BUF_SIZ 64      // Size of Input buffer is defined by Macro constant
void kruskal(graph *g); // Print minimum cost spanning tree by Kruskal Algorithm

/************************************************************************************************************************
 * function     : int main(void);
 * description  : main function of this program.
 *                It reads line by line from stdin, parse and insert edge into edge min-heap.
 *                Print minimum cost spanning tree by function 'void kruskal(graph *g);'
 ************************************************************************************************************************
 * Input        : void
 * Output       : int   (exit code: 0 for normal)
 ************************************************************************************************************************/
int main(void){ 
    char line[BUF_SIZ];                                             // input buffer (store the line of string)
    graph g={0};                                        // structure graph g (all member variables are initialized as 0)
    while(fgets(line,BUF_SIZ,stdin)!=NULL && *line!='\n' && *line!='\0')    // get line from stdin and iterate until EOF
        insertEdge(&g,line[0]-'a',line[2]-'a',atoi(line+4));        // insert the Edge into edge heap and mark vertices.
    kruskal(&g);                                                    // get minimum cost spanning tree by kruskal(&g)
    return 0;
}

/************************************************************************************************************************
 * function     : void kruskal(graph *g);
 * description  : Find the minimum cost spanning tree of given graph by Kruskal Algorithm. Print it to stdout
 *                It reads line by line from stdin, parse and insert edge into edge min-heap.
 *                Print minimum cost spanning tree by function 'void kruskal(graph *g);'
 ************************************************************************************************************************
 * Input        : graph* g      (the address of graph whose minimum cost spanning tree is needed)
 * Output       : void
 ************************************************************************************************************************/
void kruskal(graph *g){
    edge edge;                          // temporary variable (store the target edge inspected)
    int s1, s2;                         // the indexes of roots of two set (temp var for target edge) 
    int selected=0;                     // variable that count the number of edge selected for minimum cost spanning tree
    if((g->esize)<(g->n)-1){                 // if edges are less than n-1
        fputs("no spanning tree",stdout);   // there are no spannig tree
        return;                         // further process is not needed
    }
    while((g->esize) && selected!=(g->n)-1){ // iterate while edge min-heap is not empty and selected edges are less than n-1
        edge=deleteHeap(g);             // get the minimum weighted, unselected edge from min-heap
        s1=findSet(g->vset,edge.v1);    // find the index of root of set which includes the 1st vertex of edge
        s2=findSet(g->vset,edge.v2);    // find the index of root of set which includes the 2nd vertex of edge
        if(s1!=s2){                     // if two vertices is not in same set
            ++selected;                 // this edge may be chosen for minimum cost spanning tree
            fprintf(stdout,"%c---%c = %d\n",edge.v1+'a',edge.v2+'a',edge.w);    // print this edge in format
            unionSet(g->vset,s1,s2);    // union these two set (since these are chosen and connected now.)
        }
    }                               // the number of edges of spanning tree of the graph that has n vertices must be n-1
    if(selected!=(g->n)-1)               // if less than n-1 of edges are selected
        fputs("no spanning tree",stdout);   // there are no spanning tree
}