/***********************************************************************/
#include "lpc17xx_gpio.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_systick.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_pwm.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_adc.h"
#include "mylpclib.h"
#include "lpc17xx_rtc.h"
#include "lpc17xx_wdt.h"
#include "individualproj.c"


//Run Main Program
int main (void){

	//Setup external device communication, I2C1 Bus && UART
	setupUART();
	setupI2C1();
	setupADC();
	setupGPIO(2,5,1);
	SetupPWM(10);

	//Start tracking mode with a threshold of 3
	trackingMode(3);

	return 1;
}
