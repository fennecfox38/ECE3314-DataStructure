/************************************************************************************************************************
 * File Name            : graph.h
 * Author               : Kang, Jun Gu
 * Date                 : 2022.05.27
 * Operating System     : Ubuntu 20.04.4 LTS
 * Compiler             : gcc 9.4.0
 * Build/Host/Target    : x86_64-linux-gnu
 ************************************************************************************************************************
 * version      : 1.0.0
 * description  : Declare the struct 'graph', 'edge', 'minheap' and its methods (subfunction)
 ************************************************************************************************************************/
#ifndef __GRAPH_H__
#define __GRAPH_H__

#define MAX_V 26            // Maximum number of vertices: Number of the alphabet
#define MAX_E 325           // Maximum number of edges: (MAX_V)*(MAX_V-1)/2

typedef struct{             // Structure (implies the edge of undirected graph)
    short v1, v2;           // two vertices of the edge
    int w;                  // the weight of the edge
} edge;                     // redefined as type of 'edge'

typedef struct{             // Structure (implies the undirected graph)
    short vset[MAX_V];      // The array of vertices (will be reconstructed to vertices set)
    edge eheap[MAX_E];      // The array of edges (will be min-heap sorted by weight)
    short n;                // The number of vertices
    short esize;            // The valid size of edge array
} graph;                    // redefined as type of 'graph'

void insertEdge(graph* g, int v1, int v2, int w);   // add the given edge to the graph (register two vertices and one edge)
edge deleteHeap(graph *g);                          // Delete and return the root of minheap (and reorganize minheap)
int findSet(short *vset, int vertex);               // find the root of set of given vertex
void unionSet(short *vset, int s1, int s2);         // Perform the union operation of given set

#endif