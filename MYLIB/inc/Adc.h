#ifndef  __ADC_H
#define __ADC_H

#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_adc.h"
#include "stm32f4xx_ll_dma.h"
#include "Led.h"
#include "main.h"
#include "Usart.h"



#define ADC_CONVERTED_DATA_BUFFER_SIZE   ((uint32_t)   3)

  /* Timeout values for ADC operations. */
  /* (enable settling time, disable settling time, ...)                       */
  /* Values defined to be higher than worst cases: low clock frequency,       */
  /* maximum prescalers.                                                      */
  /* Example of profile very low frequency : ADC clock frequency 36MHz        */
  /* prescaler 2, sampling time 56 ADC clock cycles, resolution 12 bits.      */
  /*  - ADC enable time: maximum delay is 3 us                                */
  /*    (refer to device datasheet, parameter "tSTAB")                        */
  /*  - ADC disable time: maximum delay should be a few ADC clock cycles      */
  /*  - ADC stop conversion time: maximum delay should be a few ADC clock     */
  /*    cycles                                                                */
  /*  - ADC conversion time: with this hypothesis of clock settings, maximum  */
  /*    delay will be 99us.                                                   */
  /*    (refer to device reference manual, section "Timing")                  */
  /* Unit: ms                                                                 */
  #define ADC_CALIBRATION_TIMEOUT_MS       ((uint32_t)   1)
  #define ADC_ENABLE_TIMEOUT_MS            ((uint32_t)   1)
  #define ADC_DISABLE_TIMEOUT_MS           ((uint32_t)   1)
  #define ADC_STOP_CONVERSION_TIMEOUT_MS   ((uint32_t)   1)
  #define ADC_CONVERSION_TIMEOUT_MS        ((uint32_t)   2)	
	
	/* Definitions of environment analog values */
  /* Value of analog reference voltage (Vref+), connected to analog voltage   */
  /* supply Vdda (unit: mV).                                                  */
  #define VDDA_APPLI                       ((uint32_t)3300)
	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/



#ifdef  GLOBAL_ADC
#define __ADC_EXT
#else
#define __ADC_EXT extern
#endif

/* Variable to report status of DMA transfer of ADC group regular conversions */
/*  0: DMA transfer is not completed                                          */
/*  1: DMA transfer is completed                                              */
/*  2: DMA transfer has not been started yet (initial state)                  */
__ADC_EXT volatile uint8_t ubDmaTransferStatus; /* Variable set into DMA interruption callback */

/* Variable to report status of ADC group regular sequence conversions:       */
/*  0: ADC group regular sequence conversions are not completed               */
/*  1: ADC group regular sequence conversions are completed                   */
__ADC_EXT volatile uint8_t ubAdcGrpRegularSequenceConvStatus; /* Variable set into ADC interruption callback */

/* Variables for ADC conversion data computation to physical values */
__ADC_EXT volatile uint16_t uhADCxConvertedData_PA4_mVolt;        /* Value of voltage on GPIO pin (on which is mapped ADC channel) calculated from ADC conversion data (unit: mV) */
__ADC_EXT volatile uint16_t uhADCxConvertedData_PA0_mVolt; 
__ADC_EXT volatile uint16_t uhADCxConvertedData_PA1_mVolt; 
__ADC_EXT volatile uint16_t uhADCxConvertedData_VrefAnalog_mVolt;         /* Value of analog reference voltage (Vref+), connected to analog voltage supply Vdda, calculated from ADC conversion data (unit: mV) */
__ADC_EXT volatile uint32_t ubAdcGrpRegularSequenceConvCount;         /* Value of analog reference voltage (Vref+), connected to analog voltage supply Vdda, calculated from ADC conversion data (unit: mV) */

/* Variables for ADC conversion data */

//static uint16_t aADCxConvertedData[ADC_CONVERTED_DATA_BUFFER_SIZE]; /* ADC group regular conversion data */




/* Variable to report number of ADC group regular sequence completed          */
//static uint32_t ubAdcGrpRegularSequenceConvCount = 0; /* Variable set into ADC interruption callback */




void Configure_DMA(void);
void Configure_ADC(void);
void Activate_ADC(void);
void AdcDmaTransferComplete_Callback(void);
void AdcDmaTransferError_Callback(void);
void AdcGrpRegularOverrunError_Callback(void);
void AdcGrpRegularSequenceConvComplete_Callback(void);
uint16_t GetVoltagePA4(void);
uint16_t GetVoltagePA0(void);
uint16_t GetVoltagePA1(void);
void ADCPrintValue(void);

#endif 
