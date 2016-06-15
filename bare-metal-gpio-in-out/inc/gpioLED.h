#ifndef GPIOLED_H_
#define GPIOLED_H_

/*
 * =====================================================================================
 *
 *       Filename:  gpioLED.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  19/05/2016 20:03:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Francisco Helder (), helderhdw@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "hw_control_AM335x.h"
#include "soc_AM335x.h"
#include "hw_cm_wkup.h"
#include "hw_gpio_v2.h"
#include "beaglebone.h"
#include "hw_cm_per.h"
#include "hw_types.h"
#include "gpioConfig.h"


/* This is used to configure a GPIO pin as an input pin. */
#define DIR_INPUT                1
/* This is used to configure a GPIO pin as an output pin.*/
#define DIR_OUTPUT               0

/* This is used to write a logic 0 to a pin.*/
#define PIN_LOW                  0

/* This is used to write a logic 1 to a pin.*/
#define PIN_HIGH                 1

#define GPIO_INSTANCE_ADDRESS(n)	( (n==0) ? SOC_GPIO_0_REGS : (n==1) ? SOC_GPIO_1_REGS : (n==2) ? SOC_GPIO_2_REGS: SOC_GPIO_3_REGS)
#define GPIO_INSTANCE_PIN_NUMBER        (23)
#define TOGGLE                          (0x01u)

/* Enumera os possiveis modulos para utilização*/
enum module_clk {MODULE_0,MODULE_1,MODULE_2,MODULE_3} module_clk;

enum pin_reference {GPIO0, GPIO1, GPIO2, GPIO3, GPIO4, GPIO5, GPIO6, GPIO7,
					GPIO8, GPIO9, GPIO10, GPIO11, GPIO12, GPIO13, GPIO14, GPIO15,
					GPIO16, GPIO17, GPIO18, GPIO19, GPIO20, GPIO21, GPIO22, GPIO23,
					GPIO24, GPIO25, GPIO26, GPIO27, GPIO28, GPIO29, GPIO30, GPIO31} pin_reference;

int ledInit(int pin_number_to_out, int pin_number_to_in, int GPIOModule_to_out, int GPIOModule_to_in);
void ledToggle(int pin_number, int GPIOModule);
void GPIOPinMuxSetup(unsigned int offsetAddr, unsigned int padConfValue);
void GPIOPinMuxSetupInput(unsigned int offsetAddr, unsigned int padConfValue);
void GPIOModuleEnable(unsigned int baseAdd);
void GPIOModuleReset(unsigned int baseAdd);
void GPIODirModeSet(unsigned int baseAdd, unsigned int pinNumber, unsigned int pinDirection);
void GPIOPinWrite(unsigned int baseAdd, unsigned int pinNumber, unsigned int pinValue);




#endif //GPIOLED_H_
