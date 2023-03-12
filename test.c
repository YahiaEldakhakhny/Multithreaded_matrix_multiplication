#include "funcs.h"

int main(){
	// Matrix k;
	// strcpy(k.file_name, "a.txt");
	// strcpy(k.prefix, "a");
	// k.type = INPUT;
// 
	// read_matrix(k, &(k.rows),&(k.cols));
	// printf("rows = %d\n", k.rows);
	// printf("cols = %d\n", k.cols);
	// printf("col = %d\n", k.cols);

	// int i;
	// while(fscanf(fl, "%d", &i) != EOF){
		// printf("%d\n", i);
	// }

	int r=2, c=3;
	printf("defined r, c\n");
	int** mat;
	printf("defined mat\n");
	mat = malloc(sizeof(int*) * r);
	for(int l =0; l< r; l++){
		mat[l] = malloc(sizeof(int) * c);
	}
	printf("Allocation loop done\n");
	int arr[] = {3, 4, 5, 17, -1, 9};
	printf("defined 1d arr\n");
	array_to_matrix(mat, arr, r, c);
	for(int j =0; j<r; j++){
		printf("row #%d: ", j);
		for(int g = 0; g<c; g++){
			printf("%d", mat[j][g]);
		}
		printf("\n");
	}
	free(mat);
	return 0;
}
