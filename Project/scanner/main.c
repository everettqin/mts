/**
  ******************************************************************************
  * @file    MTS/Scanner/main.c 
  * @author  Yifeng Qin & Sabastian
  * @version V0.1.0
  * @date    19-Juni-2013
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *	none
  ******************************************************************************  
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h" 
#include "common.h"
#include "buttons.h"
#include "enc_1.h"
#include "enc_2.h"
#include "sensor_header.h"
#include "sensor.h"

/** @addtogroup MTS
  * @{
  */

/** @addtogroup Scanner
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint8_t MainState = DISABLE; 

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */

int main(void)
{	
	BUTTON_USER_Start();
	
	//SENSOR_HEADER_Init();
	//SENSOR_HEADER_Start();
	
	//SENSOR_Init();
	//SENSOR_Start();
	
	while(1){
		ENC_1_GetStatus();
	}
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
