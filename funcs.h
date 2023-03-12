#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define WORD_SIZE 32
#define INPUT 0
#define OUTPUT 0b0001
#define PER_MATRIX 0b0010
#define PER_ROW 0b0100
#define PER_ELEMENT 0b1000

#define IS_OUTPUT(TYPE) TYPE & OUTPUT
#define IS_PER_MATRIX(TYPE) TYPE & PER_MATRIX
#define IS_PER_ROW(TYPE) TYPE & PER_ROW
#define IS_PER_ELEMENT(TYPE) TYPE & PER_ELEMENT

// struct to store all data related to a matrix
typedef struct{
	char file_name[WORD_SIZE];
	char prefix[WORD_SIZE];
	FILE* file_ptr;
	int** mat;
	int rows, cols;
	int type; // type of a matrix indicate if its input or output, and if output then which method
} Matrix;


// Function to generate the file name of a matrix
void get_file_name(Matrix m, char file_name[]);

// Function to read data of a matrix from a txt file
void read_matrix(Matrix m, int* r, int* c);