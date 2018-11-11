#define GLOBAL_BUTTON

#include "Button.h"

void Configure_User_Button(void)
{
  //Setup User Button GPIO PC13
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_13, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_13, LL_GPIO_PULL_UP);
	
	//Setup Interrupts for Line 13 EXTI
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);                  \
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE13); 
	LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_13);
	LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_13);
	NVIC_EnableIRQ(EXTI15_10_IRQn); // Enable IRQ for EXTI line 13 in NVIC
}
