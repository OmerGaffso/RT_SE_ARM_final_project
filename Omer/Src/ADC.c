#include "RTG.h"
#include "ADC.h"


// flag to indicate convert complete
uint8_t adc_read;

uint8_t adc_test(uint8_t iter)
{
	uint16_t adc_read = INIT_VALUE;
	// Enables ADC DMA. Sets it's buffer to adc_read and requests 1 read
	HAL_ADC_Start_DMA(ADC_HANDLE, (uint32_t *) &adc_read, READ_BUFF);

	for(uint8_t i = 0; i < iter; i++)
	{
		// read the value and store it in adc_read
		HAL_ADC_Start(ADC_HANDLE);

		adc_delay_till_read();

		// check if the ADC read value is out of valid range
		if ( adc_read < LOWER_BOUND || UPPER_BOUND < adc_read )
			return FAILURE;
	}

	return SUCCESS;
}

/// Delay until enters HAL_ADC_ConvCpltCallback
void adc_delay_till_read()
{
	uint8_t tickstart = HAL_GetTick();
	while (adc_read != TRUE)
	{
		if (HAL_GetTick() - tickstart > SECOND_IN_MILLISECONS)
			break;
	}
	adc_read = FALSE;
}

// enter here after convert complete
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	adc_read = TRUE;
}
