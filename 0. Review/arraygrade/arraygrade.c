#include <stdio.h>

#define NUM_STUDENT 4
#define MID_INDEX 0
#define FINAL_INDEX 1
#define SUM_INDEX 2

void calcgrade(int g[][3]);
void printgrade(int g[][3]);

int main(void){
	int grade[][3]={{10,20},{33,35},{13,79},{60,45},{0,0}};

	calcgrade(grade);
	printgrade(grade);

	return 0;
}

void calcgrade(int g[][3]){
	int i, j;
	g[NUM_STUDENT][MID_INDEX]=g[NUM_STUDENT][FINAL_INDEX]=g[NUM_STUDENT][SUM_INDEX]=0;
	for(i=0;i<NUM_STUDENT;++i){
		for(j=0;j<SUM_INDEX;++j)
			g[i][SUM_INDEX]+=g[i][j];
		g[NUM_STUDENT][MID_INDEX]+=g[i][MID_INDEX];
		g[NUM_STUDENT][FINAL_INDEX]+=g[i][FINAL_INDEX];
	}
}

void printgrade(int g[][3]){
	int i, j;
	puts("************************************************");
	printf("%14s%14s%14s\n","MID-TERM","FINAL-TERM","SUM");
	puts("************************************************");
	for(i=0;i<=NUM_STUDENT;++i){
		for(j=0;j<=SUM_INDEX;++j)
			printf("%14d",g[i][j]);
		putchar('\n');
	}
	puts("************************************************");
}