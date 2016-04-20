/*
 * =====================================================================================
 *
 *       Filename:  gpioFunc.c
 *
 *    Description:  gpio function
 *
 *        Version:  1.0
 *        Created:  30/10/2014 08:00 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Benoit François-Marie Christian Roulle
 *        Company:  Fundacao CPqD
 *
 * =====================================================================================
 */

#include "gpioFunc.h"

int initGpio(unsigned int gpio)
{
	char set_value[2]; 
	FILE* fp= NULL;
	//Using sysfs we need to write pin to /sys/class/gpio/export
	//This will create the folder /sys/class/gpio/gpio22

	if ((fp = fopen("/sys/class/gpio/export", "ab")) == NULL)
		{
			printf("Cannot open export file.\n");
			return(-1);
		}
	//Set pointer to begining of the file
	rewind(fp);
	//Write our value of pin to the file
	sprintf(set_value,"%d",gpio);
	fwrite(&set_value, sizeof(char), 2, fp);
	fclose(fp);

	return(0);
}


int releaseGpio(unsigned int gpio)
{
	char set_value[2]; 
	FILE* fp= NULL;
	//Using sysfs we need to write pin to /sys/class/gpio/unexport
	//This will delete the folder /sys/class/gpio/gpio22
	if ((fp = fopen("/sys/class/gpio/unexport", "ab")) == NULL)
		{
			printf("Cannot open unexport file.\n");
			return(-1);
		}
	//Set pointer to begining of the file
	rewind(fp);
	//Write our value of pin to the file
	sprintf(set_value,"%d",gpio);
	fwrite(&set_value, sizeof(char), 2, fp);
	fclose(fp);

	return(0);
}


int gpio_set_dir(unsigned int gpio, unsigned int out_flag)
{
	
	char set_value_out[] = "out";
	
	char set_value_in[] = "in";
	

	char out[3]; 
	char path[100];
	FILE* fp= NULL;
	//Using sysfs we need to write pin to /sys/class/gpio/gpioxx/direction
	//This will create the folder /sys/class/gpio/gpio22
	sprintf(path,"/sys/class/gpio/gpio%d/direction", gpio);
	if ((fp = fopen(path,"ab")) == NULL)
		{
			printf("Cannot open direction file.\n");
			return(-1);
		}
	//Set pointer to begining of the file
	rewind(fp);
	//Write our value of pin to the file

	if (out_flag == 0 )
	{
		fwrite(&set_value_out, sizeof(char), 3, fp);
		fclose(fp);
		printf("out\n");
	}
	else if (out_flag == 1){
		fwrite(&set_value_in, sizeof(char), 2, fp);
		fclose(fp);
		printf("in\n");
    }	
    else{
    	printf("ERRO_FLAG_OUT\n");
    }

	return(0);


}


int gpio_set_value(unsigned int gpio, unsigned int value)
{
	char set_value[3]; 
	char path[40];
	FILE* fp= NULL;
	//Using sysfs we need to write pin to /sys/class/gpio/gpioxx/value
	sprintf(path,"/sys/class/gpio/gpio%d/value", gpio);
	if ((fp = fopen(path,"ab")) == NULL)
		{
			printf("Cannot open value file.\n");
			return(-1);
		}
	//Set pointer to begining of the file
	rewind(fp);
	//Write our value of pin to the file
	sprintf(set_value,"%d",value);
	fwrite(&set_value, sizeof(char), 1, fp);
	fclose(fp);

	return(0);
}


int gpio_get_value(unsigned int gpio, unsigned int *value)
{ 
	char path[40];
	char set_value;
	FILE* fp= NULL;
	//Using sysfs we need to write pin to /sys/class/gpio/gpioxx/value
	sprintf(path,"/sys/class/gpio/gpio%d/value", gpio);
	if ((fp = fopen(path,"rb")) == NULL)
		{
			printf("Cannot open value file.\n");
			return(-1);
		}
	//Set pointer to begining of the file
	rewind(fp);
	//Write our value of pin to the file
	fread(&set_value, sizeof(char), 1, fp);
	fclose(fp);
	*value = set_value - '0';
	return(0); 
}


int gpio_set_edge(unsigned int gpio, char *edge)
{
	return(0);
}


int gpio_fd_open(unsigned int gpio)
{
	return(0);
}


int gpio_fd_close(int fd)
{
	return(0);
}


