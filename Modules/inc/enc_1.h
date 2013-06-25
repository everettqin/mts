#ifndef __ENC_1_H
#define __ENC_1_H

#include "common.h"
#include "stm32f4xx_conf.h" 

/* Private function prototypes -----------------------------------------------*/
extern void ENC_1_Init(int16_t distance);
extern void ENC_1_Start(void);
extern void ENC_1_GetStatus(void);

#endif
