#define GLOBAL_ENABLE

#include "Enable.h"


void Configure_Motorboard_Enable(void){
	//GREEN
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_GPIO_SetPinMode(GPIOB,     LL_GPIO_PIN_6, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinPull(GPIOB,     LL_GPIO_PIN_6, LL_GPIO_PULL_NO);
  LL_GPIO_SetPinSpeed(GPIOB,    LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_6);
}
void Configure_OutLED_Enable(void){
	//GREEN
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_GPIO_SetPinMode(GPIOB,     LL_GPIO_PIN_13, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinPull(GPIOB,     LL_GPIO_PIN_13, LL_GPIO_PULL_NO);
  LL_GPIO_SetPinSpeed(GPIOB,    LL_GPIO_PIN_13, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_13);
}
void Configure_MidLED_Enable(void){
	//GREEN
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_GPIO_SetPinMode(GPIOB,     LL_GPIO_PIN_14, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinPull(GPIOB,     LL_GPIO_PIN_14, LL_GPIO_PULL_NO);
  LL_GPIO_SetPinSpeed(GPIOB,    LL_GPIO_PIN_14, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_14);
}
void Configure_InLED_Enable(void){
	//GREEN
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_GPIO_SetPinMode(GPIOB,     LL_GPIO_PIN_15, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinPull(GPIOB,     LL_GPIO_PIN_15, LL_GPIO_PULL_NO);
  LL_GPIO_SetPinSpeed(GPIOB,    LL_GPIO_PIN_15, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_15);
}
void Configure_Bipolar1_Enable(void){
	//GREEN
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_GPIO_SetPinMode(GPIOA,     LL_GPIO_PIN_7, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinPull(GPIOA,     LL_GPIO_PIN_7, LL_GPIO_PULL_NO);
  LL_GPIO_SetPinSpeed(GPIOA,    LL_GPIO_PIN_7, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_7);
}
void Configure_Bipolar2_Enable(void){
	//GREEN
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_GPIO_SetPinMode(GPIOA,     LL_GPIO_PIN_6, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinPull(GPIOA,     LL_GPIO_PIN_6, LL_GPIO_PULL_NO);
  LL_GPIO_SetPinSpeed(GPIOA,    LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_6);
}

/**
  * @brief  Turn-on LED2.
  * @param  None
  * @retval None
  */
void MotorBoard_On(void)
{
  /* Turn LED2 on */
  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_6);
}
void OutLED_On(void)
{
  /* Turn LED2 on */
  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_13);
}
void MidLED_On(void)
{
  /* Turn LED2 on */
  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_14);
}
void InLED_On(void)
{
  /* Turn LED2 on */
  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_15);
}
void Bipolar1_On(void)
{
  /* Turn LED2 on */
  LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_7);
}
void Bipolar2_On(void)
{
  /* Turn LED2 on */
  LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_6);
}
/**
  * @brief  Turn-off LED2.
  * @param  None
  * @retval None
  */

void MotorBoard_Off(void)
{
  
  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_6);
}
void OutLED_Off(void)
{
  
  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_13);
}
void MidLED_Off(void)
{

  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_14);
}

void InLED_Off(void)
{

  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_15);
}


