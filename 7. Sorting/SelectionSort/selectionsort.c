# include <stdio.h>

void swap (int *a, int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void selectionSort(int array[], int size){
    for(int step=0;step<size-1;++step){
        int min_idx=step;
        for(int i=step+1;i<size;++i)
            if(array[i]<array[min_idx])
                min_idx=i;
        swap(array+min_idx,array+step);
    }
}

void printArray(int array[], int size){
    for(int i=0; i<size; ++i)
        printf("%d ",array[i]);
    putchar('\n');
}

int main(void){
    int size=5, array[]={20,12,10,15,2};
    fputs("Before sorting: ",stdout);
    printArray(array,size);

    selectionSort(array,size);
    fputs("After sorting: ",stdout);
    printArray(array,size);
    return 0;
}