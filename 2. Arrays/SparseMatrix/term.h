#define MAX_TERMS 101
typedef struct{
    int col;
    int row;
    int value;
} term;

// a[0].row: the number of rows
// a[0].col: the number of cols
// a[0].value: the number of non-zero values

void transpose(term a[], term b[]);
void fast_transpose(term a[], term b[]);