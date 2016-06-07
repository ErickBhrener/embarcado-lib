#include <stdio.h>

#define SWAP(x,y) (y)=(x)+(y);(x)=(y)-(x);(y)=(y)-(x);

int main(void) {

	int x ,y = 0;
	printf("Digite dois numeros: \n");
	scanf("%d %d",&x, &y);
	printf("x=%d y=%d\n", x, y);
	SWAP(x,y)
	printf("Resultado x=%d y=%d\n", x, y);
	return(0);
}
