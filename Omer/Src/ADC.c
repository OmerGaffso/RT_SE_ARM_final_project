#include "RTG.h"
#include "ADC.h"

uint8_t adc_complete = FALSE;

uint8_t adc_test(uint8_t iter)
{
	uint16_t adc_read = INIT_VALUE;

	HAL_ADC_Start_DMA(ADC_HANDLE, (uint32_t *) &adc_read, READ_BUFF);
	while(iter--)
	{
		HAL_ADC_Start(ADC_HANDLE);

		if (!adc_test_conditions(adc_read))
			return FAILURE;

		adc_read = INIT_VALUE;
	}

	return SUCCESS;
}

/**
 * Checks that the test conditions are correct.
 */
uint8_t adc_test_conditions(uint32_t adc_read)
{
	/// The ADC wasn't sampled.
	if (!adc_complete)
		return FALSE;

	/// The ADC is not in range.
	if ( adc_read < LOWER_BOUND || UPPER_BOUND < adc_read )
		return FALSE;

	return TRUE;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if ( hadc == ADC_HANDLE )
		adc_complete = TRUE;
}
