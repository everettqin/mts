#include <stdint.h> 

#ifndef __COMMON_H
#define __COMMON_H

/* Global macro -------------------------------------------------------------*/
/**
 * START_PROGRAMM		USER BUTTON			|									
 * ENC_1 						GPIOA_PIN15(CH1)|	GPIOB_PIN3(CH2)			| TIM2 
 * ENC_2 						GPIOB_PIN6(CH1)	|	GPIOB_PIN7(CH3)   		|	TIM4
 * PAPER_FEEDER			GPIOC_PIN6(CH1)	| 								|	TIM3
 * SENSOR_HEADER 		GPIOC_PIN8(CH3)	|	GPIOC_PIN9(CH4)	|	TIM3
 * SENSOR						GPIOC				| pin_2		pin_3	|	ADC
 */

/* ENC_1 Configuration ------------------------------------------------------*/
#define ENC_1_RESOLUTION			2000		// (1/rad)

/* definitions the timer */
#define ENC_1_TIMER 					TIM2 
#define ENC_1_TIMER_IQRn    	TIM2_IRQn
#define ENC_1_TIMER_CLK 			RCC_APB1Periph_TIM2 
#define ENC_1_COUNT() 				ENC_1_TIMER->CNT 

/* definitions for the quadrature encoder pins */ 
#define ENC_1_A_GPIO_PORT 		GPIOA 
#define ENC_1_A_GPIO_PIN 			GPIO_Pin_15 
#define ENC_1_A_GPIO_CLK 			RCC_AHB1Periph_GPIOA 
#define ENC_1_A_GPIO_SOURCE 	GPIO_PinSource15 
#define ENC_1_A_GPIO_AF 			GPIO_AF_TIM2 

#define ENC_1_B_GPIO_PORT 		GPIOB 
#define ENC_1_B_GPIO_PIN 			GPIO_Pin_3 
#define ENC_1_B_GPIO_CLK 			RCC_AHB1Periph_GPIOB 
#define ENC_1_B_GPIO_SOURCE 	GPIO_PinSource3 
#define ENC_1_B_GPIO_AF 			GPIO_AF_TIM2 


/* ENC_2 Configuration --------------------------------------------------------*/
/* definitions the timer */
#define ENC_2_TIMER 					TIM4 
#define ENC_2_TIMER_IQRn    	TIM4_IRQn
#define ENC_2_TIMER_CLK 			RCC_APB1Periph_TIM4 
#define ENC_2_COUNT() 				ENC_2_TIMER->CNT 

/* definitions for the quadrature encoder pins */ 
#define ENC_2_A_GPIO_PORT 		GPIOB 
#define ENC_2_A_GPIO_PIN 			GPIO_Pin_6 
#define ENC_2_A_GPIO_CLK 			RCC_AHB1Periph_GPIOB 
#define ENC_2_A_GPIO_SOURCE 	GPIO_PinSource6
#define ENC_2_A_GPIO_AF 			GPIO_AF_TIM4 

#define ENC_2_B_GPIO_PORT 		GPIOB 
#define ENC_2_B_GPIO_PIN 			GPIO_Pin_7 
#define ENC_2_B_GPIO_CLK 			RCC_AHB1Periph_GPIOB 
#define ENC_2_B_GPIO_SOURCE 	GPIO_PinSource7 
#define ENC_2_B_GPIO_AF 			GPIO_AF_TIM4 

/* Paper Feeder Configuration --------------------------------------------------------*/
/* definitions the signal */
#define PAPER_FEEDER_SIGNAL_FREQUENCY		10			//	(Hz)
#define PAPER_FEEDER_SIGNA_PERIOD				1 / PAPER_FEEDER_FREQUENCY	//	(sec)
#define	PAPER_FEEDER_SIGNA_WIDTH				0.5			//	(1)

/* definitions the timer */
#define PAPER_FEEDER_TIMER 				TIM3 
#define PAPER_FEEDER_TIMER_CLK 		RCC_APB1Periph_TIM3 

/* definitions the gpio pins */ 
#define PAPER_FEEDER_GPIO_PORT 		GPIOC 
#define PAPER_FEEDER_GPIO_PIN 		GPIO_Pin_6 
#define PAPER_FEEDER_GPIO_CLK 		RCC_AHB1Periph_GPIOC 
#define PAPER_FEEDER_GPIO_SOURCE 	GPIO_PinSource6
#define PAPER_FEEDER_GPIO_AF 			GPIO_AF_TIM3 

/* Sensor Header Configuration --------------------------------------------------------*/
/* definitions the signal */
#define SENSOR_HEADER_SIGNAL_FREQUENCY		10			//	(Hz)
#define SENSOR_HEADER_SIGNA_PERIOD				1 / SENSOR_HEADER_SIGNAL_FREQUENCY	//	(sec)
#define	SENSOR_HEADER_SIGNA_WIDTH				0.5			//	(1)

/* definitions the timer */
#define SENSOR_HEADER_TIMER 				TIM3 
#define SENSOR_HEADER_TIMER_CLK 		RCC_APB1Periph_TIM3 

/* definitions the gpio pins */ 
#define SENSOR_HEADER_C_GPIO_PORT 		GPIOC 
#define SENSOR_HEADER_C_GPIO_PIN 			GPIO_Pin_8 
#define SENSOR_HEADER_C_GPIO_CLK 			RCC_AHB1Periph_GPIOC 
#define SENSOR_HEADER_C_GPIO_SOURCE 	GPIO_PinSource8
#define SENSOR_HEADER_C_GPIO_AF 			GPIO_AF_TIM3 

#define SENSOR_HEADER_D_GPIO_PORT 		GPIOC 
#define SENSOR_HEADER_D_GPIO_PIN 			GPIO_Pin_9 
#define SENSOR_HEADER_D_GPIO_CLK 			RCC_AHB1Periph_GPIOC 
#define SENSOR_HEADER_D_GPIO_SOURCE 	GPIO_PinSource9
#define SENSOR_HEADER_D_GPIO_AF 			GPIO_AF_TIM3 

/* Sensor Configuration --------------------------------------------------------*/
/* definitions the ADC */
#define SENSOR_A_ADC 							ADC3 
#define SENSOR_A_ADC_CLK 					RCC_APB2Periph_ADC3 

#define SENSOR_B_ADC 							ADC4 
#define SENSOR_B_ADC_CLK 					RCC_APB2Periph_ADC4 

/* definitions the gpio */ 
#define SENSOR_A_GPIO_PORT 			GPIOC
#define SENSOR_A_GPIO_PIN 			GPIO_Pin_2 
#define SENSOR_A_GPIO_CLK 			RCC_AHB1Periph_GPIOC 

#define SENSOR_B_GPIO_PORT 			GPIOC 
#define SENSOR_B_GPIO_PIN 			GPIO_Pin_3 
#define SENSOR_B_GPIO_CLK 			RCC_AHB1Periph_GPIOC 

/* Global variable ------------------------------------------------------------*/
extern uint32_t ENCA_value;
extern uint32_t ENCB_value;
extern uint32_t ENC_count;
extern uint32_t IRQ_count;

extern void Common_Variable_Init(void);

#endif /* __COMMON_H */	


