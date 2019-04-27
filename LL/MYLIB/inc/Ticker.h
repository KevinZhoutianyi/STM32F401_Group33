#ifndef  __TICKER_H
#define __TICKER_H
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_tim.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_bus.h"
#include "Motors_And_Encoders.h"
#include "Led.h"
typedef struct 
{
	float P;
	float I;
	float D;
	
	int CurrentError;
	int LastError;
	int Pout;
	int Iout;
	int Dout;
	int PIDout;
	
	int IMax;
	int PIDMax;


}PID_Type;




#ifdef  __Ticker_Global
#define __Ticker_EXT  
#else
#define __Ticker_EXT extern
#endif

__Ticker_EXT PID_Type LeftPID,RightPID,NaviPID;
__Ticker_EXT int32_t currentPulseLeft,lastPulseLeft,currentPulseRight,lastPulseRight,targetRight,targetLeft,leftSpeed,rightSpeed;
__Ticker_EXT float dutyCycleLeft,dutyCycleRight;
__Ticker_EXT int32_t average,deviation,S1,S2,S3,S4,S5,S6,position,speedDiff,_state,reachOutRight,reachOutLeft,delayCounter,finish,finishCounter;



void Configure_TIMTimeBase(void);
void MotorPIDCallback(void);
void NaviPIDInit(float P, float I, float D);

void LeftPIDInit(float P, float I, float D);
void RightPIDInit(float P, float I, float D);

void SetTargetLeft(uint32_t x);
void SetTargetRight(uint32_t x);

float Abs(float x);

int32_t getRightSpeed(void);
int32_t getLeftSpeed(void);
#endif 
