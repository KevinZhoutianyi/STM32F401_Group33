#define GLOBAL_ADC

#include "Adc.h"

uint16_t aADCxConvertedData[ADC_CONVERTED_DATA_BUFFER_SIZE];

//to get the average 
uint16_t ADCAverage[6][AVERAGESIZE];
uint16_t averageCounter;
uint16_t i = 0,j=0;
uint32_t tempTotal=0;


/**
  * @brief  This function configures DMA for transfer of data from ADC
  * @param  None
  * @retval None
  */
void Configure_DMA(void)
{
  /*## Configuration of NVIC #################################################*/
  /* Configure NVIC to enable DMA interruptions */
  NVIC_SetPriority(DMA2_Stream0_IRQn, 1);  /* DMA IRQ lower priority than ADC IRQ */
  NVIC_EnableIRQ(DMA2_Stream0_IRQn);
  
  /*## Configuration of DMA ##################################################*/
  /* Enable the peripheral clock of DMA */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
  
  /* Configure the DMA transfer */
  /*  - DMA transfer in circular mode to match with ADC configuration:        */
  /*    DMA unlimited requests.                                               */
  /*  - DMA transfer from ADC without address increment.                      */
  /*  - DMA transfer to memory with address increment.                        */
  /*  - DMA transfer from ADC by half-word to match with ADC configuration:   */
  /*    ADC resolution 12 bits.                                               */
  /*  - DMA transfer to memory by half-word to match with ADC conversion data */
  /*    buffer variable type: half-word.                                      */
  LL_DMA_SetChannelSelection(DMA2, LL_DMA_STREAM_0, LL_DMA_CHANNEL_0);
  LL_DMA_ConfigTransfer(DMA2,
                        LL_DMA_STREAM_0,
                        LL_DMA_DIRECTION_PERIPH_TO_MEMORY |
                        LL_DMA_MODE_CIRCULAR              |
                        LL_DMA_PERIPH_NOINCREMENT         |
                        LL_DMA_MEMORY_INCREMENT           |
                        LL_DMA_PDATAALIGN_HALFWORD        |
                        LL_DMA_MDATAALIGN_HALFWORD        |
                        LL_DMA_PRIORITY_HIGH               );
  
	
 /* Set DMA transfer addresses of source and destination */
  LL_DMA_ConfigAddresses(DMA2,
                        LL_DMA_STREAM_0,
                         (uint32_t)&(ADC1->DR),
                         (uint32_t)aADCxConvertedData,
                         LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
  
  /* Set DMA transfer size */
  LL_DMA_SetDataLength(DMA2,
                        LL_DMA_STREAM_0,
                       ADC_CONVERTED_DATA_BUFFER_SIZE);
  
  /* Enable DMA transfer interruption: transfer complete */
  LL_DMA_EnableIT_TC(DMA2,
                        LL_DMA_STREAM_0);

  /* Enable DMA transfer interruption: transfer error */
  LL_DMA_EnableIT_TE(DMA2,
                        LL_DMA_STREAM_0);
  
  /*## Activation of DMA #####################################################*/
  /* Enable the DMA transfer */
    LL_DMA_EnableStream(DMA2,LL_DMA_STREAM_0);
}

/**
  * @brief  Configure ADC (ADC instance: ADC1) and GPIO used by ADC channels.
  * @note   In case re-use of this function outside of this example:
  *         This function includes checks of ADC hardware constraints before
  *         executing some configuration functions.
  *         - In this example, all these checks are not necessary but are
  *           implemented anyway to show the best practice usages
  *           corresponding to reference manual procedure.
  *           (On some STM32 series, setting of ADC features are not
  *           conditioned to ADC state. However, in order to be compliant with
  *           other STM32 series and to show the best practice usages,
  *           ADC state is checked anyway with same constraints).
  *           Software can be optimized by removing some of these checks,
  *           if they are not relevant considering previous settings and actions
  *           in user application.
  *         - If ADC is not in the appropriate state to modify some parameters,
  *           the setting of these parameters is bypassed without error
  *           reporting:
  *           it can be the expected behavior in case of recall of this 
  *           function to update only a few parameters (which update fullfills
  *           the ADC state).
  *           Otherwise, it is up to the user to set the appropriate error 
  *           reporting in user application.
  * @note   Peripheral configuration is minimal configuration from reset values.
  *         Thus, some useless LL unitary functions calls below are provided as
  *         commented examples - setting is default configuration from reset.
  * @param  None
  * @retval None
  */
void Configure_ADC(void)
{
	
  volatile uint32_t wait_loop_index = 0;
  cS1 =1;
	cS2 =1;
	cS3 =1;
	cS4 =1;
	cS5 =1;
	cS6 =1;
	state=0;
	averageCounter = 0;
//	ubAdcGrpRegularSequenceConvCount=0;
	uhADCxConvertedData_PA4_mVolt=0;       
	uhADCxConvertedData_PC2_mVolt=0;           
	uhADCxConvertedData_PC3_mVolt=0;
	uhADCxConvertedData_PB0_mVolt=0;
		uhADCxConvertedData_PC0_mVolt=0;
		uhADCxConvertedData_PC1_mVolt=0;
	//uhADCxConvertedData_VrefAnalog_mVolt=0;
//	ubAdcGrpRegularSequenceConvStatus=0;
	ubDmaTransferStatus=2;
	
  /*## Configuration of GPIO used by ADC channels ############################*/
  
  /* Note: On this STM32 device, ADC1 channel 4 is mapped on GPIO pin PA.04 */ 
  
  /* Enable GPIO Clock */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  
  /* Configure GPIO in analog mode to be used as ADC input */
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_ANALOG);
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_0, LL_GPIO_MODE_ANALOG);
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_2, LL_GPIO_MODE_ANALOG);
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_3, LL_GPIO_MODE_ANALOG);
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_1, LL_GPIO_MODE_ANALOG);
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_0, LL_GPIO_MODE_ANALOG);
  
  /*## Configuration of NVIC #################################################*/
  /* Configure NVIC to enable ADC1 interruptions */
  NVIC_SetPriority(ADC_IRQn, 0); /* ADC IRQ greater priority than DMA IRQ */
  NVIC_EnableIRQ(ADC_IRQn);
  
  /*## Configuration of ADC ##################################################*/
  
  /*## Configuration of ADC hierarchical scope: common to several ADC ########*/
  
  /* Enable ADC clock (core clock) */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
  
  /* Note: Hardware constraint (refer to description of the functions         */
  /*       below):                                                            */
  /*       On this STM32 serie, setting of these features are not             */
  /*       conditioned to ADC state.                                          */
  /*       However, in order to be compliant with other STM32 series          */
  /*       and to show the best practice usages, ADC state is checked.        */
  /*       Software can be optimized by removing some of these checks, if     */
  /*       they are not relevant considering previous settings and actions    */
  /*       in user application.                                               */
  if(__LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE() == 0)
  {
    /* Note: Call of the functions below are commented because they are       */
    /*       useless in this example:                                         */
    /*       setting corresponding to default configuration from reset state. */
    
    /* Set ADC clock (conversion clock) common to several ADC instances */
    LL_ADC_SetCommonClock(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_CLOCK_SYNC_PCLK_DIV2);
    
    /* Set ADC measurement path to internal channels */
    LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), (LL_ADC_PATH_INTERNAL_VREFINT | LL_ADC_PATH_INTERNAL_TEMPSENSOR));
    
    /* Delay for ADC temperature sensor stabilization time.                   */
    /* Compute number of CPU cycles to wait for, from delay in us.            */
    /* Note: Variable divided by 2 to compensate partially                    */
    /*       CPU processing cycles (depends on compilation optimization).     */
    /* Note: If system core clock frequency is below 200kHz, wait time        */
    /*       is only a few CPU processing cycles.                             */
    /* Note: This delay is implemented here for the purpose in this example.  */
    /*       It can be optimized if merged with other delays                  */
    /*       during ADC activation or if other actions are performed          */
    /*       in the meantime.                                                 */
    wait_loop_index = 4;//(( 0.5* (SystemCoreClock / (100000 * 2))) / 10);
    while(wait_loop_index != 0)
    {
      wait_loop_index--;
    }
  
  /*## Configuration of ADC hierarchical scope: multimode ####################*/
  
    /* Note: ADC multimode is not available on this device:                   */
    /*       only 1 ADC instance is present.                                  */
    /* Set ADC multimode configuration */
    // LL_ADC_SetMultimode(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_MULTI_INDEPENDENT);
    
    /* Set ADC multimode DMA transfer */
    // LL_ADC_SetMultiDMATransfer(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_MULTI_REG_DMA_EACH_ADC);
    
    /* Set ADC multimode: delay between 2 sampling phases */
    // LL_ADC_SetMultiTwoSamplingDelay(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_MULTI_TWOSMP_DELAY_1CYCLE);
    
  }
  
  
  /*## Configuration of ADC hierarchical scope: ADC instance #################*/
  
  /* Note: Hardware constraint (refer to description of the functions         */
  /*       below):                                                            */
  /*       On this STM32 serie, setting of these features are not             */
  /*       conditioned to ADC state.                                          */
  /*       However, ADC state is checked anyway with standard requirements    */
  /*       (refer to description of this function).                           */
  if (LL_ADC_IsEnabled(ADC1) == 0)
  {
    /* Note: Call of the functions below are commented because they are       */
    /*       useless in this example:                                         */
    /*       setting corresponding to default configuration from reset state. */
    
    /* Set ADC data resolution */
    // LL_ADC_SetResolution(ADC1, LL_ADC_RESOLUTION_12B);
    
    /* Set ADC conversion data alignment */
    // LL_ADC_SetResolution(ADC1, LL_ADC_DATA_ALIGN_RIGHT);
    
    /* Set Set ADC sequencers scan mode, for all ADC groups                   */
    /* (group regular, group injected).                                       */
    LL_ADC_SetSequencersScanMode(ADC1, LL_ADC_SEQ_SCAN_ENABLE);
    
  }
  
  
  /*## Configuration of ADC hierarchical scope: ADC group regular ############*/
  
  /* Note: Hardware constraint (refer to description of the functions         */
  /*       below):                                                            */
  /*       On this STM32 serie, setting of these features are not             */
  /*       conditioned to ADC state.                                          */
  /*       However, ADC state is checked anyway with standard requirements    */
  /*       (refer to description of this function).                           */
  if (LL_ADC_IsEnabled(ADC1) == 0)
  {
    /* Set ADC group regular trigger source */
    LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);
    
    /* Set ADC group regular trigger polarity */
    // LL_ADC_REG_SetTriggerEdge(ADC1, LL_ADC_REG_TRIG_EXT_RISING);
    
    /* Set ADC group regular continuous mode */
    LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);
    
    /* Set ADC group regular conversion data transfer */
    LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_UNLIMITED);
    
    /* Specify which ADC flag between EOC (end of unitary conversion)         */
    /* or EOS (end of sequence conversions) is used to indicate               */
    /* the end of conversion.                                                 */
    // LL_ADC_REG_SetFlagEndOfConversion(ADC1, LL_ADC_REG_FLAG_EOC_SEQUENCE_CONV);
    
    /* Set ADC group regular sequencer */
    /* Note: On this STM32 serie, ADC group regular sequencer is              */
    /*       fully configurable: sequencer length and each rank               */
    /*       affectation to a channel are configurable.                       */
    /*       Refer to description of function                                 */
    /*       "LL_ADC_REG_SetSequencerLength()".                               */
    
    /* Set ADC group regular sequencer length and scan direction */
    LL_ADC_REG_SetSequencerLength(ADC1, LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS);
    
    /* Set ADC group regular sequencer discontinuous mode */
    // LL_ADC_REG_SetSequencerDiscont(ADC1, LL_ADC_REG_SEQ_DISCONT_DISABLE);
    
    /* Set ADC group regular sequence: channel on the selected sequence rank. */
    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_4);
		LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_2, LL_ADC_CHANNEL_12);
		LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_3, LL_ADC_CHANNEL_13);
		LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_4, LL_ADC_CHANNEL_8);
		LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_5, LL_ADC_CHANNEL_11);
		LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_6, LL_ADC_CHANNEL_10);
		
//    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_2, LL_ADC_CHANNEL_VREFINT);
//    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_3, LL_ADC_CHANNEL_TEMPSENSOR);
  }
  
  
  /*## Configuration of ADC hierarchical scope: ADC group injected ###########*/
  
  /* Note: Hardware constraint (refer to description of the functions         */
  /*       below):                                                            */
  /*       On this STM32 serie, setting of these features are not             */
  /*       conditioned to ADC state.                                          */
  /*       However, ADC state is checked anyway with standard requirements    */
  /*       (refer to description of this function).                           */
  if (LL_ADC_IsEnabled(ADC1) == 0)
  {
    /* Note: Call of the functions below are commented because they are       */
    /*       useless in this example:                                         */
    /*       setting corresponding to default configuration from reset state. */
    
    /* Set ADC group injected trigger source */
    // LL_ADC_INJ_SetTriggerSource(ADC1, LL_ADC_INJ_TRIG_SOFTWARE);
    
    /* Set ADC group injected trigger polarity */
    // LL_ADC_INJ_SetTriggerEdge(ADC1, LL_ADC_INJ_TRIG_EXT_RISING);
    
    /* Set ADC group injected conversion trigger  */
    // LL_ADC_INJ_SetTrigAuto(ADC1, LL_ADC_INJ_TRIG_INDEPENDENT);
    
    /* Set ADC group injected sequencer */
    /* Note: On this STM32 serie, ADC group injected sequencer is             */
    /*       fully configurable: sequencer length and each rank               */
    /*       affectation to a channel are configurable.                       */
    /*       Refer to description of function                                 */
    /*       "LL_ADC_INJ_SetSequencerLength()".                               */
    
    /* Set ADC group injected sequencer length and scan direction */
    // LL_ADC_INJ_SetSequencerLength(ADC1, LL_ADC_INJ_SEQ_SCAN_DISABLE);
    
    /* Set ADC group injected sequencer discontinuous mode */
    // LL_ADC_INJ_SetSequencerDiscont(ADC1, LL_ADC_INJ_SEQ_DISCONT_DISABLE);
    
    /* Set ADC group injected sequence: channel on the selected sequence rank. */
    // LL_ADC_INJ_SetSequencerRanks(ADC1, LL_ADC_INJ_RANK_1, LL_ADC_CHANNEL_4);
  }
  
  
  /*## Configuration of ADC hierarchical scope: channels #####################*/
  
  /* Note: Hardware constraint (refer to description of the functions         */
  /*       below):                                                            */
  /*       On this STM32 serie, setting of these features are not             */
  /*       conditioned to ADC state.                                          */
  /*       However, in order to be compliant with other STM32 series          */
  /*       and to show the best practice usages, ADC state is checked.        */
  /*       Software can be optimized by removing some of these checks, if     */
  /*       they are not relevant considering previous settings and actions    */
  /*       in user application.                                               */
  if (LL_ADC_IsEnabled(ADC1) == 0)
  {
    /* Set ADC channels sampling time */
    /* Note: Considering interruption occurring after each ADC group          */
    /*       regular sequence conversions                                     */
    /*       (IT from DMA transfer complete),                                 */
    /*       select sampling time and ADC clock with sufficient               */
    /*       duration to not create an overhead situation in IRQHandler.      */
    /* Note: Set long sampling time due to internal channels (VrefInt,        */
    /*       temperature sensor) constraints.                                 */
    /*       Refer to description of function                                 */
    /*       "LL_ADC_SetChannelSamplingTime()".                               */
    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_4, LL_ADC_SAMPLINGTIME_56CYCLES);
    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_12, LL_ADC_SAMPLINGTIME_56CYCLES);
    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_13, LL_ADC_SAMPLINGTIME_56CYCLES);
		    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_8, LL_ADC_SAMPLINGTIME_56CYCLES);
		LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_11, LL_ADC_SAMPLINGTIME_56CYCLES);
		LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_10, LL_ADC_SAMPLINGTIME_56CYCLES);
//    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_VREFINT, LL_ADC_SAMPLINGTIME_480CYCLES);
//    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_TEMPSENSOR, LL_ADC_SAMPLINGTIME_480CYCLES);
    
  }
  
  
  /*## Configuration of ADC transversal scope: analog watchdog ###############*/
  
  /* Note: On this STM32 serie, there is only 1 analog watchdog available.    */
  
  /* Set ADC analog watchdog: channels to be monitored */
  // LL_ADC_SetAnalogWDMonitChannels(ADC1, LL_ADC_AWD_DISABLE);
  
  /* Set ADC analog watchdog: thresholds */
  // LL_ADC_SetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_HIGH, __LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B));
  // LL_ADC_SetAnalogWDThresholds(ADC1, LL_ADC_AWD_THRESHOLD_LOW, 0x000);
  
  
  /*## Configuration of ADC transversal scope: oversampling ##################*/
  
  /* Note: Feature not available on this STM32 serie */
  
  
  /*## Configuration of ADC interruptions ####################################*/
  /* Enable interruption ADC group regular end of unitary conversion          */
  /* or end of sequence conversions.                                          */
  /* Note: On this STM32 serie, ADC group regular end of conversion           */
  /*       must be selected among end of unitary conversion                   */
  /*       or end of sequence conversions.                                    */
  /*       Refer to function "LL_ADC_REG_SetFlagEndOfConversion()".           */
  LL_ADC_EnableIT_EOCS(ADC1);
  
  /* Enable interruption ADC group regular overrun */
  LL_ADC_EnableIT_OVR(ADC1);
  
  /* Note: in this example, ADC group regular end of conversions              */
  /*       (number of ADC conversions defined by DMA buffer size)             */
  /*       are notified by DMA transfer interruptions).                       */
  /*       ADC interruptions of end of conversion are enabled optionally,     */
  /*       as demonstration purpose in this example.                          */
  
}

/**
  * @brief  Perform ADC activation procedure to make it ready to convert
  *         (ADC instance: ADC1).
  * @note   Operations:
  *         - ADC instance
  *           - Enable ADC
  *         - ADC group regular
  *           none: ADC conversion start-stop to be performed
  *                 after this function
  *         - ADC group injected
  *           none: ADC conversion start-stop to be performed
  *                 after this function
  * @param  None
  * @retval None
  */
void Activate_ADC(void)
{
  #if (USE_TIMEOUT == 1)
  uint32_t Timeout = 0; /* Variable used for timeout management */
  #endif /* USE_TIMEOUT */
  
  /*## Operation on ADC hierarchical scope: ADC instance #####################*/
  
  /* Note: Hardware constraint (refer to description of the functions         */
  /*       below):                                                            */
  /*       On this STM32 serie, setting of these features are not             */
  /*       conditioned to ADC state.                                          */
  /*       However, in order to be compliant with other STM32 series          */
  /*       and to show the best practice usages, ADC state is checked.        */
  /*       Software can be optimized by removing some of these checks, if     */
  /*       they are not relevant considering previous settings and actions    */
  /*       in user application.                                               */
  if (LL_ADC_IsEnabled(ADC1) == 0)
  {
    /* Enable ADC */
    LL_ADC_Enable(ADC1);
		LL_ADC_REG_StartConversionSWStart(ADC1);
    
  }
  
  /*## Operation on ADC hierarchical scope: ADC group regular ################*/
  /* Note: No operation on ADC group regular performed here.                  */
  /*       ADC group regular conversions to be performed after this function  */
  /*       using function:                                                    */
  /*       "LL_ADC_REG_StartConversion();"                                    */
  
  /*## Operation on ADC hierarchical scope: ADC group injected ###############*/
  /* Note: No operation on ADC group injected performed here.                 */
  /*       ADC group injected conversions to be performed after this function */
  /*       using function:                                                    */
  /*       "LL_ADC_INJ_StartConversion();"                                    */
  
}





/**
  * @brief  DMA transfer complete callback
  * @note   This function is executed when the transfer complete interrupt
  *         is generated
  * @retval None
  */
void AdcDmaTransferComplete_Callback()
{
  /* Update status variable of DMA transfer */
  //ubDmaTransferStatus = 1;
	 if (LL_ADC_IsEnabled(ADC1) == 1)
  {
    LL_ADC_REG_StartConversionSWStart(ADC1);
  }
  else
  {
    /* Error: ADC conversion start could not be performed */
    LED_Blinking(LED_BLINK_ERROR);
  }
  
  /* Set LED depending on DMA transfer status */
  /* - Turn-on if DMA transfer is completed */
  /* - Turn-off if DMA transfer is not completed */
  //LED_On();
  
  /* For this example purpose, check that DMA transfer status is matching     */
  /* ADC group regular sequence status:                                       */
//  if (ubAdcGrpRegularSequenceConvStatus != 1)
 // {
 //   AdcDmaTransferError_Callback();
 // }
  
  /* Reset status variable of ADC group regular sequence */
 // ubAdcGrpRegularSequenceConvStatus = 0;
}

/**
  * @brief  DMA transfer error callback
  * @note   This function is executed when the transfer error interrupt
  *         is generated during DMA transfer
  * @retval None
  */

void AdcDmaTransferError_Callback()
{

  /* Error detected during DMA transfer */
  while(1)
		printf("!");
}

/**
  * @brief  ADC group regular end of sequence conversions interruption callback
  * @note   This function is executed when the ADC group regular 
  *         sequencer has converted all ranks of the sequence.
  * @retval None
  */
void AdcGrpRegularSequenceConvComplete_Callback()
{
	
	for(i=0; i <= 5; i++)
	{
		ADCAverage[i][averageCounter] =* (aADCxConvertedData+i);
	}
	averageCounter++;
	if(averageCounter==AVERAGESIZE)
		averageCounter=0;
  /* Update status variable of ADC group regular sequence */
  //ubAdcGrpRegularSequenceConvStatus = 1;
  //ubAdcGrpRegularSequenceConvCount++;
}

/**
  * @brief  ADC group regular overrun interruption callback
  * @note   This function is executed when ADC group regular
  *         overrun error occurs.
  * @retval None
  */
void AdcGrpRegularOverrunError_Callback(void)
{
  /* Note: Disable ADC interruption that caused this error before entering in */
  /*       infinite loop below.                                               */
  
  /* Disable ADC group regular overrun interruption */
  LL_ADC_DisableIT_OVR(ADC1);
	
  
  /* Error from ADC */
	while(1)
		printf("*");
}

uint16_t GetAverage(uint16_t x)
{
	tempTotal=0;
	for(j=0;j<AVERAGESIZE;j++)
	{
		tempTotal += ADCAverage[x][j];
	}
	return tempTotal/AVERAGESIZE;
}

uint16_t GetVoltagePA4(void)
{
	uhADCxConvertedData_PA4_mVolt        = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, GetAverage(0), LL_ADC_RESOLUTION_12B);
  return uhADCxConvertedData_PA4_mVolt*cS3;
}
uint16_t GetVoltagePC2(void)
{
	uhADCxConvertedData_PC2_mVolt            = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, GetAverage(1), LL_ADC_RESOLUTION_12B);
  return uhADCxConvertedData_PC2_mVolt*cS1;
}
uint16_t GetVoltagePC3(void)
{
	uhADCxConvertedData_PC3_mVolt = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, GetAverage(2), LL_ADC_RESOLUTION_12B);
	return uhADCxConvertedData_PC3_mVolt*cS2;
}
uint16_t GetVoltagePB0(void)
{
	uhADCxConvertedData_PB0_mVolt = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, GetAverage(3), LL_ADC_RESOLUTION_12B);
	return uhADCxConvertedData_PB0_mVolt*cS4;
}
uint16_t GetVoltagePC1(void)
{
	uhADCxConvertedData_PC1_mVolt = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, GetAverage(4), LL_ADC_RESOLUTION_12B);
	return uhADCxConvertedData_PC1_mVolt*cS5;
}

uint16_t GetVoltagePC0(void)
{
	uhADCxConvertedData_PC0_mVolt = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, GetAverage(5), LL_ADC_RESOLUTION_12B);
	return uhADCxConvertedData_PC0_mVolt*cS6;
}


void ADCPrintValue(void)
{
			
		printf("PC2:%u\r\n",GetVoltagePC2());//s1
		printf("PC3:%u\r\n",GetVoltagePC3());
    printf("PA4:%u\r\n",GetVoltagePA4());
		printf("PB0:%u\r\n",GetVoltagePB0());
		printf("PC1:%u\r\n",GetVoltagePC1());
		printf("PC0:%u\r\n",GetVoltagePC0());
	
	printf("\n\n");
//	printf("PC0:%u\r\n",__LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, aADCxConvertedData[0], LL_ADC_RESOLUTION_12B));
//	printf("PC0:%u\r\n",__LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, aADCxConvertedData[1], LL_ADC_RESOLUTION_12B));
//	printf("PC0:%u\r\n",__LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, aADCxConvertedData[2], LL_ADC_RESOLUTION_12B));
//	printf("PC0:%u\r\n",__LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, aADCxConvertedData[3], LL_ADC_RESOLUTION_12B));
//	printf("PC0:%u\r\n",__LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, aADCxConvertedData[4], LL_ADC_RESOLUTION_12B));
//	printf("PC0***:%u\r\n",__LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, aADCxConvertedData[5], LL_ADC_RESOLUTION_12B));
	
		
		printf("\n\n");
		
    
}


void CalCoef(void)
{
	cS1 = 450.0f/(GetVoltagePC2()*3);
	cS2 = 450.0f/(GetVoltagePC3()*3);
	cS3 = 450.0f/(GetVoltagePA4()*3);
	cS4 = 450.0f/(GetVoltagePB0()*3);
	cS5 = 450.0f/(GetVoltagePC1()*3);
	cS6 = 450.0f/(GetVoltagePC0()*3);
	state = 1;
}

