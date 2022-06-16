/************************************************************************************************************************
 * File Name            : graph.c
 * Author               : Kang, Jun Gu
 * Date                 : 2022.05.27
 * Operating System     : Ubuntu 20.04.4 LTS
 * Compiler             : gcc 9.4.0
 * Build/Host/Target    : x86_64-linux-gnu
 ************************************************************************************************************************
 * version      : 1.0.0
 * dependency   : graph.h
 * description  : Methods (or subfunction) of the graph, set and minheap data structure.
 ************************************************************************************************************************/
#include "graph.h"

/************************************************************************************************************************
 * function     : void insertEdge(graph* g, int v1, int v2, int w);
 * description  : add the info of edge (2 vertices and weight) to given graph.
 *                Register two vertices on vertice array
 *                Insert edge into min-heap whose data type is 'edge' (min-heap is ordered by the weight of edge)
 *                Note that this skips cheking the fullity of heap (for performance),
 *                since the capacity of minheap is guaranteed to be able to accept the maximum number of edges, MAX_E.
 ************************************************************************************************************************
 * Input        : graph* g          (the address of graph that will accept the edge)
 *                int v1, v2        (the two vertices that compose the edge)
 *                int w             (the weight of the edge)
 * Output       : void
 ************************************************************************************************************************/
void insertEdge(graph* g, int v1, int v2, int w){   // Register Vertices + insert Edge into Min-Heap
    int i=++(g->esize);                             // Starting from the last element of min-heap
    while((i!=1) && (w<((g->eheap)[i/2].w))){       // iterate until it reachs to root or smaller parent
        (g->eheap)[i]=(g->eheap)[i/2];              // move parent's data to child
        i=i/2;                                      // and move index upward (index points to parent)
    }   // Now element index i pointing is proper place to insert Edge (following min-heap policy) 
    (g->eheap)[i].w=w;              // save the weight (on the proper element)
    (g->eheap)[i].v1=v1;            // save the 1st vertex (on the proper element)
    (g->eheap)[i].v2=v2;            // save the 2nd vertex (on the proper element)
    if(g->vset[v1]!=-1){
        g->vset[v1]=-1;             // mark the 1st vertex in vertice list (set as -1 for 'set' representation)
        ++(g->n);                   // increase the vertices count
    }
    if(g->vset[v2]!=-1){
        g->vset[v2]=-1;             // mark the 2nd vertex in vertice lise (set as -1 for 'set' representation)
        ++(g->n);                   // increase the vertices count
    }          
}

/************************************************************************************************************************
 * function     : edge deleteHeap(graph* g);
 * description  : Perform the deletion of root of the edge min-heap and return it back.
 *                It also re-arrange the min-heap to meet the min-heap policy (parent is smaller than its children)
 *                Note that deleteHeap skips cheking the empty of heap (for performance),
 *                since the function 'void kruskal(graph *g)' calls this only when the heap is not empty.
 ************************************************************************************************************************
 * Input        : graph* g          (the address of vertices array represented as a set)
 * Output       : edge              (returns the edge that was previously root of the min-heap)
 ************************************************************************************************************************/
edge deleteHeap(graph* g){
    int parent=1;                       // navigating index: initially start from root and descend by loop
    int child=2;                        // child of 'parent', left child is selected as default.
    edge root=(g->eheap)[1];            // temporary variable that stores the return value root. (will be deleted)
    edge tmp=(g->eheap)[(g->esize)--];  // temp var storing the last element (and shrink the heap size)
    while(child<=(g->esize)){           // iterate only when child is in valid range (smaller than the heap size)
        if(child<(g->esize) && ((g->eheap)[child].w)>((g->eheap)[child+1].w))
            ++child;                    // choose right child if right child's weight is smaller than left.
        if((tmp.w)<((g->eheap)[child].w)) break;    // escape the loop if child is bigger than tmp (proper to insert)
        (g->eheap)[parent]=(g->eheap)[child];       // if not, move child's data to parent
        parent=child;                               // and index parent points child now. 
        child=parent*2;                             // and index child points parent's left child
    }                                   // Now 'parent' points the proper place to insert the 'tmp'
    (g->eheap)[parent]=tmp;             // store the data of 'tmp' to where 'parent' points
    return root;                        // Return the deleted root data.
}

/************************************************************************************************************************
 * function     : void unionSet(short *vset, int s1, int s2);
 * description  : Perform the union operation of two sets whose root is given.
 *                Note that s1 and s2 must be the index of the root and not be the same. (otherwise it corrupts the set)
 *                Union must be performed by merging smaller set into bigger set to keep the balance (for performance)
 *                In set representation, the element of set in array has its parent index, while the root element has cou
 *                nt in negative. (Magnititude is count and sign is negative) Union operation must keep these properties.
 ************************************************************************************************************************
 * Input        : short *vset       (the address of vertices array represented as a set)
 *                int s1            (the index of the root of 1st set)
 *                int s2            (the index of the root of 2nd set)
 * Output       : void
 ************************************************************************************************************************/
void unionSet(short *vset, int s1, int s2){
    int cnt=vset[s1]+vset[s2];      // the count of new unioned set is calculated by simply adding two counts.
    if(vset[s1]>vset[s2]){          // if s2 has more elements (Note that count is in negative)
        vset[s1]=s2;                // merge s1 into s2
        vset[s2]=cnt;               // and update the count of s2
    }
    else{                           // if s1 has more elements
        vset[s2]=s1;                // merge s2 into s1
        vset[s1]=cnt;               // and update the count of s1
    }
}

/************************************************************************************************************************
 * function     : int findSet(short *vset, int vertex);
 * description  : Traceback the root of the set which includes the given vertex, and returns it. (Also collapsing)
 *                Identifying the set
 ************************************************************************************************************************
 * Input        : short *vset       (the address of vertices array represented as a set)
 *                int vertex        (the vertex whose root needs to be found)
 * Output       : int               (returns the index of root of the set)
 ************************************************************************************************************************/
int findSet(short *vset, int vertex){
    int root, tmp;
    for(root=vertex;vset[root]>=0;root=vset[root]); // iterate ascend (refer vset) until negative value is found (root)
    for(;vertex!=root;vertex=tmp){  // collapsing set tree: replace its parent with root and iterate ascend until root
        tmp=vset[vertex];           // save its parent to tmp
        vset[vertex]=root;          // replace parent with root
    }
    return root;                    // return the index of the root of set
}