#include "main.h"
#include "System_Functions.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "Usart.h"
#include "Adc.h"
#include "Button.h"



int main(void)
{
//	int counter = 0;
	uint16_t *dataPointer;
  SystemClock_Config();
	Configure_USB_UART();
	Configure_User_LED();
	Configure_User_Button();
	
	
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

  while (1)
  {
		while(ubDmaTransferStatus != 1)
    {
    }
//		LL_ADC_REG_StartConversionSWStart(ADC1);
//		while(counter!=10000)
//		{
//			counter++;
//		}
    
		dataPointer = GetData();
    /* Computation of ADC conversions raw data to physical values             */
    /* using LL ADC driver helper macro.                                      */
		
    uhADCxConvertedData_PA4_mVolt        = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, *dataPointer, LL_ADC_RESOLUTION_12B);
    uhADCxConvertedData_PA0_mVolt            = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, *(dataPointer+1), LL_ADC_RESOLUTION_12B);
    uhADCxConvertedData_PA1_mVolt = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, *(dataPointer+2), LL_ADC_RESOLUTION_12B);
    printf("PA4:%u\r\n",uhADCxConvertedData_PA4_mVolt);
		printf("PA0:%u\r\n",uhADCxConvertedData_PA0_mVolt);
		printf("PA1:%u\r\n",uhADCxConvertedData_PA1_mVolt);
		

    /* Wait for a new ADC conversion and DMA transfer */
    while(ubDmaTransferStatus != 0)
    {
    }
//		counter = 0;
	}
	
}



