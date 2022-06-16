#include "term.h"
#define MAX_COL 100

void fast_transpose(term a[], term b[]){
    int i,j;
    int row_terms[MAX_COL]={0,};
    int starting_pos[MAX_COL];

    int num_terms = b[0].value = a[0].value;
    int num_cols = b[0].row = a[0].col;
    b[0].col=a[0].row;
    
    if(num_terms>0){
        //for(i=0;i<num_cols;++i)
        //    row_terms[i]=0;
        for(i=1;i<=num_terms;++i)
            ++row_terms[a[i].col];
        starting_pos[0]=1;
        for(i=1;i<num_cols;++i)
            starting_pos[i]=starting_pos[i-1]+row_terms[i-1];
        for(i=1;i<=num_cols;++i){
            j=starting_pos[a[i].col]++;
            b[j].row=a[i].col;
            b[j].col=a[i].row;
            b[j].value=a[i].value;
        }
    }
}