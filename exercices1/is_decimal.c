#include <stdio.h>

#define is_digit(x) ( ((x)=='0') || ((x)=='1') || ((x)=='2') || ((x)=='3') \
	|| ((x)=='4') || ((x)=='5') || ((x)=='6') || ((x)=='7') \
	|| ((x)=='8') || ((x)=='9') )

int main(){
	char input =0;
	printf("Digite a entrada: \n");
	scanf("%c",&input);
	if(is_digit(input)){
		printf("%d é um digito! \n", input);
	}else{
		printf("Não é um digito \n");
	}
}
