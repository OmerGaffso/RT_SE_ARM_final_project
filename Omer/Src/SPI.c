#include "RTG.h"
#include "SPI.h"

/// Flags to be used in call backs
uint8_t spi_tx_done_flag = FALSE;		// Flag to notify complete transmit
uint8_t spi_rx_done_flag = FALSE;		// Flag to notify complete received
uint8_t spi_tx_rx_done_flag = FALSE;	// Flag to notify complete tx/rx

/// Buffers
uint8_t master_buff[DATA_SIZE] = { 0 }; 	// init the buffer to be full '\0'
uint8_t rx_slave_buff[DATA_SIZE] = { 0 }; 	// init the buffer to be full '\0'
uint8_t tx_slave_buff[DATA_SIZE] = { 0 };	// init the buffer to be full '\0'
uint8_t origin_data[DATA_SIZE] = { 0 }; 	// buffer for the original data.
uint8_t dummy_buff[DATA_SIZE] = { 0 };  	// dummy buffer that will stay '\0'
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
	memcpy(origin_data, data, data_length);

	for(uint8_t i = 0; i < iter ; i++)
	{
		spi_init_receive(data_length);

		spi_transmit_to_slave(SPI_MASTER, SPI_SLAVE, data_length);
		spi_delay_till_received(); // delay until receive complete

//		spi_init_receive(data_length);

		spi_transmit_to_master(SPI_SLAVE, SPI_MASTER, data_length);

		if(strncmp((char *)master_buff, (char *)data, data_length) != 0)
		{
			result = RETURN_FAILURE;
			return result;
		}
	}
	return result;
}

void spi_init_receive(int data_length) // TODO: accept buff parameters
{
	HAL_SPI_Receive_DMA(SPI_MASTER, master_buff, data_length);
	HAL_SPI_Receive_DMA(SPI_SLAVE, rx_slave_buff, data_length);
}

/**
 * This function will send the data from SPI master to SPI slave.
 */
void spi_transmit_to_slave(	SPI_HandleTypeDef *spi_transmit,
							SPI_HandleTypeDef *spi_receive,
							uint8_t data_length)
{

//	HAL_SPI_Receive_DMA(spi_receive, receive_buff, data_length);
	// transmit the original data to the slave.
	HAL_SPI_Transmit_DMA(SPI_MASTER, origin_data, data_length);
//	HAL_SPI_TransmitReceive_DMA(SPI_MASTER, origin_data, rx_slave_buff, data_length);
//	HAL_SPI_TransmitReceive_IT(SPI_SLAVE, tx_slave_buff, master_buff, data_length);
	spi_delay_till_transmited(); // delay until completed the transmit

//	void spi_delay_till_tx_rx();
}

/**
 * This function will send the data from SPI slave to SPI master.
 */
void spi_transmit_to_master(SPI_HandleTypeDef *spi_transmit,
							SPI_HandleTypeDef *spi_receive,
							uint8_t data_length)
{
	memcpy(tx_slave_buff, rx_slave_buff, data_length);

//	HAL_SPI_TransmitReceive_DMA(SPI_MASTER, dummy_buff, rx_slave_buff, DATA_SIZE);
//	HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, tx_slave_buff, master_buff, data_length);
//	spi_delay_till_tx_rx();

	HAL_SPI_Transmit_DMA(SPI_SLAVE, tx_slave_buff, data_length);
	HAL_SPI_Receive_DMA(SPI_MASTER, master_buff, data_length);
//	HAL_SPI_Receive_DMA(SPI_SLAVE, dummy_buff, data_length);
//	spi_init_receive(data_length);

	HAL_SPI_Transmit_DMA(SPI_MASTER, dummy_buff, data_length);
//	HAL_SPI_Transmit_DMA(SPI_MASTER, dummy_buff, data_length);
//	spi_delay_till_transmited(); // delay until completed the transmit
	spi_delay_till_received(); // delay until receive complete
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
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi == SPI_MASTER || hspi == SPI_SLAVE)
		spi_tx_done_flag = TRUE;
}

/// Enters here upon complete SPI receive
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi == SPI_MASTER || hspi == SPI_SLAVE)
			spi_rx_done_flag = TRUE;
}

/// Enters here upon complete SPI receive
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	static uint8_t master_done = FALSE;
	static uint8_t slave_done = FALSE;

	if (hspi == SPI_MASTER)
		master_done = TRUE;
	else if (hspi == SPI_SLAVE)
		slave_done = TRUE;

	if (master_done && slave_done)
	{
		spi_tx_rx_done_flag = TRUE;
		master_done = FALSE;
		slave_done = FALSE;
	}
}
