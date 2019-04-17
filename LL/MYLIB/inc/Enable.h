#ifndef  __ENABLE_H
#define __ENABLE_H

#define GLOBAL_ENABLE

#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_bus.h"
#include "main.h"




void Configure_Motorboard_Enable(void);
void Configure_OutLED_Enable(void);
void Configure_MidLED_Enable(void);
void Configure_InLED_Enable(void);
void Configure_Bipolar1_Enable(void);
void Configure_Bipolar2_Enable(void);

/**
  * @brief  Turn-on LED2.
  * @param  None
  * @retval None
  */
void MotorBoard_On(void);
void OutLED_On(void);
void MidLED_On(void);
void InLED_On(void);
void Bipolar1_On(void);
void Bipolar2_On(void);
/**
  * @brief  Turn-off LED2.
  * @param  None
  * @retval None
  */

void MotorBoard_Off(void);
void OutLED_Off(void);
void MidLED_Off(void);
void InLED_Off(void);




#endif 