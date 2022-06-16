# include <stdio.h>

void swap (int *a, int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void quickSort(int array[], int low, int high){
    if(low>=high) return;
    int pivot=array[high];
    int i=low-1;
    for(int j=low;j<high;++j)
        if(array[j]<=pivot)
            swap(array+(++i),array+j);
    swap(array+(++i),array+high);

    quickSort(array, low, i-1);
    quickSort(array, i+1, high);
}

void printArray(int array[], int size){
    for(int i=0; i<size; ++i)
        printf("%d ",array[i]);
    putchar('\n');
}

int main(void){
    int size=7, array[]={8,7,6,1,0,9,2};
    fputs("Before sorting: ",stdout);
    printArray(array,size);

    quickSort(array,0, size-1);
    fputs("After sorting: ",stdout);
    printArray(array,size);
    return 0;
}