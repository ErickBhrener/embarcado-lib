#include <stdio.h>
#include <stdlib.h>

#ifndef DIE 
#define DIE fprintf(stderr, "Fatal Error:Abort\n");\
	exit(8);
#endif
int main() {
	/* a random value for testing */
	int value;
	value = 1;
	if (value < 0){
		printf("We did not die\n");
	}
	DIE;
	return (0);
}
