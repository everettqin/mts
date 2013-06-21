#include "enc_2.h"

void ENC_2_Init(void);
void ENC_2_Start(void);
void ENC_2_GetStatus(void);
void ENC_2_GPIO_Init(void);
void ENC_2_TIM_Init(void);

uint32_t ENC_2_A_value		= 0;
uint32_t ENC_2_B_value		= 0;
uint32_t ENC_2_count			= 0;

void ENC_2_Init (void) {
	ENC_2_GPIO_Init();
	ENC_2_TIM_Init();
}

void ENC_2_Start(void) {	
	/* turn on the timer/counters */ 
	TIM_Cmd (ENC_2_TIMER, ENABLE);
}

void ENC_2_GetStatus(void){
		ENC_2_A_value 	= GPIO_ReadInputDataBit(ENC_2_A_GPIO_PORT, ENC_2_A_GPIO_PIN);
		ENC_2_B_value 	= GPIO_ReadInputDataBit(ENC_2_B_GPIO_PORT, ENC_2_B_GPIO_PIN);
		ENC_2_count 	= ENC_2_COUNT();
}
	
/**
  * @brief  Configure the Pins Channel of ENC.
  * @param  None
  * @retval None
  */
void ENC_2_GPIO_Init(void){
	/* Private typedef -----------------------------------------------------------*/
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* GPIOD Periph clock enable */	
	RCC_AHB1PeriphClockCmd 				(ENC_2_A_GPIO_CLK, ENABLE); 
	RCC_AHB1PeriphClockCmd 				(ENC_2_B_GPIO_CLK, ENABLE); 

	/* Configure Pins(ENCA -> PA15, ENCB -> PB3) as input with pushpull mode */
	GPIO_StructInit 							(&GPIO_InitStructure); 
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF; 
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP; 
	
	GPIO_InitStructure.GPIO_Pin 	= ENC_2_A_GPIO_PIN; 
	GPIO_Init 										(ENC_2_A_GPIO_PORT, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin 	= ENC_2_B_GPIO_PIN; 
	GPIO_Init 										(ENC_2_B_GPIO_PORT, &GPIO_InitStructure); 

	/* Connect the pins to their Alternate Functions */ 
	GPIO_PinAFConfig 							(ENC_2_A_GPIO_PORT, ENC_2_A_GPIO_SOURCE, ENC_2_A_GPIO_AF); 
	GPIO_PinAFConfig 							(ENC_2_B_GPIO_PORT, ENC_2_B_GPIO_SOURCE, ENC_2_B_GPIO_AF); 

}

/**
  * @brief  Configure the TIM Init and IRQ Handler.
  * @param  None
  * @retval None
  */
void ENC_2_TIM_Init(void) {	
	/* Private typedef -----------------------------------------------------------*/
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	/* Timer peripheral clock enable */
	RCC_APB1PeriphClockCmd 				(ENC_2_TIMER_CLK, ENABLE); 
	
	/** 
	* set them up as encoder inputs 
	* set both inputs to rising polarity to let it use both edges
	*/
	TIM_EncoderInterfaceConfig 		(ENC_2_TIMER, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling); 
	TIM_SetAutoreload 						(ENC_2_TIMER, 0xffffff); 
	 
	/* clear the interrupt */
	TIM_ClearFlag(ENC_2_TIMER, TIM_FLAG_Update);
	
	/* enable TIM2 Interrupt */
  TIM_ITConfig(ENC_2_TIMER, TIM_IT_Update, ENABLE);
	
	/* Enable the TIM2 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel 										= ENC_2_TIMER_IQRn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority 				= 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd 								= ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
