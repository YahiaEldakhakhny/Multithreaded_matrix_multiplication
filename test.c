#include "funcs.h"

int main(){
	Matrix k;
	strcpy(k.file_name, "a.txt");
	strcpy(k.prefix, "a");
	k.type = INPUT;

	// Get number of rows and columns
	get_rc(k, &(k.rows),&(k.cols));
	printf("rows = %d\n", k.rows);
	printf("cols = %d\n", k.cols);

	// allocate memory for matrix
	k.mat = malloc(sizeof(int*) * k.rows);
	for(int i = 0; i < k.rows; i++){
		k.mat[i] = malloc(sizeof(int) * k.cols);
	}

	populate_matrix(k);

	for(int r = 0; r < k.rows; r++){
		printf("row #%d", r);
		for(int c = 0; c < k.cols; c++){
			printf("%d ", k.mat[r][c]);
		}
		printf("\n");
	}
	return 0;
}
