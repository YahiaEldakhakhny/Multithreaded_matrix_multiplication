/*
This code is the work of
Yahia Walid Mohamad Eldakhakhny		19016891
Detailed project description is at:
https://github.com/SajedHassan/Operating-Systems/tree/master/Labs/lab2
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "funcs.h"

// Structs to measure time taken by each method
struct timeval stop_per_mat, start_per_mat;
struct timeval stop_per_row, start_per_row;
struct timeval stop_per_elem, start_per_elem;

// Create matrices A, B, C for different casses
Matrix A, B, C_per_mat, C_per_row, C_per_elem;

// Function executed by threads in per row method
void* multiply_row(void* R);

// Function executed by threads in per element method
void* multiply_elem(void* P);

int main(int argc,char* argv[]){
	A.type = INPUT;
	B.type = INPUT;
	C_per_mat.type = PER_MATRIX;
	C_per_row.type = PER_ROW;
	C_per_elem.type = PER_ELEMENT;

	/*
	If the user provides 3 arguments for the names I will use these arguments
	If the user does not provide any arguments or provides an incomplete set of arguments
	then I will use the defaults
	*/
	if(argc < 4){
		strcpy(A.prefix, "a");
		strcpy(B.prefix, "b");
		strcpy(C_per_mat.prefix, "c");
		strcpy(C_per_row.prefix, "c");
		strcpy(C_per_elem.prefix, "c");
	}
	else{
		strcpy(A.prefix, argv[1]);
		strcpy(B.prefix, argv[2]);
		strcpy(C_per_mat.prefix, argv[3]);
		strcpy(C_per_row.prefix, argv[3]);
		strcpy(C_per_elem.prefix, argv[3]);

	}
	// Get file names of the matrices according to the provided command line arguments or default values
	get_file_name(A, A.file_name);
	get_file_name(B, B.file_name);
	get_file_name(C_per_mat, C_per_mat.file_name);
	get_file_name(C_per_row, C_per_row.file_name);
	get_file_name(C_per_elem, C_per_elem.file_name);

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

	// If user provides incompatibel matrix size
	if(A.cols != B.rows){
		printf("Incompatible Matrix sizes\n");
		exit(-1);
	}
	
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

	printf("A thread per matrix:\n");
    printf("Seconds taken: %lu\n", stop_per_mat.tv_sec - start_per_mat.tv_sec);
    printf("Microseconds taken: %lu\n", stop_per_mat.tv_usec - start_per_mat.tv_usec);
	printf("1 Thread needed\n");
	
	// write matrix to txt file
	write_mat(C_per_mat);

	/** Multiply A and B using A thread per row **/
	// Allocate space in C_per_row
	C_per_row.rows = A.rows;
	C_per_row.cols = B.cols;
	C_per_row.mat = malloc(sizeof(int*) * C_per_row.rows);
	for(int i = 0; i < C_per_row.rows; i++){
		C_per_row.mat[i] = malloc(sizeof(int) * C_per_row.cols);
	}

	// Number of threads = number of rows in C_per_row
	pthread_t threads_arr_row[C_per_row.rows];
	int res;
	// Number of rows must be stored in an array to allow each thread to read the correct number
	int nums[C_per_row.rows];
	//start checking time
	gettimeofday(&start_per_row, NULL);

	// Run threads
	for(int i = 0; i < C_per_row.rows; i++){
		nums[i] = i;
		res = pthread_create(&threads_arr_row[i], NULL, multiply_row, (void*) &nums[i]);
		if(res){
			printf("ERROR\n");
			exit(-1);
		}
	}
	// Wait for threads to join
	for(int j = 0; j < C_per_row.rows; j++){
		if(pthread_join(threads_arr_row[j], NULL)){
			printf("Error joining threads\n");
			exit(-1);
		}
	}

	//end checking time
    gettimeofday(&stop_per_row, NULL);
	// Get time of execution
	printf("A thread per row:\n");
    printf("Seconds taken (per row) %lu\n", stop_per_row.tv_sec - start_per_row.tv_sec);
    printf("Microseconds taken (per row): %lu\n", stop_per_row.tv_usec - start_per_row.tv_usec);
	printf("%d Threads created\n", C_per_row.rows);	
	// write matrix to txt file
	write_mat(C_per_row);



	/** Multiply A and B using A thread per element **/
	// Allocate space in C_per_elem
	C_per_elem.rows = A.rows;
	C_per_elem.cols = B.cols;
	C_per_elem.mat = malloc(sizeof(int*) * C_per_elem.rows);
	for(int i = 0; i < C_per_elem.rows; i++){
		C_per_elem.mat[i] = malloc(sizeof(int) * C_per_elem.cols);
	}

	// Number of threads = number of elements in C_per_elem
	pthread_t threads_arr_elem[C_per_elem.rows][C_per_elem.cols];
	// Positions of elements must be stored so each thread can access its target position
	int positions[C_per_elem.rows][C_per_elem.cols][2];
	//start checking time
	gettimeofday(&start_per_elem, NULL);


	// Run threads
	for(int i = 0; i < C_per_elem.rows; i++){
		for(int j = 0; j < C_per_elem.cols; j++){
			positions[i][j][0] = i;
			positions[i][j][1] = j;
			res = pthread_create(&threads_arr_elem[i][j], NULL, multiply_elem, (void*) positions[i][j]);
			if(res){
				printf("ERROR\n");
				exit(0);
			}
			
		}
	}
	// Wait for threads to join
	for(int k = 0; k < C_per_elem.rows; k++){
		for(int l = 0; l < C_per_elem.cols; l++){
			if(pthread_join(threads_arr_elem[k][l], NULL)){
				printf("Error joining threads\n");
				exit(-1);
			}		
		}
	}
	
	//end checking time
    gettimeofday(&stop_per_elem, NULL);
	// Get time of execution
	printf("A Thread per Element:\n");
    printf("Seconds taken (per element) %lu\n", stop_per_elem.tv_sec - start_per_elem.tv_sec);
    printf("Microseconds taken (per element): %lu\n", stop_per_elem.tv_usec - start_per_elem.tv_usec);
	printf("%d Threads created\n", C_per_elem.cols * C_per_elem.rows);
	// write matrix to txt file
	write_mat(C_per_elem);

	/* Free allocated space */
	// Matrix A
	for(int i = 0; i < A.rows; i++){
		free(A.mat[i]);
	}
	free(A.mat);

	// Matrix B
	for(int i = 0; i < B.rows; i++){
		free(B.mat[i]);
	}
	free(B.mat);

	// Matrix C_per_mat
	for(int i = 0; i < C_per_mat.rows; i++){
		free(C_per_mat.mat[i]);
	}
	free(C_per_mat.mat);

	// Matrix C_per_row
	for(int i = 0; i < C_per_row.rows; i++){
		free(C_per_row.mat[i]);
	}
	free(C_per_row.mat);

	// Matrix C_per_elem
	for(int i = 0; i < C_per_elem.rows; i++){
		free(C_per_elem.mat[i]);
	}
	free(C_per_elem.mat);
	
	
	return 0;
}
/**************** END OF MAIN ****************/


// Function executed by threads in per row method
void* multiply_row(void* R){
	int trgt_row = *((int*) R);
	int sum = 0;
	for(int i = 0; i < C_per_row.cols; i++){
		sum = 0;
		for(int j = 0; j < A.cols; j++){
			sum += A.mat[trgt_row][j] * B.mat[j][i];
		}
		C_per_row.mat[trgt_row][i] = sum;
	}
	return NULL;
}


// Function executed by threads in per row method
void* multiply_elem(void* P){
	int* pos = (int*) P;
	int r = pos[0], c = pos[1];
	int sum = 0;
	for(int i = 0; i < A.cols; i++){
		sum += A.mat[r][i] * B.mat[i][c];
	}
	C_per_elem.mat[r][c] = sum;
	return NULL;
}
