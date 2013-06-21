/**
  ******************************************************************************
  * @file    MTS/Scanner/paper_feeder.c 
  * @author  Yifeng Qin & Sabastian
  * @version V0.1.0
  * @date    19-Juni-2013
  * @brief   Paper Feed
  ******************************************************************************
  * @attention
  *	none
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "paper_feeder.h"
#include "enc_1.h"
#include "common.h"
#include "stm32f4xx_conf.h" 

/* Private macro -------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void PAPER_FEEDER_TIM_Init (void);
void PAPER_FEEDER_GPIO_Init(void);
void PAPER_FEEDER_Init(void);
void PAPER_FEEDER_Start(void);
void PAPER_FEEDER_Move(int16_t distance);


/**
  * @brief  Configure the Timer.
  * @param  None
  * @retval None
  */
void PAPER_FEEDER_TIM_Init(void) {
	/* Private typedef -----------------------------------------------------------*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  			TIM_OCInitStructure;
	
	/* Private variables ---------------------------------------------------------*/
	uint16_t CCR_Val = 333;
	uint16_t PrescalerValue = 0;
	
	/* TIMER clock enable */
  RCC_APB1PeriphClockCmd(PAPER_FEEDER_TIMER_CLK, ENABLE);
	
	/* Compute the prescaler value */
  PrescalerValue = (uint16_t) ((SystemCoreClock /2) / 28000000) - 1;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period 				= 665;
  TIM_TimeBaseStructure.TIM_Prescaler 		= PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;

  TIM_TimeBaseInit(PAPER_FEEDER_TIMER, &TIM_TimeBaseStructure);

  /* PWM Mode configuration */
  TIM_OCInitStructure.TIM_OCMode 					= TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState 		= TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse 					= CCR_Val;
  TIM_OCInitStructure.TIM_OCPolarity 			= TIM_OCPolarity_High;

  TIM_OC1Init(PAPER_FEEDER_TIMER, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(PAPER_FEEDER_TIMER, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(PAPER_FEEDER_TIMER, ENABLE);
	
}
/**
  * @brief  Configure the GPIO Ouput.
  * @param  None
  * @retval None
  */
void PAPER_FEEDER_GPIO_Init (void) {
	/* Private typedef -----------------------------------------------------------*/
	GPIO_InitTypeDef 				GPIO_InitStructure;
	
  /* GPIO clock enable */
  RCC_AHB1PeriphClockCmd(PAPER_FEEDER_GPIO_CLK, ENABLE);
   
  /* GPIO Configuration */
  GPIO_InitStructure.GPIO_Pin 		= PAPER_FEEDER_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_UP ;
  GPIO_Init(PAPER_FEEDER_GPIO_PORT, &GPIO_InitStructure); 

  /* Connect TIM3 pins to AF2 */  
  GPIO_PinAFConfig(PAPER_FEEDER_GPIO_PORT, PAPER_FEEDER_GPIO_SOURCE, PAPER_FEEDER_GPIO_AF);
}

void PAPER_FEEDER_Init(void){
	PAPER_FEEDER_GPIO_Init();
	PAPER_FEEDER_TIM_Init();
}

void PAPER_FEEDER_Start(void){
	TIM_Cmd(PAPER_FEEDER_TIMER, ENABLE);
}

void PAPER_FEEDER_Move(int16_t distance) {
	ENC_1_Init();
	ENC_1_Start();
	
	PAPER_FEEDER_Init();
	PAPER_FEEDER_Start();
}
