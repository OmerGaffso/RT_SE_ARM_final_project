#include "RTG.h"
#include "I2C.h"

/// Flags to be used in call backs
uint8_t i2c_tx_done_flag = FALSE;		// Flag to notify complete transmit
uint8_t i2c_rx_done_flag = FALSE;		// Flag to notify complete received

/**
 * This is the main function for the I2C testing.
 * The data received from server will be received initially by I2C2, transmit
 * to I2C1, and then transmit back to I2C2 to check if the data is the same.
 */
uint8_t i2c_test(uint8_t iter, uint8_t data_length, uint8_t *data)
{
	uint8_t i2c2_buff[DATA_SIZE] = { 0 }; // init the buffer to be full '\0'
	uint8_t i2c4_buff[DATA_SIZE] = { 0 }; // init the buffer to be full '\0'
	uint8_t result = SUCCESS;

	for(uint8_t i = 0; i < iter ; i++)
	{
		i2c_transmit_to_slave(I2C_MASTER, I2C_SLAVE, data_length, data, i2c4_buff);
		i2c_delay_till_received();
		i2c_transmit_to_master(I2C_SLAVE, I2C_MASTER, data_length, i2c4_buff, i2c2_buff);
		i2c_delay_till_received();

		if(strncmp((char *)i2c2_buff, (char *)data, data_length) != 0)
		{
			result = FAILURE;
			return result;
		}
	}
	return result;
}

/**
 * This function will send the data from I2C master to I2C slave.
 */
void i2c_transmit_to_slave(	I2C_HandleTypeDef *i2c_transmit,
							I2C_HandleTypeDef *i2c_receive,
							uint8_t data_length,
							uint8_t *transmit_buff,
							uint8_t *receive_buff )
{
	HAL_I2C_Slave_Receive_DMA(i2c_receive, receive_buff, data_length);
	HAL_I2C_Master_Transmit_DMA(i2c_transmit, SLAVE_ADDR, transmit_buff, data_length);
	i2c_delay_till_transmited();
}

/**
 * This function will send the data from I2C slave to I2C master.
 */
void i2c_transmit_to_master(I2C_HandleTypeDef *i2c_transmit,
							I2C_HandleTypeDef *i2c_receive,
							uint8_t data_length,
							uint8_t *transmit_buff,
							uint8_t *receive_buff )
{
	HAL_I2C_Master_Receive_DMA(i2c_receive, SLAVE_ADDR, receive_buff, data_length);
	HAL_I2C_Slave_Transmit_DMA(i2c_transmit, transmit_buff, data_length);
	i2c_delay_till_transmited();
}

/// Delay until enters HAL_I2C_TxCpltCallback changes flag to true
void i2c_delay_till_transmited()
{
	while(i2c_tx_done_flag != TRUE);	// TODO: add timeout to loop (for hardware problem cases)
	i2c_tx_done_flag = FALSE;
}

/// Delay until enters HAL_I2C_Rx_CpltCallback changes flag to true
void i2c_delay_till_received()
{
	while(i2c_rx_done_flag != TRUE);	// TODO: add timeout to loop (for hardware problem cases)
	i2c_rx_done_flag = FALSE;
}

/// Enters here upon completed I2C master transmit
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(hi2c == I2C_MASTER)
		i2c_tx_done_flag = TRUE;
}

/// Enters here upon completed I2C master receive
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if (hi2c == I2C_MASTER)
		i2c_rx_done_flag = TRUE;
}

/// Enters here upon completed I2C slave transmit
void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if (hi2c == I2C_SLAVE)
		i2c_tx_done_flag = TRUE;
}

/// Enters here upon completed I2C slave receive
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if (hi2c == I2C_SLAVE)
		i2c_rx_done_flag = TRUE;
}
