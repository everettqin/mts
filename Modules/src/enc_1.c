#include "enc_1.h"

void ENC_1_Init(void);
void ENC_1_Start(void);
void ENC_1_GetStatus(void);
void ENC_1_GPIO_Init(void);
void ENC_1_TIM_Init(void);

uint32_t ENC_1_A_value		= 0;
uint32_t ENC_1_B_value		= 0;
uint32_t ENC_1_count			= 0;

void ENC_1_Init (void) {
	ENC_1_GPIO_Init();
	ENC_1_TIM_Init();
}

void ENC_1_Start(void) {	
	/* turn on the timer/counters */ 
	TIM_Cmd (ENC_1_TIMER, ENABLE);
}

void ENC_1_GetStatus(void){
		ENC_1_A_value 	= GPIO_ReadInputDataBit(ENC_1_A_GPIO_PORT, ENC_1_A_GPIO_PIN);
		ENC_1_B_value 	= GPIO_ReadInputDataBit(ENC_1_B_GPIO_PORT, ENC_1_B_GPIO_PIN);
		ENC_1_count 	= ENC_1_COUNT();
}
	
/**
  * @brief  Configure the Pins Channel of ENC.
  * @param  None
  * @retval None
  */
void ENC_1_GPIO_Init(void){
	/* Private typedef -----------------------------------------------------------*/
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* GPIOD Periph clock enable */	
	RCC_AHB1PeriphClockCmd 				(ENC_1_A_GPIO_CLK, ENABLE); 
	RCC_AHB1PeriphClockCmd 				(ENC_1_B_GPIO_CLK, ENABLE); 

	/* Configure Pins(ENCA -> PA15, ENCB -> PB3) as input with pushpull mode */
	GPIO_StructInit 							(&GPIO_InitStructure); 
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP; 
	
	GPIO_InitStructure.GPIO_Pin 	= ENC_1_A_GPIO_PIN; 
	GPIO_Init 										(ENC_1_A_GPIO_PORT, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin 	= ENC_1_B_GPIO_PIN; 
	GPIO_Init 										(ENC_1_B_GPIO_PORT, &GPIO_InitStructure); 

	/* Connect the pins to their Alternate Functions */ 
	GPIO_PinAFConfig 							(ENC_1_A_GPIO_PORT, ENC_1_A_GPIO_SOURCE, ENC_1_A_GPIO_AF); 
	GPIO_PinAFConfig 							(ENC_1_B_GPIO_PORT, ENC_1_B_GPIO_SOURCE, ENC_1_B_GPIO_AF); 

}

/**
  * @brief  Configure the TIM Init and IRQ Handler.
  * @param  None
  * @retval None
  */
void ENC_1_TIM_Init(void) {	
	/* Private typedef -----------------------------------------------------------*/
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	/* Timer peripheral clock enable */
	RCC_APB1PeriphClockCmd 				(ENC_1_TIMER_CLK, ENABLE); 
	
	/** 
	* set them up as encoder inputs 
	* set both inputs to rising polarity to let it use both edges
	*/
	TIM_EncoderInterfaceConfig 		(ENC_1_TIMER, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling); 
	TIM_SetAutoreload 						(ENC_1_TIMER, 0xfff); 
	 
	/* clear the interrupt */
	TIM_ClearFlag(ENC_1_TIMER, TIM_FLAG_Update);
	
	/* enable TIM2 Interrupt */
  TIM_ITConfig(ENC_1_TIMER, TIM_IT_Update, ENABLE);
	
	/* Enable the TIM2 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel 										= ENC_1_TIMER_IQRn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority 				= 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd 								= ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
