#include "gpioLED.h"
#include "gpioConfig.h"


/* Config clock of a module*/

void GPIO0_ModuleClkConfig(void){
	HWREG(SOC_CM_WKUP_REGS + CM_WKUP_GPIO0_CLKCTRL) |=
          CM_WKUP_GPIO0_CLKCTRL_MODULEMODE_ENABLE;

    HWREG(SOC_CM_WKUP_REGS + CM_WKUP_GPIO0_CLKCTRL) |=
          CM_WKUP_GPIO0_CLKCTRL_OPTFCLKEN_GPIO0_GDBCLK;
}

void GPIO1_ModuleClkConfig(void){

    HWREG(SOC_CM_PER_REGS + CM_PER_GPIO1_CLKCTRL) |=
          CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE;

    HWREG(SOC_CM_PER_REGS + CM_PER_GPIO1_CLKCTRL) |=
          CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK;
}

void GPIO2_ModuleClkConfig(void){
	HWREG(SOC_CM_PER_REGS + CM_PER_GPIO2_CLKCTRL) |=
          CM_PER_GPIO2_CLKCTRL_MODULEMODE_ENABLE;

    HWREG(SOC_CM_PER_REGS + CM_PER_GPIO2_CLKCTRL) |=
          CM_PER_GPIO2_CLKCTRL_OPTFCLKEN_GPIO_2_GDBCLK;
}

void GPIO3_ModuleClkConfig(void){
	HWREG(SOC_CM_PER_REGS + CM_PER_GPIO3_CLKCTRL) |=
          CM_PER_GPIO3_CLKCTRL_MODULEMODE_ENABLE;

    HWREG(SOC_CM_PER_REGS + CM_PER_GPIO3_CLKCTRL) |=
          CM_PER_GPIO3_CLKCTRL_OPTFCLKEN_GPIO_3_GDBCLK;
}

/* Points which module to config*/
void ConfigGPIOClkModule(int module_clk){
	switch(module_clk){
		case MODULE_0:
			GPIO0_ModuleClkConfig();
			break;
		case MODULE_1:
			GPIO1_ModuleClkConfig();
			break;
		case MODULE_2:
			GPIO2_ModuleClkConfig();
			break;
		case MODULE_3:
			GPIO3_ModuleClkConfig();
			break;
	}
}

/* Do the pin mux according with the module and pin number*/
void ConfigModule_0(int pin_number){

}
void ConfigModule_1(int pin_number){
	int aux = 0;
	switch(pin_number){
		case GPIO0 ... GPIO7:
        	GPIOPinMuxSetup(CONTROL_CONF_GPMC_AD(pin_number), CONTROL_CONF_MUXMODE(7));		
			break;

		case GPIO8 ... GPIO11:
			referenceTo_UART(pin_number);
			break;

		case GPIO12 ... GPIO15:
        	GPIOPinMuxSetupInput(CONTROL_CONF_GPMC_AD(pin_number), CONTROL_CONF_MUXMODE(7));
			break;
		
		case GPIO16 ... GPIO27:
			aux = pin_number - 16;
        	GPIOPinMuxSetup(CONTROL_CONF_GPMC_A(aux), CONTROL_CONF_MUXMODE(7));
			break;

		case GPIO28:
			GPIOPinMuxSetup(CONTROL_CONF_GPMC_BE1N, CONTROL_CONF_MUXMODE(7));
			break;
		
		case GPIO29 ... GPIO31:
			referenceTo_GPMC_CSN(pin_number);
			break;
	}
}

void ConfigModule_2(int pin_number){

}
void ConfigModule_3(int pin_number){

}

void referenceTo_UART(int pin_number){
	switch(pin_number){
		case GPIO8:
            GPIOPinMuxSetup(CONTROL_CONF_UART_CTSN(0), CONTROL_CONF_MUXMODE(7));
            break;
        case GPIO9:
            GPIOPinMuxSetup(CONTROL_CONF_UART_RTSN(0), CONTROL_CONF_MUXMODE(7));        
            break;
        case GPIO10:
            GPIOPinMuxSetup(CONTROL_CONF_UART_RXD(0), CONTROL_CONF_MUXMODE(7));
            break;
        case GPIO11:
            GPIOPinMuxSetup(CONTROL_CONF_UART_TXD(0), CONTROL_CONF_MUXMODE(7));
            break;
	}
}

void referenceTo_GPMC_CSN(int pin_number){
	switch(pin_number){
		case GPIO29:
            GPIOPinMuxSetup(CONTROL_CONF_GPMC_CSN(0), CONTROL_CONF_MUXMODE(7));
            break;
        case GPIO30:
            GPIOPinMuxSetup(CONTROL_CONF_GPMC_CSN(1), CONTROL_CONF_MUXMODE(7));
            break;
        case GPIO31:
            GPIOPinMuxSetup(CONTROL_CONF_GPMC_CSN(2), CONTROL_CONF_MUXMODE(7));
            break;
    }
}