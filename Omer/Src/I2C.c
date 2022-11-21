#include "RTG.h"
#include "I2C.h"
/**
 * This is the main function for the I2C testing.
 * The data received from server will be received initially by I2C2, transmit
 * to I2C4, and then transmit back to I2C2 to check if the data is the same.
 * @param iter - number of iteration for the test
 * @param data_length - the length of string to transmit and receive
 * @param data - the string data to transmit and receive
 * @return 0x01 if the tests passed successfully, or 0xff if tests failed.
 */
uint8_t i2c_test(uint8_t iter, uint8_t data_length, uint8_t *data)
{
	uint8_t i2c2_buff[data_length] = { 0 }; // init the buffer to be full '\0'
	uint8_t i2c4_buff[data_length] = { 0 }; // init the buffer to be full '\0'
	uint8_t result = RETURN_SUCCESS;

	for(uint8_t i = 0; i < iter ; i++)
	{
		i2c_tran_to_slave(data_length, data, i2c4_buff);
		i2c_tran_to_master(data_length, i2c4_buff, i2c2_buff);

		if(strncmp((char *)uart4_buff, (char *)data, data_length) != 0)
		{
			result = RETURN_FAILURE;
			break;
		}
	}
	return result;
}

/**
 * This function will send the data from I2C master to I2C slave.
 */
void i2c_tran_to_slave(	uint8_t data_length,
						uint8_t *transmit_buff,
						uint8_t *receive_buff )
{
	HAL_I2C_Slave_Receive_DMA(I2C_4, receive_buff, data_length);
	HAL_I2C_Master_Transmit_DMA(I2C_2, SLAVE_ADDR, transmit_buff, data_length);
}

/**
 * This function will send the data from I2C slave to I2c master.
 */
void i2c_tran_to_master(	uint8_t data_length,
							uint8_t *transmit_buff,
							uint8_t *receive_buff )
{
	HAL_I2C_Master_Receive_DMA(I2C_2, SLAVE_ADDR, receive_buff, data_length);
	HAL_I2C_Slave_Transmit_DMA(I2C_4, transmit_buff, data_length);
}
