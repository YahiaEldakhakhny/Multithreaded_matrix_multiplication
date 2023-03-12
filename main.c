#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "funcs.h"

// Structs to measure time taken by each method
struct timeval stop_per_mat, start_per_mat;

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

	/** Read data of matrix A **/
	// get number of rows and columns
	get_rc(A, &(A.rows), &(A.cols));
	// Allocate memory for matrix
	A.mat = malloc(sizeof(int*) * A.rows);
	for(int i = 0; i < A.rows; i++){
		A.mat[i] = malloc(sizeof(int) * A.cols);
	}

	populate_matrix(A);

	/** Read data of matrix B **/
	// get number of rows and columns
	get_rc(B, &(B.rows), &(B.cols));
	// Allocate memory for matrix
	B.mat = malloc(sizeof(int*) * B.rows);
	for(int i = 0; i < B.rows; i++){
		B.mat[i] = malloc(sizeof(int) * B.cols);
	}

	populate_matrix(B);


	/** Multiply A and B using 1 thread **/
	// Allocate space in C_per_matrix
	C_per_mat.rows = A.rows;
	C_per_mat.cols = B.cols;
	C_per_mat.mat = malloc(sizeof(int*) * C_per_mat.rows);
	for(int i = 0; i < C_per_mat.rows; i++){
		C_per_mat.mat[i] = malloc(sizeof(int) * C_per_mat.cols);
	}

	// Multiply A and B
    gettimeofday(&start_per_mat, NULL); //start checking time

	for (int i = 0; i < C_per_mat.rows; i++) {
		for (int j = 0; j < C_per_mat.cols; j++) {
			C_per_mat.mat[i][j] = 0;
			for (int k = 0; k < B.rows; k++) {
				C_per_mat.mat[i][j] += A.mat[i][k] * B.mat[k][j];
			}
		}
	}

    gettimeofday(&stop_per_mat, NULL); //end checking time

    printf("Seconds taken (per matrix) %lu\n", stop_per_mat.tv_sec - start_per_mat.tv_sec);
    printf("Microseconds taken (per matrix): %lu\n", stop_per_mat.tv_usec - start_per_mat.tv_usec);



	return 0;
}
