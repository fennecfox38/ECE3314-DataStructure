void dgemm (int size, double (*C)[size], double (*A)[size], double (*B)[size]){
	int i, j, k;
	for(i=0;i!=size;++i)
	for(j=0;j!=size;++j)
	for(k=0;k!=size;++k)
		C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
} 