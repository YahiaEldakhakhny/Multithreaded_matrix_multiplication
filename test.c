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

	Matrix y = k;
	strcpy(y.prefix, "y");
	y.type = OUTPUT | PER_ROW;
	get_file_name(y, y.file_name);

	write_mat(y);
	return 0;
}
