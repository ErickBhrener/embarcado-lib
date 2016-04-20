#include <stdio.h>
#include "gpioLib.h"
#include <time.h>

void delay(int intervalo){
	usleep(100000 * intervalo);
}

void menu(){
	printf("***********__Menu__************\n");
	printf("1 - one led by time\n");
	printf("2 - both leds by time\n");
	printf("3 - toggle/alternate between leds\n");
	printf(" -1 to get out of here\n");
	printf("*******************************\n");
}

int main(void)
{
	//building gpio files and properties
	/* 101 */
	/* 90 */
	//end of build
	
	time_t start, end;
	double time_left= 0.0;
	int option = 0, pino=0;
	int intervalo = 3;
	while(option != -1){
		printf("Escolha o número do pino.\n");
		scanf("%d",&pino);
		setGpio(pino);
		set_gpio_dir(pino,0);
		setGpio(44);
		set_gpio_dir(44,0);
		time_left = 0.0;
		time(&start);
		printf("Defina o intervalo:\n");
		scanf("%d",&intervalo);
		do{
			time(&end);
			time_left=difftime(end,start);
	    		set_gpio_value(pino,1);
	    		set_gpio_value(44,1);
	    		delay(intervalo);
	    		set_gpio_value(pino,0);
	    		set_gpio_value(44,0);
	    		delay(intervalo);
		}while(time_left<60);
	}
		/*switch(option) {

			case 1:
				time(&start);
				printf("Defina o pino: \n");
				scanf("%d",&intervalo);
				do{
					time(&end);
					time_left=difftime(end,start);
	    	 		set_gpio_value(intervalo,1);
	    	 		delay(8);
	    	 		set_gpio_value(intervalo,0);
	    	 		delay(8);
				}while(time_left<15);
	      		break;
		
	   		case 2:
	      		time(&start);
				printf("Defina o intervalo: \n");
				scanf("%d",&intervalo);
				do{
					time(&end);
					time_left=difftime(end,start);
	    	 		set_gpio_value(101,1);
	    	 		set_gpio_value(90,1);
	    	 		delay(intervalo);
	    	 		set_gpio_value(101,0);
	    	 		set_gpio_value(90,0);
	    	 		delay(intervalo);
				}while(time_left<20);
	      		break;
	  		case 3:
	  			time(&start);
				do{
					time(&end);
					time_left=difftime(end,start);
	    	 		set_gpio_value(101,1);
	    	 		delay(3);
	    	 		set_gpio_value(101,0);
	    	 		delay(3);
	    	 		set_gpio_value(90,1);
	    	 		delay(3);
	    	 		set_gpio_value(90,0);
	    	 		delay(3);
				}while(time_left<30);
	      		break;
	  			break;
	   		default :
	   			break;
		}*/
	return 0;
}
