#include "RTG.h"
#include "I2C.h"
/**
 * This is the main function for the I2C testing.
 * The data received from server will be received initially by I2C2, transmit
 * to I2C4, and then transmit back to I2C2 to check if the data is the same.
 */
uint8_t i2c_test(uint8_t iter, uint8_t data_length, uint8_t *data)
{
	uint8_t i2c2_buff[data_length] = { 0 }; // init the buffer to be full '\0'
	uint8_t i2c4_buff[data_length] = { 0 }; // init the buffer to be full '\0'
	uint8_t result = RETURN_SUCCESS;

	for(uint8_t i = 0; i < iter ; i++)
	{
		i2c_tran_to_slave(I2C_2, I2C_4, data_length, data, i2c4_buff);
		i2c_tran_to_master(I2C_4, I2c_2, data_length, i2c4_buff, i2c2_buff);

		if(strncmp((char *)i2c2_buff, (char *)data, data_length) != 0)
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
void i2c_tran_to_slave(	I2C_HandleTypeDef *i2c_transmit,
						I2C_HandleTypeDef *i2c_receive,
						uint8_t data_length,
						uint8_t *transmit_buff,
						uint8_t *receive_buff )
{
	HAL_I2C_Slave_Receive_IT(i2c_receive, receive_buff, data_length);
	HAL_I2C_Master_Transmit_IT(i2c_transmit, SLAVE_ADDR, transmit_buff, data_length);
}

/**
 * This function will send the data from I2C slave to I2c master.
 */
void i2c_tran_to_master(	I2C_HandleTypeDef *i2c_transmit,
							I2C_HandleTypeDef *i2c_receive,
							uint8_t data_length,
							uint8_t *transmit_buff,
							uint8_t *receive_buff )
{
	HAL_I2C_Master_Receive_IT(i2c_receive, SLAVE_ADDR, receive_buff, data_length);
	HAL_I2C_Slave_Transmit_IT(i2c_transmit, transmit_buff, data_length);
}
