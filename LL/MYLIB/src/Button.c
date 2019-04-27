#define GLOBAL_BUTTON

#include "Button.h"
#include "Ticker.h"

void Configure_User_Button(void)
{
	state_ = 0;
   /* Enable the BUTTON Clock */
  USER_BUTTON_GPIO_CLK_ENABLE();
  
  /* Configure GPIO for BUTTON */
  LL_GPIO_SetPinMode(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN, LL_GPIO_PULL_NO);
  
  /* if(Button_Mode == BUTTON_MODE_EXTI) */
  {
    /* Connect External Line to the GPIO */
    USER_BUTTON_SYSCFG_SET_EXTI();
    
    /* Enable a rising trigger EXTI line 13 Interrupt */
    USER_BUTTON_EXTI_LINE_ENABLE();
    USER_BUTTON_EXTI_FALLING_TRIG_ENABLE();
    
    /* Configure NVIC for USER_BUTTON_EXTI_IRQn */
    NVIC_EnableIRQ(USER_BUTTON_EXTI_IRQn); 
    NVIC_SetPriority(USER_BUTTON_EXTI_IRQn,0x03);  
  }
}

/**
  * @brief  Function to manage IRQ Handler
  * @param  None
  * @retval None
  */
void UserButton_Callback(void)
{
	if(state_ == 0)
	{
	state_ = 1;
	targetLeft = 1000;
	targetRight = 1000;
	LL_mDelay(50);
	}else if(state_ == 1)
	{
	state_ = 2;
		LL_mDelay(50);
	}else if(state_==2)
	{
		finishCounter = 0;
		finish = 0;
		LL_mDelay(50);
	}
	
	ADCPrintValue();
//	//ADC1->CR2 |= 1<<30;
//  /* Turn LED off before performing a new ADC conversion start */
//  /* (conversion of ranks set in ADC group regular sequencer).                */
//  LED_Off();
//  
//  /* Reset status variable of DMA transfer before performing a new ADC        */
//  /* conversion start of a sequence (in case of previous DMA transfer         */
//  /* completed).                                                              */
//  /* Note: Optionally, for this example purpose, check DMA transfer           */
//  /*       status before starting another ADC conversion.                     */
//  if (ubDmaTransferStatus != 0)
//  {
//    ubDmaTransferStatus = 0;
//  }
//  else
//  {
//    /* Error: Previous action (ADC conversion or DMA transfer) not yet        */
//    /* completed.                                                             */
//    LED_Blinking(LED_BLINK_ERROR);
//  }
//  
//  /* Start ADC group regular conversion */
//  /* Note: Hardware constraint (refer to description of the functions         */
//  /*       below):                                                            */
//  /*       On this STM32 serie, setting of these features are not             */
//  /*       conditioned to ADC state.                                          */
//  /*       However, in order to be compliant with other STM32 series          */
//  /*       and to show the best practice usages, ADC state is checked.        */
//  /*       Software can be optimized by removing some of these checks, if     */
//  /*       they are not relevant considering previous settings and actions    */
//  /*       in user application.                                               */
//  if (LL_ADC_IsEnabled(ADC1) == 1)
//  {
//    LL_ADC_REG_StartConversionSWStart(ADC1);
//  }
//  else
//  {
//    /* Error: ADC conversion start could not be performed */
//    LED_Blinking(LED_BLINK_ERROR);
//  }
}

