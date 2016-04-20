#include "gpioLib.h"

int setGpio(unsigned int gpio){

	char gpio_value[2];

	FILE* fp= NULL;

	if((fp = fopen("/sys/class/gpio/export","ab"))==NULL){
		printf("Can't open 'export' file. \n");
		return (-1);
	}

	rewind(fp);
	//It will write the gpio value inside of the char sequence
	sprintf(gpio_value,"%d",gpio);
	//It will write out the char sequence into the file
	fwrite(&gpio_value,sizeof(char),3, fp);

	fclose(fp);

	return (0);

}

int release_gpio(unsigned int gpio){
	char gpio_value[2];

	FILE* fp= NULL;

	if((fp = fopen("/sys/class/gpio/unexport","ab"))==NULL){
		printf("Can't open 'export' file. \n");
		return (-1);
	}

	rewind(fp);
	//It will write the gpio value inside of the char sequence
	sprintf(gpio_value,"%d",gpio);
	//It will write out the char sequence into the file
	fwrite(&gpio_value,sizeof(char),3, fp);

	fclose(fp);

	return (0);

}

int set_gpio_dir(unsigned int gpio, unsigned int flag){
	char out_value[] = "out";
	char in_value[] = "in";

	char path[100];

	FILE* fp = NULL;

	sprintf(path,"/sys/class/gpio/gpio%d/direction",gpio);
	if((fp = fopen(path,"ab"))==NULL){
		printf("Can't open 'direction' file. \n");
		return(-1);
	}

	rewind(fp);

	if(flag==0){
		fwrite(&out_value, sizeof(char), 3, fp);
		fclose(fp);
		printf("'Out' value signed. \n");
	}else if(flag==1){
		fwrite(&in_value, sizeof(char), 2, fp);
		fclose(fp);
		printf("'In' value signed. \n");
	}else{
		printf("Flag unavailable or wrong value. \n");
	}

	return(0);
}

int set_gpio_value(unsigned int gpio, unsigned int value){
	char set_value[3];
	char path[100];
	FILE* fp = NULL;
	sprintf(path,"/sys/class/gpio/gpio%d/value",gpio);
	if((fp=fopen(path,"ab"))==NULL){
		printf("Can't open 'value' file.\n");
		return(-1);
	}
	rewind(fp);
	sprintf(set_value,"%d", value);
	fwrite(&set_value,sizeof(char), 1, fp);
	fclose(fp);
	return(0);
}

