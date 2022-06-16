#define SIZE 4
#include <stdio.h>
void dgemm (int size, double (*C)[size], double (*A)[size], double (*B)[size]);
void printM (int size, double **matrix){
	double **p1, **p2;
	putchar('{');
	for(p1=matrix+(size*size);matrix<p1;){
		printf("\n\t{ ");
		for(p2=matrix+size;matrix<p2;++matrix)
			printf("%lf, ",*((double*)matrix));
		printf("\b\b },");
	}
	printf("\b \n}\n");
}
int main(void){
	double A[SIZE][SIZE]= { { 1.0, 2.0, 3.0, 4.0 },
				{ 5.0, 6.0, 7.0, 8.0 },
				{ 9.0, 10.0, 11.0, 12.0},
				{ 13.0, 14.0, 15.0, 16.0} };
	double B[SIZE][SIZE]= { { -1.0, -2.0, -3.0, -4.0 },
				{ -5.0, -6.0, -7.0, -8.0 },
				{ -9.0, -10.0, -11.0, -12.0},
				{ -13.0, -14.0, -15.0, -16.0} };
	double C[SIZE][SIZE]= { { 0.0, 0.0, 0.0, 0.0 },
				{ 0.0, 0.0, 0.0, 0.0 },
				{ 0.0, 0.0, 0.0, 0.0 },
				{ 0.0, 0.0, 0.0, 0.0 } };
	printM(SIZE,(double**)A);
	printM(SIZE,(double**)B);
	dgemm(SIZE, C, A, B);
	printM(SIZE,(double**)C);
	return 0;
}
