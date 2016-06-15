#ifndef GPIOCONFIG_H_
#define GPIOCONFIG_H_

#include "gpioLED.h"

void GPIO0_ModuleClkConfig(void);
void GPIO1_ModuleClkConfig(void);
void GPIO2_ModuleClkConfig(void);
void GPIO3_ModuleClkConfig(void);

void ConfigGPIOClkModule(int module_clk);

void ConfigModule_0(int pin_number);
void ConfigModule_1(int pin_number);
void ConfigModule_2(int pin_number);
void ConfigModule_3(int pin_number);

void referenceTo_UART(int pin_number);
void referenceTo_GPMC_CSN(int pin_number);

#endif //GPIOCONFIG_H_