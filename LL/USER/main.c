#include "main.h"
#include "System_Functions.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "Usart.h"
#include "Adc.h"
#include "Button.h"
#include "Enable.h"
#include "Motors_And_Encoders.h"



int main(void)
{

  SystemClock_Config();
	
	Configure_USB_UART();
	Configure_User_LED();
	Configure_User_Button();
	
	Configure_Motorboard_Enable();
	
	Configure_OutLED_Enable();
	Configure_MidLED_Enable();
	Configure_InLED_Enable();
	
	Configure_Bipolar1_Enable();
	Configure_Bipolar2_Enable();
	
	Configure_Motor_Right();
	Configure_Motor_Left();
	
		Configure_Encoder_Left(); 
		Configure_Encoder_Right(); 
	
	/* Configure DMA for data transfer from ADC */
  Configure_DMA();
  
  /* Configure ADC */
  /* Note: This function configures the ADC but does not enable it.           */
  /*       To enable it, use function "Activate_ADC()".                       */
  /*       This is intended to optimize power consumption:                    */
  /*       1. ADC configuration can be done once at the beginning             */
  /*          (ADC disabled, minimal power consumption)                       */
  /*       2. ADC enable (higher power consumption) can be done just before   */
  /*          ADC conversions needed.                                         */
  /*          Then, possible to perform successive "Activate_ADC()",          */
  /*          "Deactivate_ADC()", ..., without having to set again            */
  /*          ADC configuration.                                              */
  Configure_ADC();
  
  /* Activate ADC */
  /* Perform ADC activation procedure to make it ready to convert. */
  Activate_ADC();
	MotorBoard_On();
	
	OutLED_On();
	MidLED_On();
	InLED_On();
	
	Bipolar1_On();
	Bipolar2_On();
	
	
	Set_DutyCycle_Motor_Right(40);
	Set_DutyCycle_Motor_Left(40);

  while (1)
  {
		LL_mDelay(500);
		ADCPrintValue();
		printf("\r\n Lpulses:%d",getPulsesLeft());
		printf("\r\n Rpulses:%d",getPulsesRight());

	}
	
}



