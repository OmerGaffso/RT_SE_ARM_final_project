#include "RTG.h"
#include "ADC.h"

/// Count the number of conversions completed, to make sure the conversion
/// happens at every new loop iteration.
uint8_t convert_cnt;

uint8_t adc_test(uint8_t iter)
{
	uint16_t adc_read = INIT_VALUE;
	// Enables ADC DMA. Sets it's buffer to adc_read and requests 1 read
	HAL_ADC_Start_DMA(ADC_HANDLE, (uint32_t *) &adc_read, READ_BUFF);

	// Initiate the read counter to 0
	convert_cnt = INIT_VALUE;

	for(uint8_t i = 0; i < iter; i++)
	{
		// read the value and store it in adc_read
		HAL_ADC_Start(ADC_HANDLE);

		/// check if the ADC read value is out of valid range
		if ( adc_read < LOWER_BOUND || UPPER_BOUND < adc_read )
			return FAILURE;
	}
	if(convert_cnt != iter)
		return FAILURE;

	return SUCCESS;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	++convert_cnt;
}
