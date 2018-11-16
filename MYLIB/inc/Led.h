#ifndef  __LED_H
#define __LED_H

#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_bus.h"
#include "main.h"

void Configure_User_LED(void);
void LED_On(void);
void LED_Off(void);
void LED_Blinking(uint32_t Period);


#endif 