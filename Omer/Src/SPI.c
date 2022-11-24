#include "RTG.h"
#include "SPI.h"

/// Flags to be used in call backs
uint8_t spi_tx_done_flag = FALSE;		// Flag to notify complete transmit
uint8_t spi_rx_done_flag = FALSE;		// Flag to notify complete received
uint8_t spi_tx_rx_done_flag = FALSE;	// Flag to notify complete tx/rx

/// Buffers
uint8_t master_buff[DATA_SIZE]; 	// init the buffer to be full '\0'
uint8_t slave_buff[DATA_SIZE]; 	// init the buffer to be full '\0'
uint8_t dummy_buff[DATA_SIZE] = { 1 };  	// dummy buffer that will stay '\0'

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
	uint8_t result = RETURN_SUCCESS;
//	data_len = data_length;
//	memcpy(slave_buff, data, data_length);

//	HAL_SPI_Receive_DMA(SPI_SLAVE, slave_buff, data_length);

	for(uint8_t i = 0; i < iter ; i++)
	{
/** WORKS!!!!
		HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, data, slave_buff, data_length);
		HAL_SPI_TransmitReceive_DMA(SPI_MASTER, master_buff, master_buff, data_length);

		HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, slave_buff, slave_buff, data_length);
		HAL_SPI_TransmitReceive_DMA(SPI_MASTER, master_buff, master_buff, data_length);
*/
		HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, slave_buff, slave_buff, data_length);
		HAL_SPI_TransmitReceive_DMA(SPI_MASTER, data, master_buff, data_length);

		HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, slave_buff, slave_buff, data_length);
		HAL_SPI_TransmitReceive_DMA(SPI_MASTER, master_buff, master_buff, data_length);

		if(strncmp((char *)master_buff, (char *)data, data_length) != 0)
		{
			result = RETURN_FAILURE;
			return result;
		}
		reset_buffers();
	}
	return result;
}

void reset_buffers()
{
	memset(master_buff, '0', DATA_SIZE);
	memset(slave_buff, '0', DATA_SIZE);
}

/**
 * This function will send the data from SPI master to SPI slave.
 */
void spi_transmit_to_slave(	SPI_HandleTypeDef *spi_transmit,
							SPI_HandleTypeDef *spi_receive,
							uint8_t data_length,
							uint8_t *data)
{

	// transmit the original data to the slave.
	HAL_SPI_Receive_DMA(SPI_SLAVE, slave_buff, data_length);
	HAL_SPI_Transmit_DMA(SPI_MASTER, master_buff, data_length);
}

/**
 * This function will send the data from SPI slave to SPI master.
 */
void spi_transmit_to_master(SPI_HandleTypeDef *spi_transmit,
							SPI_HandleTypeDef *spi_receive,
							uint8_t data_length)
{
//	memcpy(tx_slave_buff, rx_slave_buff, data_length);

//	HAL_SPI_TransmitReceive_DMA(SPI_MASTER, dummy_buff, rx_slave_buff, DATA_SIZE);
//	HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, tx_slave_buff, master_buff, data_length);
//	spi_delay_till_tx_rx();

//	HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, slave_buff, slave_buff, data_length);
//	HAL_SPI_TransmitReceive_DMA(SPI_MASTER, master_buff, master_buff, data_length);

	HAL_SPI_Transmit_DMA(SPI_SLAVE, slave_buff, data_length);
//	HAL_SPI_Receive_DMA(SPI_MASTER, master_buff, data_length);
//
//	HAL_SPI_Receive_DMA(SPI_SLAVE, dummy_buff, data_length);
//	spi_init_receive(data_length);

//	HAL_SPI_Transmit_DMA(SPI_MASTER, dummy_buff, data_length);
//	HAL_SPI_Transmit_DMA(SPI_MASTER, dummy_buff, data_length);
//	spi_delay_till_transmited(); // delay until completed the transmit
//	spi_delay_till_received(); // delay until receive complete
}

/// Delay until enters HAL_SPI_TxCpltCallback changes flag to true
void spi_delay_till_transmited()
{
	while(spi_tx_done_flag != TRUE);	// TODO: add timeout to loop (for hardware problem cases)
	spi_tx_done_flag = FALSE;
}

/// Delay until enters HAL_SPI_Rx_CpltCallback changes flag to true
void spi_delay_till_received()
{
	while(spi_rx_done_flag != TRUE);	// TODO: add timeout to loop (for hardware problem cases)
	spi_rx_done_flag = FALSE;
}

/// Delay until enters HAL_SPI_Rx_CpltCallback for master and slave to change
/// the flag
void spi_delay_till_tx_rx()
{
	while(spi_tx_rx_done_flag != TRUE);	// TODO: add timeout to loop (for hardware problem cases)
	spi_tx_rx_done_flag = FALSE;
}

/// Enters here upon complete SPI transmit
//void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
//{
//	if (hspi == SPI_MASTER)
//		HAL_SPI_Receive_DMA(SPI_SLAVE, slave_buff, data_len);
//	if (hspi == SPI_SLAVE)
//		HAL_SPI_Receive_DMA(SPI_MASTER, master_buff, data_len);
//}

/// Enters here upon complete SPI receive
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
//	if (hspi == SPI_MASTER)
//		HAL_SPI_Receive_DMA(SPI_MASTER, master_buff, data_len);
//	if (hspi == SPI_SLAVE)
//		HAL_SPI_Receive_DMA(SPI_SLAVE, slave_buff, data_len);
}

/// Enters here upon complete SPI receive
//void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
//{
//	if (hspi == SPI_MASTER)
//
//		//		HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, slave_buff, slave_buff, data_len);
//	if (hspi == SPI_SLAVE)
////		HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, master_buff, master_buff, data_len);
//}
