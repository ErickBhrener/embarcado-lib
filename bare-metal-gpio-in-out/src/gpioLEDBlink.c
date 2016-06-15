/*
 * =====================================================================================
 *
 *       Filename:  gpioLEDBlink.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/05/2016 12:15:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Francisco Helder (), helderhdw@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "gpioLED.h"
#include "gpioConfig.h"

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define MSEG                           (0x3FFFFFF)

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void Delay(volatile unsigned int count);
int getInput(int pin_number_output,int GPIOModule_output);

/*FUNCTION*-------------------------------------------------------
*
* Function Name : main
* Comments      :
*END*-----------------------------------------------------------*/
int main() {

    /* configure gpio pin for the blue LED control. */
    ledInit(GPIO23,MODULE_1,GPIO12,MODULE_1);

    while(TRUE){
        /* Change the state of the blue LED. */
        if(getInput(GPIO12,MODULE_1)){
            ledToggle(GPIO23,MODULE_1);
        }

        /* Pause for 500 ms */
        Delay(MSEG);

    }

    return(0);
} 

/*FUNCTION*-------------------------------------------------------
*
* Function Name : Delay
* Comments      :
*END*-----------------------------------------------------------*/
static void Delay(volatile unsigned int count){
    while(count--);
      asm("   nop");
}
int getInput(int pin_number_output,int GPIOModule_output){
    int *aux_bitwise = (GPIO_INSTANCE_ADDRESS(GPIOModule_output) + GPIO_DATAIN);
    int bitwise = aux_bitwise;

    if(bitwise & (1 << pin_number_output)){
        return PIN_HIGH;
    }else{
        return PIN_LOW;
    }
}
