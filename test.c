#include "funcs.h"

int main(){
	Matrix k;
	strcpy(k.file_name, "a.txt");
	strcpy(k.prefix, "a");
	k.type = OUTPUT | PER_MATRIX;

	printf("%d\n", k.type);
	return 0;
}
