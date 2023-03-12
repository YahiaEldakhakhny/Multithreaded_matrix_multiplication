#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "funcs.h"

// Create 3 matrices A, B, C
Matrix A, B, C_per_mat;


int main(int argc,char* argv[]){
	A.type = INPUT;
	B.type = INPUT;
	C_per_mat.type = OUTPUT | PER_MATRIX;
	
	// Get file names from input arguments and set default file names
	if(argc < 4){
		strcpy(A.prefix, "a");
		strcpy(B.prefix, "b");
		strcpy(C_per_mat.prefix, "c");
	}
	else{
		strcpy(A.prefix, argv[1]);
		strcpy(B.prefix, argv[2]);
		strcpy(C_per_mat.prefix, argv[3]);

	}
	get_file_name(A, A.file_name);
	get_file_name(B, B.file_name);
	get_file_name(C_per_mat, C_per_mat.file_name);

	printf("A file_name is %s\n", A.file_name);
	printf("B file_name is %s\n", B.file_name);
	printf("C file_name is %s\n", C_per_mat.file_name);

	
	




	return 0;
}
