#include "sensor.h"
#include "common.h"
#include "stm32f4xx_conf.h" 

/* Private define ------------------------------------------------------------*/
#define ADC_CDR_ADDRESS     ((uint32_t)0x40012308) // ADC common regular data register for dual and trple modes
__IO uint16_t SENSOR_DualConvertedValue[2];
__IO uint16_t SENSOR_A_VoltValue = 0;
__IO uint16_t SENSOR_B_VoltValue = 0;

void SENSOR_Init(void);
void SENSOR_Start(void);
void SENSOR_GetStatus(void);

void SENSOR_GPIO_Init(void);
void SENSOR_DMA_Init(void);
void SENSOR_ADC_Init(void);

void SENSOR_DMA_Init(void) {
  DMA_InitTypeDef       DMA_InitStructure;

  /* Enable DMA2 clocks ****************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

  DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC_CDR_ADDRESS;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&SENSOR_DualConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 2;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);

  /* DMA2_Stream0 enable */
  DMA_Cmd(DMA2_Stream0, ENABLE);
}


void SENSOR_ADC_Init(void) {
	
 	ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2, ENABLE);
												 
/* ADC Common configuration *************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_DualMode_Interl;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_2;  
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2; 
  ADC_CommonInit(&ADC_CommonInitStructure);

  /* ADC1 regular channel 12 configuration ************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
		
  ADC_Init(ADC1, &ADC_InitStructure);
  ADC_Init(ADC2, &ADC_InitStructure);

  ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 1, ADC_SampleTime_3Cycles);
  ADC_RegularChannelConfig(ADC2, ADC_Channel_13, 1, ADC_SampleTime_3Cycles);

  /* Enable DMA request after last transfer (multi-ADC mode) ******************/
  ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);

  /* Enable ADC **************************************************************/
  ADC_Cmd(ADC1, ENABLE);
  ADC_Cmd(ADC2, ENABLE);
	
	/* Enable DMA2 Stream0 Transfer complete interrupt */
	DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE);

	/* Enable ADC1 DMA since ADC1 is the Master*/
	ADC_DMACmd(ADC1, ENABLE);
}


void SENSOR_GPIO_Init(void){
	/* Private typedef -----------------------------------------------------------*/
	GPIO_InitTypeDef      GPIO_InitStructure;
	
 	/* GPIOD Periph clock enable */	
 	RCC_AHB1PeriphClockCmd 				(SENSOR_A_GPIO_CLK, ENABLE); 
 	RCC_AHB1PeriphClockCmd 				(SENSOR_B_GPIO_CLK, ENABLE); 

 	/* Configure Pins as analog input with pushpull mode */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	
	GPIO_InitStructure.GPIO_Pin = SENSOR_A_GPIO_PIN;
  GPIO_Init(SENSOR_A_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SENSOR_B_GPIO_PIN;
  GPIO_Init(SENSOR_B_GPIO_PORT, &GPIO_InitStructure);
}
void SENSOR_Init(void) {
	NVIC_InitTypeDef NVIC_InitStructure;

	SENSOR_DMA_Init();
	SENSOR_GPIO_Init();
	SENSOR_ADC_Init();
	  /* Enable the DMA2 Stream0 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void SENSOR_Start(void) {
  ADC_SoftwareStartConv(ADC1);
}

void SENSOR_GetStatus(void) {
	/* The Voltage Range of ADC is in 0V~3V */
	SENSOR_A_VoltValue = ADC_GetConversionValue(ADC1) * 3000/0xfff;
	SENSOR_B_VoltValue = ADC_GetConversionValue(ADC2) * 3000/0xfff;
}


