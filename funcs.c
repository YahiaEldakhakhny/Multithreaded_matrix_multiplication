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


// Function to read data of a matrix from a txt file
void read_matrix(Matrix m, int* r, int* c){
	// Get number of rows and cols
	m.file_ptr = fopen(m.file_name, "r");
	fscanf(m.file_ptr, "row=%d col=%d", r, c);


	fclose(m.file_ptr);
}




