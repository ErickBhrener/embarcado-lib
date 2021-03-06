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

int flagToggle=0x0;

/*FUNCTION*-------------------------------------------------------
*
* Function Name : GPIO1_ModuleClkConfig
* Comments      : This function enables the L3 and L4_PER interface 
* clocks. This also enables functional clocks of GPIO1 instance.
*END*-----------------------------------------------------------*/
static void GPIO1_ModuleClkConfig(void){

    /* Writing to MODULEMODE field of CM_PER_GPIO1_CLKCTRL register. */
    HWREG(SOC_CM_PER_REGS + CM_PER_GPIO1_CLKCTRL) |=
          CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE;

    /*
    ** Writing to OPTFCLKEN_GPIO_1_GDBCLK bit in CM_PER_GPIO1_CLKCTRL
    ** register.
    */
    HWREG(SOC_CM_PER_REGS + CM_PER_GPIO1_CLKCTRL) |=
          CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK;

}

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
static void GPIOPinMuxSetup(unsigned int offsetAddr, unsigned int padConfValue){
    HWREG(SOC_CONTROL_REGS + offsetAddr) = (padConfValue);
}

/*FUNCTION*-------------------------------------------------------
*
* Function Name : SPIOModuleEnable 
* Comments      : This API is used to enable the GPIO module. When 
* the GPIO module is enabled, the clocks to the module are not gated.
*
* \param  baseAdd    The memory address of the GPIO instance being used
*END*-----------------------------------------------------------*/
static void GPIOModuleEnable(unsigned int baseAdd){
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
static void GPIOModuleReset(unsigned int baseAdd){
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
static void GPIODirModeSet(unsigned int baseAdd,
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
static void GPIOPinWrite(unsigned int baseAdd,
                            unsigned int pinNumber,
                            unsigned int pinValue) {

    if(PIN_HIGH == pinValue){
        HWREG(baseAdd + GPIO_SETDATAOUT) = (1 << pinNumber);
    }else{
        HWREG(baseAdd + GPIO_CLEARDATAOUT) = (1 << pinNumber);
    }
}
static void GetGPIOPinName(){
        
    if (GPIO_INSTANCE_PIN_NUMBER >= 0 || GPIO_INSTANCE_PIN_NUMBER <= 7){
        GPIOPinMuxSetup(CONTROL_CONF_GPMC_AD(GPIO_INSTANCE_PIN_NUMBER), CONTROL_CONF_MUXMODE(GPIO_INSTANCE_PIN_NUMBER));
    }else if (GPIO_INSTANCE_PIN_NUMBER >= 8 || GPIO_INSTANCE_PIN_NUMBER <= 11){
        switch(GPIO_INSTANCE_PIN_NUMBER){
            case 8:
                GPIOPinMuxSetup(CONTROL_CONF_UART_RTSN(GPIO_INSTANCE_PIN_NUMBER), CONTROL_CONF_MUXMODE(GPIO_INSTANCE_PIN_NUMBER));
                break;
            case 9:
                GPIOPinMuxSetup(CONTROL_CONF_UART_CTSN(GPIO_INSTANCE_PIN_NUMBER), CONTROL_CONF_MUXMODE(GPIO_INSTANCE_PIN_NUMBER));
                break;
            case 10:
                GPIOPinMuxSetup(CONTROL_CONF_UART_RXD(GPIO_INSTANCE_PIN_NUMBER), CONTROL_CONF_MUXMODE(GPIO_INSTANCE_PIN_NUMBER));
                break;
            case 11:
                GPIOPinMuxSetup(CONTROL_CONF_UART_TXD(GPIO_INSTANCE_PIN_NUMBER), CONTROL_CONF_MUXMODE(GPIO_INSTANCE_PIN_NUMBER));
                break;
        }
    }else if (GPIO_INSTANCE_PIN_NUMBER >= 12 || GPIO_INSTANCE_PIN_NUMBER <= 14){
        GPIOPinMuxSetup(CONTROL_CONF_GPMC_AD(GPIO_INSTANCE_PIN_NUMBER), CONTROL_CONF_MUXMODE(GPIO_INSTANCE_PIN_NUMBER));
    }else if (GPIO_INSTANCE_PIN_NUMBER >= 16 || GPIO_INSTANCE_PIN_NUMBER <= 27){
        int PIN_REFERENCE = GPIO_INSTANCE_PIN_NUMBER - 16;
        GPIOPinMuxSetup(CONTROL_CONF_GPMC_A(PIN_REFERENCE), CONTROL_CONF_MUXMODE(PIN_REFERENCE));
    }else if (GPIO_INSTANCE_PIN_NUMBER == 28) {
        GPIOPinMuxSetup(CONTROL_CONF_GPMC_BE1N , CONTROL_CONF_MUXMODE(GPIO_INSTANCE_PIN_NUMBER));
    }else if (GPIO_INSTANCE_PIN_NUMBER >= 29 || GPIO_INSTANCE_PIN_NUMBER <= 31){

    }
}
/*FUNCTION*-------------------------------------------------------
*
* Function Name : ledInit
* Comments      :
*END*-----------------------------------------------------------*/
int ledInit(){

    /* Enabling functional clocks for GPIO1 instance. */
    GPIO1_ModuleClkConfig();
 
    /* Selecting GPIO1[23] pin for use. */
    /*GPIOPinMuxSetup(CONTROL_CONF_GPMC_A(7), CONTROL_CONF_MUXMODE(7));*/
    GetGPIOPinName();
    /* Enabling the GPIO module. */
    GPIOModuleEnable(GPIO_INSTANCE_ADDRESS);

    /* Resetting the GPIO module. */
    GPIOModuleReset(GPIO_INSTANCE_ADDRESS);

    /* Setting the GPIO pin as an output pin. */
    GPIODirModeSet(GPIO_INSTANCE_ADDRESS,
               GPIO_INSTANCE_PIN_NUMBER,
               DIR_OUTPUT);
    
    return(0);

}
/*FUNCTION*-------------------------------------------------------
*
* Function Name : ledToggle
* Comments      :
*END*-----------------------------------------------------------*/
void ledToggle(){
    
    flagToggle^=TOGGLE;

    if(flagToggle){
        /* Driving a logic HIGH on the GPIO pin. */
        GPIOPinWrite(GPIO_INSTANCE_ADDRESS,
                GPIO_INSTANCE_PIN_NUMBER,
                PIN_HIGH);
    }else{
         /* Driving a logic LOW on the GPIO pin. */
        GPIOPinWrite(GPIO_INSTANCE_ADDRESS,
                GPIO_INSTANCE_PIN_NUMBER,
                PIN_LOW);
    }
}

