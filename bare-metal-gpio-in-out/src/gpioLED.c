/*
 * =====================================================================================
 *
 *       Filename:  gpioLED.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  19/05/2016 20:01:58
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
int flagToggle=0x0;
/*FUNCTION*-------------------------------------------------------
*
* Function Name : GPIOPinMuxSetup
* Comments      : This function does the pin multiplexing for any GPIO Pin.
*
* \param  offsetAddr   This is the offset address of the Pad Control Register
*                      corresponding to the GPIO pin. These addresses are
*                      offsets with respect to the base address of the
*                      Control Module.
* \param  padConfValue This is the value to be written to the Pad Control
*                      register whose offset address is given by 'offsetAddr'.
*
* The 'offsetAddr' and 'padConfValue' can be obtained from macros defined
* in the file 'include/armv7a/am335x/pin_mux.h'.\n
*END*-----------------------------------------------------------*/
void GPIOPinMuxSetup(unsigned int offsetAddr, unsigned int padConfValue){
    HWREG(SOC_CONTROL_REGS + offsetAddr) = (padConfValue);
}

void GPIOPinMuxSetupInput(unsigned int offsetAddr, unsigned int padConfValue){
    HWREG(SOC_CONTROL_REGS + offsetAddr) = (padConfValue);
    HWREG(SOC_CONTROL_REGS + offsetAddr) |= CONTROL_CONF_GPMC_AD12_CONF_GPMC_AD12_RXACTIVE;
    HWREG(SOC_CONTROL_REGS + offsetAddr) &= ~(CONTROL_CONF_GPMC_AD12_CONF_GPMC_AD12_PUTYPESEL);
    HWREG(SOC_CONTROL_REGS + offsetAddr) &= ~(CONTROL_CONF_GPMC_AD12_CONF_GPMC_AD12_PUDEN);
    
}

/*FUNCTION*-------------------------------------------------------
*
* Function Name : SPIOModuleEnable 
* Comments      : This API is used to enable the GPIO module. When 
* the GPIO module is enabled, the clocks to the module are not gated.
*
* \param  baseAdd    The memory address of the GPIO instance being used
*END*-----------------------------------------------------------*/
void GPIOModuleEnable(unsigned int baseAdd){
    HWREG(baseAdd + GPIO_CTRL) &= ~(GPIO_CTRL_DISABLEMODULE);
}

/*FUNCTION*-------------------------------------------------------
*
* Function Name : SPIOModuleEnable 
* Comments      : This API performs the module reset of the GPIO 
* module. It also waits until the reset process is complete.
*
* \param  baseAdd    The memory address of the GPIO instance being used
*END*-----------------------------------------------------------*/
void GPIOModuleReset(unsigned int baseAdd){
    HWREG(baseAdd + GPIO_SYSCONFIG) |= (GPIO_SYSCONFIG_SOFTRESET);
}

/*FUNCTION*-------------------------------------------------------
*
* Function Name : GPIODirModeSet
* Comments      : This API configures the direction of a specified 
* GPIO pin as being either input or output.
*
* \param  baseAdd       The memory address of the GPIO instance being used
* \param  pinNumber     The number of the pin in the GPIO instance
* \param  pinDirection  The required direction for the GPIO pin
*
* 'pinNumber' can take one of the following values:
* (0 <= pinNumber <= 31)\n
*
* 'pinDirection' can take one of the following values:
* - GPIO_DIR_INPUT - to configure the pin as an input pin\n
* - GPIO_DIR_OUTPUT - to configure the pin as an output pin\n
*END*-----------------------------------------------------------*/
void GPIODirModeSet(unsigned int baseAdd,
                            unsigned int pinNumber,
                            unsigned int pinDirection) {
    /* Checking if pin is required to be an output pin. */
    if(DIR_OUTPUT == pinDirection){
        HWREG(baseAdd + GPIO_OE) &= ~(1 << pinNumber);
    }else{
        HWREG(baseAdd + GPIO_OE) |= (1 << pinNumber);
    }
}

/*FUNCTION*-------------------------------------------------------
*
* Function Name : GPIOPinWrite
* Comments      : This API drives an output GPIO pin to a logic 
* HIGH or a logic LOW state.
*
* \param  baseAdd     The memory address of the GPIO instance being used
* \param  pinNumber   The number of the pin in the GPIO instance
* \param  pinValue    This specifies whether a logic HIGH or a logic LOW
*                     should be driven on the output pin
*
* 'pinNumber' can take one of the following values:
* (0 <= pinNumber <= 31)\n
*
* 'pinValue' can take one of the following values:
* - GPIO_PIN_LOW - indicating to drive a logic LOW(logic 0) on the pin.
* - GPIO_PIN_HIGH - indicating to drive a logic HIGH(logic 1) on the pin.
*END*-----------------------------------------------------------*/
void GPIOPinWrite(unsigned int baseAdd,
                            unsigned int pinNumber,
                            unsigned int pinValue) {

    if(PIN_HIGH == pinValue){
        HWREG(baseAdd + GPIO_SETDATAOUT) = (1 << pinNumber);
    }else{
        HWREG(baseAdd + GPIO_CLEARDATAOUT) = (1 << pinNumber);
    }
}
/*FUNCTION*-------------------------------------------------------
*
* Function Name : ledInit
* Comments      :
*END*-----------------------------------------------------------*/
int ledInit(int pin_number_to_out, int pin_number_to_in, int GPIOModule_to_out, int GPIOModule_to_in){

    /* Enabling functional clocks for GPIO1 instance. */
    ConfigGPIOClkModule(GPIOModule_to_out);
 
    /* Selecting GPIO1[23] pin for use. */
    /*GPIOPinMuxSetup(CONTROL_CONF_GPMC_A(7), CONTROL_CONF_MUXMODE(7));*/
    ConfigModule_1(pin_number_to_in);
    ConfigModule_1(pin_number_to_out);
    /* Enabling the GPIO module. */
    GPIOModuleEnable(GPIO_INSTANCE_ADDRESS(GPIOModule_to_out));

    /* Resetting the GPIO module. */
    GPIOModuleReset(GPIO_INSTANCE_ADDRESS(GPIOModule_to_out));

    /* Setting the GPIO pin as an output pin. */
    GPIODirModeSet(GPIO_INSTANCE_ADDRESS(GPIOModule_to_out),
               pin_number_to_out,
               DIR_OUTPUT);
    GPIODirModeSet(GPIO_INSTANCE_ADDRESS(GPIOModule_to_in),
               pin_number_to_in,
               DIR_INPUT);
    return(0);

}
/*FUNCTION*-------------------------------------------------------
*
* Function Name : ledToggle
* Comments      :
*END*-----------------------------------------------------------*/
void ledToggle(int pin_number, int GPIOModule){
    
    flagToggle^=TOGGLE;

    if(flagToggle){
        /* Driving a logic HIGH on the GPIO pin. */
        GPIOPinWrite(GPIO_INSTANCE_ADDRESS(GPIOModule),
                pin_number,
                PIN_HIGH);
    }else{
         /* Driving a logic LOW on the GPIO pin. */
        GPIOPinWrite(GPIO_INSTANCE_ADDRESS(GPIOModule),
                pin_number,
                PIN_LOW);
    }
}

