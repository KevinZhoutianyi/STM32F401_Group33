#include "Motors_And_Encoders.h"
#include "math.h"
#include "System_Functions.h"


void Set_DutyCycle_Motor_Left(float D){
	float P;    //Pulse duration                                           
  float T;    //PWM signal period  
	D = fabs(D);
	
	/* PWM signal period is determined by the value of the auto-reload register */
  T = LL_TIM_GetAutoReload(TIM3) + 1;
  /* Pulse duration is determined by the value of the compare register.       */
  /* Its value is calculated in order to match the requested duty cycle.      */
  P = ((D)*T);

  LL_TIM_OC_SetCompareCH3(TIM3, (uint32_t)P);	
}

void Set_DutyCycle_Motor_Right(float D){
	float P;    //Pulse duration                                           
  float T;    //PWM signal period  
	D = fabs(D);
	
	/* PWM signal period is determined by the value of the auto-reload register */
  T = LL_TIM_GetAutoReload(TIM3) + 1;
  /* Pulse duration is determined by the value of the compare register.       */
  /* Its value is calculated in order to match the requested duty cycle.      */
  P = ((D)*T);

  LL_TIM_OC_SetCompareCH1(TIM3, (uint32_t)P);	
}

void Configure_Motor_Right(void){
	//Setup GPIO PB7 for PWM Output (TMR4 CH2).
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC); // Enable CLK to GPIOB
  LL_GPIO_SetPinMode(GPIOC,   LL_GPIO_PIN_6, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinPull(GPIOC,   LL_GPIO_PIN_6, LL_GPIO_PULL_NO);
  LL_GPIO_SetPinSpeed(GPIOC,  LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_VERY_HIGH);
  LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_6, LL_GPIO_AF_2);
	
	// Timer 4 peripheral Configuration
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3); // Enable clock to Timer 4 peripheral
	//Set the pre-scaler value to have TIM2 counter clock equal to 42 MHz */
  LL_TIM_SetPrescaler(TIM3, __LL_TIM_CALC_PSC(SystemCoreClock, 42000000));
	LL_TIM_EnableARRPreload(TIM3);
	/* Set the auto-reload value to have a counter frequency of 1000 Hz */
	LL_TIM_SetAutoReload(TIM3, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM3), 20000));
	//Set Timer Output mode
	LL_TIM_OC_SetMode(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
	/* Set compare value to half of the counter period (50% duty cycle ) */
  LL_TIM_OC_SetCompareCH1(TIM3, ( (LL_TIM_GetAutoReload(TIM3) + 1 ) / 2));
	/* Enable TIM4_CCR1 register preload. Read/Write operations access the      */
  /* preload register. TIM4_CCR1 preload value is loaded in the active        */
  /* at each update event.                                                    */
  LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH1);
	/* Enable the capture/compare interrupt for channel 2*/
  //LL_TIM_EnableIT_CC1(TIM4);
	/* Enable output channel 2 */
  LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH1);
  /* Enable counter */
//  LL_TIM_EnableCounter(TIM3);
  /* Force update generation */
  LL_TIM_GenerateEvent_UPDATE(TIM3);
}

void Configure_Motor_Left(void){
		//Setup GPIO PA11 for PWM Output (TMR1 CH4).
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC); // Enable CLK to GPIOA
  LL_GPIO_SetPinMode(GPIOC,   LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinPull(GPIOC,   LL_GPIO_PIN_8, LL_GPIO_PULL_NO);
  LL_GPIO_SetPinSpeed(GPIOC,  LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_VERY_HIGH);
  LL_GPIO_SetAFPin_8_15(GPIOC,LL_GPIO_PIN_8, LL_GPIO_AF_2);
	
	// Timer 1 peripheral Configuration
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3); // Enable clock to Timer 1 peripheral
	//Set the pre-scaler value to have TIM1 counter clock equal to 42 MHz */
  LL_TIM_SetPrescaler(TIM3, __LL_TIM_CALC_PSC(SystemCoreClock, 42000000));
	LL_TIM_EnableARRPreload(TIM3);
	/* Set the auto-reload value to have a counter frequency of 1000 Hz */
	LL_TIM_SetAutoReload(TIM3, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM3), 20000));
	//Set Timer Output mode
	LL_TIM_OC_SetMode(TIM3, LL_TIM_CHANNEL_CH3, LL_TIM_OCMODE_PWM1);
	/* Set compare value to half of the counter period (50% duty cycle ) */
  LL_TIM_OC_SetCompareCH3(TIM3, ( (LL_TIM_GetAutoReload(TIM3) + 1 ) / 2));
	/* Enable TIM1_CCR1 register preload. Read/Write operations access the      */
  /* preload register. TIM1_CCR1 preload value is loaded in the active        */
  /* at each update event.                                                    */
  LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH3);
	/* Enable the capture/compare interrupt for channel 4*/
  //LL_TIM_EnableIT_CC1(TIM1);
	/* Enable output channel 4 */
  LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH3);
	LL_TIM_EnableAllOutputs(TIM3);
  /* Enable counter */
  LL_TIM_EnableCounter(TIM3);
  /* Force update generation */
  LL_TIM_GenerateEvent_UPDATE(TIM3);
}

int Get_Encoder_Left(void){
	return LL_TIM_GetCounter(TIM2);
}

int Get_Encoder_Right(void){
	return LL_TIM_GetCounter(TIM5);
}



void Configure_Encoder_Left(void){
    //Setup GPIO PA15 for Encoder Input (TMR2 CH1).
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA); // Enable CLK to GPIOA
  LL_GPIO_SetPinMode(  GPIOA, LL_GPIO_PIN_15, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinPull(  GPIOA, LL_GPIO_PIN_15, LL_GPIO_PULL_NO);
  LL_GPIO_SetPinSpeed( GPIOA, LL_GPIO_PIN_15, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_15, LL_GPIO_AF_1);
     
        //Setup GPIO PB3 for Encoder Input (TMR2 CH2).
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB); // Enable CLK to GPIOB
  LL_GPIO_SetPinMode(  GPIOB, LL_GPIO_PIN_3, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinPull(  GPIOB, LL_GPIO_PIN_3, LL_GPIO_PULL_NO);
  LL_GPIO_SetPinSpeed( GPIOB, LL_GPIO_PIN_3, LL_GPIO_SPEED_FREQ_VERY_HIGH);
  LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_3, LL_GPIO_AF_1);
     
    NVIC_SetPriority(TIM2_IRQn, 0);
  NVIC_EnableIRQ(TIM2_IRQn);    
     
    // Timer 2 peripheral Configuration
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2); // Enable clock to Timer 2 peripheral
    //Set the pre-scaler value to have TIM2 counter clock equal to 42 MHz */
  LL_TIM_SetPrescaler(TIM2, __LL_TIM_CALC_PSC(SystemCoreClock, 42000000));
     
    LL_TIM_IC_SetActiveInput(TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_ACTIVEINPUT_DIRECTTI);
    LL_TIM_IC_SetFilter(     TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_IC_FILTER_FDIV1);
    LL_TIM_IC_SetPrescaler(  TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_ICPSC_DIV1);
    LL_TIM_IC_SetPolarity(   TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING);
     
    LL_TIM_IC_SetActiveInput(TIM2, LL_TIM_CHANNEL_CH2, LL_TIM_ACTIVEINPUT_DIRECTTI);
    LL_TIM_IC_SetFilter(     TIM2, LL_TIM_CHANNEL_CH2, LL_TIM_IC_FILTER_FDIV1);
    LL_TIM_IC_SetPrescaler(  TIM2, LL_TIM_CHANNEL_CH2, LL_TIM_ICPSC_DIV1);
    LL_TIM_IC_SetPolarity(   TIM2, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_RISING);
     
    LL_TIM_SetEncoderMode(TIM2, LL_TIM_ENCODERMODE_X2_TI2);
    LL_TIM_EnableIT_CC1(TIM2);
     
    LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH2);
    LL_TIM_EnableCounter(TIM2);
}
 
 
void Configure_Encoder_Right(void){
    //Setup GPIO PA0 for Encoder Input (TMR5 CH1). 
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA); // Enable CLK to GPIOA
  LL_GPIO_SetPinMode(   GPIOA,  LL_GPIO_PIN_0, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinPull(   GPIOA,  LL_GPIO_PIN_0, LL_GPIO_PULL_NO);
  LL_GPIO_SetPinSpeed(  GPIOA,  LL_GPIO_PIN_0, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetAFPin_0_7( GPIOA,  LL_GPIO_PIN_0, LL_GPIO_AF_2);
     
        //Setup GPIO PA_1 for Encoder Input (TMR5 CH2).
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA); // Enable CLK to GPIOA
  LL_GPIO_SetPinMode(  GPIOA,   LL_GPIO_PIN_1, LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinPull(  GPIOA,   LL_GPIO_PIN_1, LL_GPIO_PULL_NO);
  LL_GPIO_SetPinSpeed( GPIOA,   LL_GPIO_PIN_1, LL_GPIO_SPEED_FREQ_VERY_HIGH);
  LL_GPIO_SetAFPin_0_7(GPIOA,   LL_GPIO_PIN_1, LL_GPIO_AF_2);
     
    NVIC_SetPriority(TIM5_IRQn , 0);
  NVIC_EnableIRQ(TIM5_IRQn );   
     
    // Timer 5 peripheral Configuration
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5); // Enable clock to Timer 5 peripheral
    //Set the pre-scaler value to have TIM2 counter clock equal to 42 MHz */
  LL_TIM_SetPrescaler(TIM5, __LL_TIM_CALC_PSC(SystemCoreClock, 42000000));
     
    LL_TIM_IC_SetActiveInput(TIM5, LL_TIM_CHANNEL_CH1, LL_TIM_ACTIVEINPUT_DIRECTTI);
    LL_TIM_IC_SetFilter(     TIM5, LL_TIM_CHANNEL_CH1, LL_TIM_IC_FILTER_FDIV1);
    LL_TIM_IC_SetPrescaler(  TIM5, LL_TIM_CHANNEL_CH1, LL_TIM_ICPSC_DIV1);
    LL_TIM_IC_SetPolarity(   TIM5, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING);
     
    LL_TIM_IC_SetActiveInput(TIM5, LL_TIM_CHANNEL_CH2, LL_TIM_ACTIVEINPUT_DIRECTTI);
    LL_TIM_IC_SetFilter(     TIM5, LL_TIM_CHANNEL_CH2, LL_TIM_IC_FILTER_FDIV1);
    LL_TIM_IC_SetPrescaler(  TIM5, LL_TIM_CHANNEL_CH2, LL_TIM_ICPSC_DIV1);
    LL_TIM_IC_SetPolarity(   TIM5, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_RISING);
     
    LL_TIM_SetEncoderMode(TIM5, LL_TIM_ENCODERMODE_X2_TI2);
    LL_TIM_EnableIT_CC1(TIM5);
     
    LL_TIM_CC_EnableChannel(TIM5, LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_EnableChannel(TIM5, LL_TIM_CHANNEL_CH2);
    LL_TIM_EnableCounter(TIM5);
}

void Start()
{
	/* 
		Pins used for this example
		Quadrature Encoder Right  on Timer 5 CH1 = PA0,  Timer 5 CH2 = PA1.
		Quadrature Encoder Left on Timer 2 CH1 = PA15, Timer 2 CH2 = PB3.
		Motor Right PWM                         = PB7,  Timer 4 CH2 
		Motor Left  PWM                         = PA11, Timer 1 CH4
		Nucleo User LED                         = PA5
		Nucleo User Button                      = PC13
*/
	
	
		//Right Motor and Encoder Initialisation
	Configure_Encoder_Right();                 //Configure Encoder input on PA15,PA1 (TIMER 2 CH1, CH2)
	Configure_Motor_Right();                   //Setup PB7 (TIMER 4 CH2) as PWM Output for Right Motor
	Set_DutyCycle_Motor_Right(0);
	
	//Left Motor and Encoder Initialisation
	Configure_Encoder_Left();                  //Configure Encoder input on PB4, PB5 (TIMER 3 CH1, CH2)
	Configure_Motor_Left();                    //Setup PA11(TIMER 1 CH4) as PWM Output for Left Motor
	Set_DutyCycle_Motor_Left(0);
	
	
	Set_DutyCycle_Motor_Left(50);
	Set_DutyCycle_Motor_Right(50);	
}

void Reset_Encoders(void){
	NVIC_DisableIRQ(TIM2_IRQn);	
	NVIC_DisableIRQ(TIM5_IRQn);

	LL_TIM_SetCounter(TIM2, 0);
	LL_TIM_SetCounter(TIM5, 0);
	
	NVIC_EnableIRQ(TIM2_IRQn);	
	NVIC_EnableIRQ(TIM5_IRQn);	
}

uint32_t getPulsesRight(void)
{
	return LL_TIM_GetCounter(TIM5);
}
uint32_t getPulsesLeft(void)
{
	return LL_TIM_GetCounter(TIM2);
}