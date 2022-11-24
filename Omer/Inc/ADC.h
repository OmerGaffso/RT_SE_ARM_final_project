/**
 * This file will be responsible for all ADC definitions and functions.
 */

#ifndef RTG_ARM_PROJECT_ADC
#define RTG_ARM_PROJECT_ADC

extern ADC_HandleTypeDef hadc2;

#define ADC_HANDLE &hadc2 			// ADC Handle

//3.3 volts will be represented as 4096 in digital value.
#define MAX_VOLTAGE 4096U
#define ALLOWED_DEVIATION 100U	//The deviation can be +100/-100

/// The voltage we read must be in range:  3996 <= read_volt <= 4196
#define UPPER_BOUND MAX_VOLTAGE + ALLOWED_DEVIATION // 4196U
#define LOWER_BOUND MAX_VOLTAGE - ALLOWED_DEVIATION // 3996U

#define READ_BUFF 1				//We read the ADC one time each iteration

/**
 * This is the main function for the ADC testing.
 * We will run a loop for the received number of iterations, in each one of
 * them sample the ADC value (connected to steady 3.3 volts), and compare them
 * to the maximum value we can receive - 4096 (allowing deviation of +-100).
 * @param iter - number of iteration for the test
 * @return 0x01 (SUCCESS macro) if the test ended successfully (sample value
 * between 3996 and 4196), and 0xff (FAILURE macro) if ended unsuccessfully.
 */
uint8_t adc_test(uint8_t iter);

/**
 * Checks that the ConvCpltCallback was called (turn on the adc_complete flag),
 * and that the value read is in accepted range.
 * @param adc_read - the value that was read during the loop iteration
 * @return TRUE (1) if the conditions passed, FALSE (0) if one of the conditions
 * failed.
 */
uint8_t adc_test_conditions(uint32_t adc_read);


#endif
