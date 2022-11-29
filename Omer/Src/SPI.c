#include "RTG.h"
#include "SPI.h"

/// Buffers
uint8_t master_buff[DATA_SIZE];
uint8_t slave_buff[DATA_SIZE];

uint8_t master_tx_rx = FALSE;
uint8_t slave_tx_rx = FALSE;

/**
 * This is the main function for the SPI testing.
 */
uint8_t spi_test(uint8_t iter, uint8_t data_length, uint8_t *data)
{
	for(uint8_t i = 0; i < iter ; i++)
	{
		// transmit from master to slave
		spi_transmit_to_slave(data_length, data);
		// wait until callbacks are called.
		spi_delay_till_tx_rx();

		// transmit from slave to master
		spi_transmit_to_master(data_length);
		// wait until callbacks are called.
		spi_delay_till_tx_rx();

		// test received data equals to original data and callback counters
		// reached expected count
		if ( strncmp((char *)master_buff, (char *)data, data_length) != 0 )
		{
			return FAILURE;
		}

		spi_reset_buffers();
	}
	return SUCCESS;
}

/**
 * This function reset the buffer to "empty" buffer (filled with zeros).
 */
void spi_reset_buffers()
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
	// ready the slave for transmit and receive
	HAL_SPI_TransmitReceive_DMA(SPI_SLAVE,
								slave_buff,
								slave_buff,
								data_length);

	// master initiate the communication. send the original data to slave.
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
	// ready the slave for transmit and receive
	HAL_SPI_TransmitReceive_DMA(SPI_SLAVE,
								slave_buff,
								slave_buff,
								data_length);

	// master initiate the communication. receive the slave buffer containing
	// the original data.
	HAL_SPI_TransmitReceive_DMA(SPI_MASTER,
								master_buff,
								master_buff,
								data_length);
}

/// Delay until enters HAL_SPI_TxRxCpltCallback for both master and slave
void spi_delay_till_tx_rx()
{
	// get the current system tick
	uint32_t tickstart = HAL_GetTick();
	while(master_tx_rx != TRUE && slave_tx_rx != TRUE)
	{
		// uses the tick as timeout period, for situations of hardware faults.
		if(HAL_GetTick() - tickstart > SECOND_IN_MILLISECONS)
			break;
	}
	master_tx_rx = FALSE;
	slave_tx_rx = FALSE;
}

/// enter this callback after successful HAL_SPI_TransmitReceive() function.
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi == SPI_MASTER)
		master_tx_rx = TRUE;

	else if (hspi == SPI_SLAVE)
		slave_tx_rx = TRUE;
}
