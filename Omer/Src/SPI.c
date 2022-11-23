#include "RTG.h"
#include "SPI.h"

/// Flags to be used in call backs
uint8_t spi_master_tx_done_flag = FALSE;// Flag to notify master complete transmit
uint8_t spi_master_rx_done_flag = FALSE;// Flag to notify master complete received
uint8_t spi_slave_tx_done_flag = FALSE;	// Flag to notify slave complete transmit
uint8_t spi_slave_rx_done_flag = FALSE;	// Flag to notify slave complete received
//uint8_t spi_tx_rx_done_flag = FALSE;		// Flag to notify complete tx/rx

/// Buffers
uint8_t dummy_buff[DATA_SIZE] = { 0 };  	// dummy buffer that will stay '\0'
uint8_t master_buff[DATA_SIZE] = { 0 }; 	// init the buffer to be full '\0'
/// changed all occurrences of rx_slave_buff to slave_buff
uint8_t slave_buff[DATA_SIZE] = { 0 }; 	// init the buffer to be full '\0'
//uint8_t rx_slave_buff[DATA_SIZE] = { 0 }; 	// init the buffer to be full '\0'
//uint8_t tx_slave_buff[DATA_SIZE] = { 0 };	// init the buffer to be full '\0'
uint8_t origin_data[DATA_SIZE] = { 0 }; 	// buffer for the original data.

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

	spi_init_receive(master_buff, slave_buff, data_length);
	for(uint8_t i = 0; i < iter ; i++)
	{

		spi_transmit_to_slave(SPI_MASTER, SPI_SLAVE, data_length, origin_data, slave_buff);
//		spi_delay_till_received(); // delay until receive complete

//		spi_init_receive(master_buff, slave_buff, data_length);

		spi_transmit_to_master(SPI_SLAVE, SPI_MASTER, data_length, slave_buff, master_buff);

		if(strncmp((char *)master_buff, (char *)data, data_length) != 0)
		{
			result = RETURN_FAILURE;
			return result;
		}

//		reset_buff();
	}
	return result;
}

void spi_init_receive(	uint8_t *receive_buff_1,
						uint8_t *receive_buff_2,
						uint8_t data_length)
// TODO: accept buff parameters OR delete this function
{
	HAL_SPI_Receive_DMA(SPI_MASTER, receive_buff_1, data_length);
	HAL_SPI_Receive_DMA(SPI_SLAVE, receive_buff_2, data_length);
}

/**
 * This function will send the data from SPI master to SPI slave.
 */
void spi_transmit_to_slave(	SPI_HandleTypeDef *spi_transmit,
							SPI_HandleTypeDef *spi_receive,
							uint8_t data_length,
							uint8_t *transmit_buff,
							uint8_t *receive_buff)
{
	// prepare the slave buffer to receive data.
	///								slave_buff
	HAL_SPI_Receive_DMA(SPI_SLAVE, slave_buff, data_length);
//	spi_init_receive(master_buff, slave_buff, data_length);
	// transmit the original data to the slave.
	///							origin_data or dummy_buff
	HAL_SPI_Transmit_DMA(SPI_MASTER, transmit_buff, data_length);

//	spi_delay_till_received(); // delay until completed the receive
	spi_delay_till_transmited(); // delay until completed the transmit
	spi_delay_till_received(); // delay until receive complete
}

/**
 * This function will send the data from SPI slave to SPI master.
 */
void spi_transmit_to_master(SPI_HandleTypeDef *spi_transmit,
							SPI_HandleTypeDef *spi_receive,
							uint8_t data_length,
							uint8_t *transmit_buff,
							uint8_t *receive_buff)
{
	HAL_SPI_Transmit_DMA(SPI_SLAVE, slave_buff, data_length);
	HAL_SPI_Receive_DMA(SPI_MASTER, master_buff, data_length);
	spi_delay_till_received();

//	spi_init_receive(dummy_buff, slave_buff, data_length);
	spi_transmit_to_slave(SPI_MASTER, SPI_SLAVE, data_length, dummy_buff, slave_buff);
	///HAL_SPI_Transmit_DMA(SPI_MASTER, dummy_buff, data_length);

}

void reset_buff()
{
	memset(master_buff, '\0', DATA_SIZE);
	memset(slave_buff, '\0', DATA_SIZE);
}
/// Delay until HAL_SPI_TxCpltCallback changes one of the flags to true
void spi_delay_till_transmited()
{
	while(spi_master_tx_done_flag != TRUE && spi_slave_tx_done_flag != TRUE);
	// TODO: add timeout to loop (for hardware problem cases)
	if (spi_master_tx_done_flag)
		spi_master_tx_done_flag = FALSE;
	if (spi_slave_tx_done_flag)
		spi_slave_tx_done_flag = FALSE;
}

/// Delay until HAL_SPI_Rx_CpltCallback changes one of the flags to true
void spi_delay_till_received()
{
	while(spi_slave_rx_done_flag != TRUE && spi_master_rx_done_flag != TRUE);
	// TODO: add timeout to loop (for hardware problem cases)
	if (spi_slave_rx_done_flag)
		spi_slave_rx_done_flag = FALSE;
	if (spi_master_rx_done_flag)
		spi_master_rx_done_flag = FALSE;
}

///// Delay until the tx and rx of both slave and
//void spi_delay_till_tx_and_rx()
//{
//	// TODO: add timeout to loop (for hardware problem cases)
//	while((spi_slave_rx_done_flag != TRUE || spi_master_rx_done_flag != TRUE)
//		&&(spi_slave_tx_done_flag != TRUE || spi_master_tx_done_flag != TRUE));
//
//	spi_master_tx_done_flag = FALSE;
//	spi_slave_tx_done_flag = FALSE;
//	spi_master_rx_done_flag = FALSE;
//	spi_slave_rx_done_flag = FALSE;
//}

/// Enters here upon complete SPI transmit
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi == SPI_MASTER)
		spi_master_tx_done_flag = TRUE;
	else if (hspi == SPI_SLAVE)
		spi_slave_tx_done_flag = TRUE;
}

/// Enters here upon complete SPI receive
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi == SPI_MASTER)
		spi_master_rx_done_flag = TRUE;
	else if (hspi == SPI_SLAVE)
		spi_slave_rx_done_flag = TRUE;
}

///// Enters here upon complete SPI receive
//void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
//{
//	static uint8_t master_done = FALSE;
//	static uint8_t slave_done = FALSE;
//
//	if (hspi == SPI_MASTER)
//		master_done = TRUE;
//	else if (hspi == SPI_SLAVE)
//		slave_done = TRUE;
//
//	if (master_done && slave_done)
//	{
//		spi_tx_rx_done_flag = TRUE;
//		master_done = FALSE;
//		slave_done = FALSE;
//	}
//}
