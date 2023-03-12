#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "funcs.h"


// Function to generate the file name of a matrix
void get_file_name(Matrix m, char file_name[]){
	// Buffer to store file name
	char fn[WORD_SIZE];
	strcpy(fn, m.prefix);

	if(IS_OUTPUT(m.type)){
		if(IS_PER_MATRIX(m.type)){
			strcat(fn, "_per_matrix");
		}
		else if(IS_PER_ROW(m.type)){
			strcat(fn, "_per_row");
		}
		else if(IS_PER_ELEMENT(m.type)){
			strcat(fn, "_per_element");
		}
	}
	
	strcat(fn, ".txt");
	strcpy(file_name, fn);
}

// Function to convert 1D array to a 2D matrix
// matrix size must be pre-allocated
void array_to_matrix(int** matrix, int *arr, int row, int col){
	// put each element in its place	
    int i,j,k=0;     
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            matrix[i][j] = arr[k];
            k++;
        }
    }
}


// Function to get number of rows and columns from a txt file
void get_rc(Matrix m, int* r, int* c){
	// Get number of rows and cols
	m.file_ptr = fopen(m.file_name, "r");
	fscanf(m.file_ptr, "row=%d col=%d", r, c);

	fclose(m.file_ptr);
}

void populate_matrix(Matrix m){
	// Open file to read values
	m.file_ptr = fopen(m.file_name, "r");
	// skip first line in file
	int temp1, temp2;
	fscanf(m.file_ptr, "row=%d col=%d", &temp1, &temp2);

	// get matrix elements in 1d array
	m.elem = malloc(sizeof(int) * m.rows * m.cols);
	int i = 0, e;
	while(fscanf(m.file_ptr, "%d", &e) != EOF){
		m.elem[i] = e;
		i++;
	}
	//Put elements in matrix
	array_to_matrix(m.mat, m.elem, m.rows, m.cols);

	fclose(m.file_ptr);
}

// Function to print the elements of a matrix
void print_mat(Matrix m){
	for(int i = 0; i < m.rows; i++){
		for(int j = 0; j < m.cols; j++){
			printf("%d ", m.mat[i][j]);
		}
		printf("\n");
	}
}


// Function to write a matrix to a txt file
void write_mat(Matrix y){
	// get the name of the method
	char method[LINE_SIZE];
	if(IS_PER_MATRIX(y.type)){
		strcpy(method, "A thread per matrix");
	}
	else if(IS_PER_ROW(y.type)){
		strcpy(method, "A thread per row");		
	}
	else if(IS_PER_ELEMENT(y.type)){
		strcpy(method, "A thread per element");	
	}
	else{
		strcpy(method, "Unkown method");
	}


	
	// open file in write mode
	y.file_ptr = fopen(y.file_name, "w");
	// write the method of the matrix
	fprintf(y.file_ptr, "Method: %s\n", method);
	// write the dimensions of the matrix
	fprintf(y.file_ptr, "row=%d col=%d\n", y.rows, y.cols);
	// write elements of the matrix
	for(int i = 0; i < y.rows; i++){
		for(int j = 0; j < y.cols; j++){
			fprintf(y.file_ptr, "%d ", y.mat[i][j]);
		}
		fprintf(y.file_ptr, "\n");
	}
	fclose(y.file_ptr);
	
}
