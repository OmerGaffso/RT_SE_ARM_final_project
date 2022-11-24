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

		/// The ADC is not in range.
		if ( adc_read < LOWER_BOUND || UPPER_BOUND < adc_read )
			return FAILURE;

	}
	return SUCCESS;
}

