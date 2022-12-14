#include "RTG.h"
#include "I2C.h"

// Flags to be used in call backs
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
		// transmit from I2C2 (master) to I2C1 (slave)
		i2c_transmit_to_slave(I2C_MASTER, I2C_SLAVE, data_length, data, i2c4_buff);
		i2c_delay_till_received();
		// transmit from I2C1 (slave) to I2C2 (master)
		i2c_transmit_to_master(I2C_SLAVE, I2C_MASTER, data_length, i2c4_buff, i2c2_buff);
		i2c_delay_till_received();

		if(strncmp((char *)i2c2_buff, (char *)data, data_length) != 0)
		{
			result = FAILURE;
			return result;
		}
		i2c_reset_buffers(i2c4_buff, i2c2_buff);
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
	// ready the master to receive
	HAL_I2C_Master_Receive_DMA(i2c_receive, SLAVE_ADDR, receive_buff, data_length);
	// master waiting to receive, master transmit
	HAL_I2C_Slave_Transmit_DMA(i2c_transmit, transmit_buff, data_length);
	i2c_delay_till_transmited();
}

/// Delay until enters HAL_I2C_TxCpltCallback changes flag to true
void i2c_delay_till_transmited()
{
	// get the current system tick
	uint32_t tickstart = HAL_GetTick();
	while(i2c_tx_done_flag != TRUE)
	{	// timeout for the case that there is an hardware fault
		if (HAL_GetTick() - tickstart > SECOND_IN_MILLISECONS)
			break;
	}
	i2c_tx_done_flag = FALSE;
}

/// Delay until enters HAL_I2C_Rx_CpltCallback changes flag to true
void i2c_delay_till_received()
{
	// get the current system tick
	uint32_t tickstart = HAL_GetTick();
	while(i2c_rx_done_flag != TRUE)
	{	// timeout for the case that there is an hardware fault
		if (HAL_GetTick() - tickstart > SECOND_IN_MILLISECONS)
			break;
	}
	i2c_rx_done_flag = FALSE;
}

/**
 * This function reset the buffer to "empty" buffer (filled with zeros).
 */
void i2c_reset_buffers(uint8_t *slave_buff, uint8_t *master_buff)
{
	memset(master_buff, '0', DATA_SIZE);
	memset(slave_buff, '0', DATA_SIZE);
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
