#define __Ticker_Global
#include "Ticker.h"
#include "Adc.h"
#define COEF1 1
#define COEF2 5
#define COEF3 10


/**
  * @brief  Configures the timer as a time base.
  * @note   Peripheral configuration is minimal configuration from reset values.
  *         Thus, some useless LL unitary functions calls below are provided as
  *         commented examples - setting is default configuration from reset.
  * @param  None
  * @retval None
  */
void Configure_TIMTimeBase(void)
{
  /* Enable the timer peripheral clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4); 
  
  /* Set counter mode */
  /* Reset value is LL_TIM_COUNTERMODE_UP */
  //LL_TIM_SetCounterMode(TIM2, LL_TIM_COUNTERMODE_UP);

  /* Set the pre-scaler value to have TIM2 counter clock equal to 10 kHz      */
  /*
    In this example TIM2 input clock (TIM2CLK)  is set to APB1 clock (PCLK1),
    since APB1 prescaler is equal to 1.
      TIM2CLK = PCLK1
      PCLK1 = HCLK
      => TIM2CLK = HCLK = SystemCoreClock
    To get TIM2 counter clock at 10 KHz, the Prescaler is computed as following:
    Prescaler = (TIM2CLK / TIM2 counter clock) - 1
    Prescaler = (SystemCoreClock /10 KHz) - 1
  */
  LL_TIM_SetPrescaler(TIM4, __LL_TIM_CALC_PSC(SystemCoreClock, 100000));
  
  /* Set the auto-reload value to have an initial update event frequency of 10000 Hz */
    /* TIM2CLK = SystemCoreClock / (APB prescaler & multiplier)                 */

  LL_TIM_SetAutoReload(TIM4, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM4), 10000));
  
  /* Enable the update interrupt */
  LL_TIM_EnableIT_UPDATE(TIM4);
  
  /* Configure the NVIC to handle TIM2 update interrupt */
  NVIC_SetPriority(TIM4_IRQn, 0);
  NVIC_EnableIRQ(TIM4_IRQn);
  
  /* Enable counter */
  LL_TIM_EnableCounter(TIM4);
  
  /* Force update generation */
  LL_TIM_GenerateEvent_UPDATE(TIM4);
}


void LeftPIDInit(float P, float I, float D)
{
	dutyCycleLeft = 0.5;
	LeftPID.P = P;
	LeftPID.I = I;
	LeftPID.D = D;
         
	LeftPID.CurrentError = 0;
	LeftPID.LastError = 0;
	LeftPID.Pout = 0;
	LeftPID.Iout = 0;
	LeftPID.Dout = 0;
	LeftPID.PIDout = 0;
	       
	LeftPID.IMax = 99999999;
	LeftPID.PIDMax = 10000;

	
}

void RightPIDInit(float P, float I, float D)
{
	dutyCycleRight = 0.5;
	RightPID.P = P;
	RightPID.I = I;
	RightPID.D = D;
          
	RightPID.CurrentError = 0;
	RightPID.LastError = 0;
	RightPID.Pout = 0;
	RightPID.Iout = 0;
	RightPID.Dout = 0;
	RightPID.PIDout = 0;
	
	RightPID.IMax = 99999999;
	RightPID.PIDMax = 10000;

}
void NaviPIDInit(float P, float I, float D)
{
	NaviPID.P = P;
	NaviPID.I = I;
	NaviPID.D = D;
   
	NaviPID.CurrentError = 0;
	NaviPID.LastError = 0;
	NaviPID.Pout = 0;
	NaviPID.Iout = 0;
	NaviPID.Dout = 0;
	NaviPID.PIDout = 0;
	   
	NaviPID.IMax = 99999999;
	NaviPID.PIDMax = 200000000;

	
}
void MotorPIDCallback(void)
{
	

	/*navi*/
	S1 = GetVoltagePC2();
	S2 = GetVoltagePC3();
	S3 = GetVoltagePA4();
	S4 = GetVoltagePB0();
	S5 = GetVoltagePC1();
	S6 = GetVoltagePC0();
	average = (S1+ S2+ S3+ S4+ S5+ S6)/6.0f;
	deviation = (Abs(S1 - average) + Abs(S2 - average) + Abs(S3 - average) + Abs(S4 - average) + Abs(S5 - average) + Abs(S6 - average)) ;
	
		position =COEF1*(S4-S3)+COEF2*(S5-S2)+COEF3*(S6-S1);
		
		NaviPID.CurrentError = 0 - position;
		NaviPID.Pout = 			NaviPID.P *			NaviPID.CurrentError;
		NaviPID.Iout += 		NaviPID.I * 		NaviPID.CurrentError;
		NaviPID.Dout	 = 				NaviPID.D * (NaviPID.CurrentError -	NaviPID.LastError);
		NaviPID.LastError = NaviPID.CurrentError;
		NaviPID.PIDout = (NaviPID.Pout + NaviPID.Iout + NaviPID.Dout);
		if(deviation>600)
	{
		targetLeft = 600 - NaviPID.PIDout;
		targetRight= 600 + NaviPID.PIDout;
		
	}
	else
	{
		
		
		targetLeft=0;
		targetRight=0;
	}
	/*navi*/
	
	
	lastPulseLeft=currentPulseLeft;
	lastPulseRight=currentPulseRight;	
	currentPulseLeft = getPulsesLeft();
	currentPulseRight = getPulsesRight();
	rightSpeed =(int32_t) (currentPulseRight-lastPulseRight)/0.0001f;
	leftSpeed = (int32_t)(currentPulseLeft-lastPulseLeft)/0.0001f;
	
	LeftPID.CurrentError = targetLeft - leftSpeed;
	LeftPID.Pout = LeftPID.P *LeftPID.CurrentError;

	LeftPID.Iout += LeftPID.I * LeftPID.CurrentError;
	LeftPID.Dout = 	LeftPID.D * (LeftPID.CurrentError -LeftPID.LastError);
	LeftPID.LastError = LeftPID.CurrentError;
	LeftPID.PIDout = (LeftPID.Pout + LeftPID.Iout + LeftPID.Dout);

	dutyCycleLeft += (float)LeftPID.PIDout/(float)LeftPID.PIDMax/2.0f;
//		dutyCycleLeft = dutyCycleLeft>0.8?0.8:dutyCycleLeft;
//	dutyCycleLeft = dutyCycleLeft<0.2?0.2:dutyCycleLeft;
	Set_DutyCycle_Motor_Left(dutyCycleLeft);
	
		RightPID.CurrentError = targetRight - rightSpeed;
	RightPID.Pout = RightPID.P *RightPID.CurrentError;
	RightPID.Iout += RightPID.I * RightPID.CurrentError;
	RightPID.Dout = 	RightPID.D * (RightPID.CurrentError -RightPID.LastError);
	RightPID.LastError = RightPID.CurrentError;
	RightPID.PIDout = (RightPID.Pout + RightPID.Iout + RightPID.Dout);

	dutyCycleRight += (float)RightPID.PIDout/(float)RightPID.PIDMax/2.0f;
	//	dutyCycleRight = dutyCycleRight>0.8?0.8:dutyCycleRight;
//	dutyCycleRight = dutyCycleRight<0.2?0.2:dutyCycleRight;
	Set_DutyCycle_Motor_Right(dutyCycleRight);
	
}

void SetTargetLeft(uint32_t x)
{
	targetLeft = x;
}
void SetTargetRight(uint32_t x)
{
	targetRight = x;
}
int32_t getRightSpeed(void)
{
	return rightSpeed;
}int32_t getLeftSpeed(void)
{
	return leftSpeed;
}
float Abs(float x)
{
	if(x>0)
	{
		return x;
	}
	else
	{
		return -x;
	}
}