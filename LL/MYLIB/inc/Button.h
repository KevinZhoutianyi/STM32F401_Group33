#ifndef  __BUTTON_H
#define __BUTTON_H

#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_bus.h"
#include "Led.h"
#include "Adc.h"
#include "main.h"


#ifdef  GLOBAL_BUTTON
#define __BUTTON_EXT
#else
#define __BUTTON_EXT extern
#endif

__BUTTON_EXT int state_;

void Configure_User_Button(void);
void UserButton_Callback(void);

#endif 
