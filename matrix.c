#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

int main(void){

    srand((unsigned)time(NULL));
    int n, sum = 0;
    printf("Enter a period: ");
    scanf("%d", &n);
    int **period = (int**)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++){
	printf("\n");
	*(period+i) = (int *)malloc(n * sizeof(int));
	for (int j = 0; j < n; j++){
	    *(*(period + i) + j) = rand() % 100;
	    printf("%-3d ", *(*(period + i) + j));
	}
    }
    printf("\n>----------------------------------------------<");
    for (int i = 0; i < n; i++){
	if (n % 2 == 1){
	    if (i == n/2){
		sum += *(*(period + i) + i); 
		continue;
	    }
	}
	int temp = *(*(period + i) + i);
	*(*(period + i) + i) = *(*(period + i) + (n-1-i)); 
	*(*(period + i) + (n-1-i)) = temp;
	sum += *(*(period + i) + i) + *(*(period + i) + (n-1-i));
    }
    for (int i = 0; i < n; i++){
	printf("\n");
	for (int j = 0; j < n; j++){
	    printf("%-3d ", *(*(period + i) + j));
	}
    }
    printf("\nSum is %d", sum);
    return 0;
}

