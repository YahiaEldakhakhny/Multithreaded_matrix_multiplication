#include "funcs.h"

int main(){
	Matrix k;
	strcpy(k.file_name, "a.txt");
	strcpy(k.prefix, "a");
	k.type = INPUT;

	read_matrix(k, &(k.rows),&(k.cols));
	printf("rows = %d\n", k.rows);
	printf("cols = %d\n", k.cols);
	// printf("col = %d\n", k.cols);

	// int i;
	// while(fscanf(fl, "%d", &i) != EOF){
		// printf("%d\n", i);
	// }

	
	return 0;
}
