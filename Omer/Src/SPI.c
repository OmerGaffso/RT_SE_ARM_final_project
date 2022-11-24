#include "RTG.h"
#include "SPI.h"

/// Buffers
uint8_t master_buff[DATA_SIZE]; 	// init the buffer to be full '\0'
uint8_t slave_buff[DATA_SIZE]; 		// init the buffer to be full '\0'

uint8_t master_tx_rx_cnt = INIT_VALUE;		// count callback calls for master
uint8_t slave_tx_rx_cnt = INIT_VALUE;		// count callback calls for slave

/**
 * This is the main function for the SPI testing.
 * The data received from server will be received initially by SPI1, transmit
 * to SPI4, and then transmit back to SPI1 to check if the data is the same.
 * @param iter - number of iteration for the test
 * @param data_length - the length of string to transmit and receive
 * @param data - the string data to transmit and receive
 * @return 0x01 if the tests passed successfully, or 0xff if tests failed.
 */
uint8_t spi_test(uint8_t iter, uint8_t data_length, uint8_t *data)
{
	for(uint8_t i = 0; i < iter ; i++)
	{
		spi_transmit_to_slave(data_length, data);

		spi_transmit_to_master(data_length);

		if (!test_conditions(data_length,data))
		{
			return FAILURE;
		}

		reset_buffers();
		master_tx_rx_cnt = INIT_VALUE;
		slave_tx_rx_cnt = INIT_VALUE;
	}
	return SUCCESS;
}

/**
 * This function reset the buffer to "empty" buffer (filled with zeros).
 */
void reset_buffers()
{
	memset(master_buff, '0', DATA_SIZE);
	memset(slave_buff, '0', DATA_SIZE);
}

/**
 * This function will send the data from SPI master to SPI slave.
 */
void spi_transmit_to_slave(	uint8_t data_length,
							uint8_t *data)
{
	HAL_SPI_TransmitReceive_DMA(SPI_SLAVE,
								slave_buff,
								slave_buff,
								data_length);

	HAL_SPI_TransmitReceive_DMA(SPI_MASTER,
								data,
								master_buff,
								data_length);
}

/**
 * This function will send the data from SPI slave to SPI master.
 */
void spi_transmit_to_master(uint8_t data_length)
{
	HAL_SPI_TransmitReceive_DMA(SPI_SLAVE,
								slave_buff,
								slave_buff,
								data_length);

	HAL_SPI_TransmitReceive_DMA(SPI_MASTER,
								master_buff,
								master_buff,
								data_length);
}

/**
 * Checks that the transmitted/received data is the same as the original
 * data, and that the data was actually sent during spi_test run.
 */
uint8_t test_conditions(uint8_t data_length, uint8_t *data)
{
	if ( strncmp((char *)master_buff, (char *)data, data_length) != 0 )
	{
		return FALSE;
	}

	if (	 master_tx_rx_cnt != CORRECT_CALLBACK_CNT
		||	 slave_tx_rx_cnt != CORRECT_CALLBACK_CNT )
	{
		return FALSE;
	}

	return TRUE;
}

/// enter this callback after successful HAL_SPI_TransmitReceive() function.
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi == SPI_MASTER)
		++master_tx_rx_cnt;
	else if (hspi == SPI_SLAVE)
		++slave_tx_rx_cnt;
}
