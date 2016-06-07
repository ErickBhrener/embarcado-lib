#include <stdio.h>

#define DIV_DEZ(numero) ((numero) % 10 ==0)

int main(){
	int numero =0;
	printf("Digite um número: \n");
	scanf("%d",&numero);
	if(DIV_DEZ(numero)){
		printf("%d é divisivel por 10! \n", numero);
	}else{
		printf("Não é divisivel por 10 \n");
	}
}
