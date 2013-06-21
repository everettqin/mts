/**
  ******************************************************************************
  * @file    MTS/Scanner/sensor_header.c 
  * @author  Yifeng Qin & Sabastian
  * @version V0.1.0
  * @date    19-Juni-2013
  * @brief   Sensor Header
  ******************************************************************************
  * @attention
  *	none
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "sensor_header.h"
#include "common.h"
#include "stm32f4xx_conf.h" 

/* Private macro -------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void SENSOR_HEADER_Init(void);
void SENSOR_HEADER_Start(void);
void SENSOR_HEADER_TIM_Init (void);
void SENSOR_HEADER_GPIO_Init(void);

/**
  * @brief  Configure the Timer.
  * @param  None
  * @retval None
  */
void SENSOR_HEADER_TIM_Init(void) {
	/* Private typedef -----------------------------------------------------------*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  			TIM_OCInitStructure;
	
	/* Private variables ---------------------------------------------------------*/
	uint16_t CCR_Val = 333;
	uint16_t PrescalerValue = 0;
	
	/* TIMER clock enable */
  RCC_APB1PeriphClockCmd(SENSOR_HEADER_TIMER_CLK, ENABLE);
	
	/* Compute the prescaler value */
  PrescalerValue = (uint16_t) ((SystemCoreClock /2) / 28000000) - 1;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period 				= 665;
  TIM_TimeBaseStructure.TIM_Prescaler 		= PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;

  TIM_TimeBaseInit(SENSOR_HEADER_TIMER, &TIM_TimeBaseStructure);

  /* PWM Mode configuration */
  TIM_OCInitStructure.TIM_OCMode 					= TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState 		= TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse 					= CCR_Val;
  TIM_OCInitStructure.TIM_OCPolarity 			= TIM_OCPolarity_High;
	
	/* PWM1 Mode configuration: Channel3 */
  TIM_OC3Init(SENSOR_HEADER_TIMER, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(SENSOR_HEADER_TIMER, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OC4Init(SENSOR_HEADER_TIMER, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(SENSOR_HEADER_TIMER, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(SENSOR_HEADER_TIMER, ENABLE);
	
}
/**
  * @brief  Configure the GPIO Ouput.
  * @param  None
  * @retval None
  */
void SENSOR_HEADER_GPIO_Init (void) {
	/* Private typedef -----------------------------------------------------------*/
	GPIO_InitTypeDef 				GPIO_InitStructure;
	
  /* GPIO clock enable */
  RCC_AHB1PeriphClockCmd(SENSOR_HEADER_C_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(SENSOR_HEADER_D_GPIO_CLK, ENABLE);
   
  /* GPIO Configuration */
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType 	= GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd 		= GPIO_PuPd_UP ;
	
	GPIO_InitStructure.GPIO_Pin 		= SENSOR_HEADER_C_GPIO_PIN;
  GPIO_Init(SENSOR_HEADER_C_GPIO_PORT, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin 		= SENSOR_HEADER_D_GPIO_PIN;
  GPIO_Init(SENSOR_HEADER_D_GPIO_PORT, &GPIO_InitStructure); 

  /* Connect TIM3 pins to AF2 */  
  GPIO_PinAFConfig(SENSOR_HEADER_C_GPIO_PORT, SENSOR_HEADER_C_GPIO_SOURCE, SENSOR_HEADER_C_GPIO_AF);
	GPIO_PinAFConfig(SENSOR_HEADER_D_GPIO_PORT, SENSOR_HEADER_D_GPIO_SOURCE, SENSOR_HEADER_C_GPIO_AF);

}

void SENSOR_HEADER_Init(void){
	SENSOR_HEADER_GPIO_Init();
	SENSOR_HEADER_TIM_Init();
}

void SENSOR_HEADER_Start(void){
	TIM_Cmd(SENSOR_HEADER_TIMER, ENABLE);
}
