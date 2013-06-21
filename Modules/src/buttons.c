#include "buttons.h"
#include "stm32f4_discovery.h"

void BUTTON_USER_Start(void);

void BUTTON_USER_Start(void) {
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
}
