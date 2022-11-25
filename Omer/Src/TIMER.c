#include "RTG.h"
#include "TIMER.h"

uint8_t second_passed;

/**
 * This is the main function of timer test. This function will control the
 * test run.
 */
uint8_t timer_test(uint8_t iter)
{
	for(uint8_t i = 0; i < iter ; ++i)
	{
		// sets flag to 0 before starting.
		second_passed = FALSE;
		// get current tick
		uint32_t tickstart = HAL_GetTick();
		// start the tested timer
		HAL_TIM_Base_Start_IT(TIMER);

		count_1_second(tickstart);
		if (second_passed)
			continue;

		return FAILURE;
	}
	return SUCCESS;
}

/**
 * This function count one second.
 */
void count_1_second(uint32_t tickstart)
{
	while(HAL_GetTick() - tickstart < SECOND_IN_MILLISECONS + TIMER_DEVIEATION);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_TIM_Base_Stop_IT(TIMER);
	second_passed = TRUE;
}

