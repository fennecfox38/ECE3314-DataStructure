#include <stdio.h>
#include "term.h"

void initSparse(int row, int col, int m[][col], term *sparse);
void printSparse(term a[]);

int main(void){
    int m[6][6]={
        {15, 0, 0, 22, 0, -15},
        {0, 11, 3, 0, 0, 0},
        {0, 0, 0, -6, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {91, 0, 0, 0, 0, 0},
        {0, 0, 28, 0, 0, 0}
    };
    term sparse[MAX_TERMS];
    term result[MAX_TERMS];

    initSparse(6,6,m,sparse);
    printSparse(sparse);

    transpose(sparse,result);
    printSparse(result);

    fast_transpose(sparse,result);
    printSparse(result);
}

void initSparse(int rows, int cols, int m[][cols], term *sparse){
    int i, j, k=0;
    sparse[0].row=rows;
    sparse[0].col=cols;
    for(i=0;i<sparse[0].row;++i){
        for(j=0;j<sparse[0].col;++j){
            if(m[i][j]){
                sparse[++k].row=i;
                sparse[k].col=j;
                sparse[k].value=m[i][j];
            }
        }
    }
    sparse[0].value=k;
}

void printSparse(term sparse[]){
    int i;
    printf("%6s : %7s %7s %7s\n","index","row","col","value");
    for(i=0;i<=sparse[0].value;++i)
        printf("%6d : %7d %7d %7d\n",i,sparse[i].row,sparse[i].col,sparse[i].value);
}
