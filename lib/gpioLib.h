#ifndef GPIOLIB_H_
#define GPIOLIB_H_


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define OUT 0
#define IN 1


int setGpio(unsigned int gpio);
int release_gpio(unsigned int gpio);
int set_gpio_dir(unsigned int gpio, unsigned int flag);
int set_gpio_value(unsigned int gpio, unsigned int value);

#endif /* GPIOLIB_H_*/
