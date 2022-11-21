#include "RTG.h"
#include "SPI.h"
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
	uint8_t spi1_buff[data_length] = { 0 }; // init the buffer to be full '\0'
	uint8_t spi4_buff[data_length] = { 0 }; // init the buffer to be full '\0'
	uint8_t result = RETURN_SUCCESS;

	for(uint8_t i = 0; i < iter ; i++)
	{
		spi_tran_rec(SPI_1, SPI_4, data_length, data, spi4_buff);
		spi_tran_rec(SPI_4, SPI_1, data_length, spi4_buff, spi1_buff);

		if(strncmp((char *)spi1_buff, (char *)data, data_length) != 0)
		{
			result = RETURN_FAILURE;
			break;
		}
	}
	return result;
}

/**
 * This function will send the data from SPI to SPI.
 */
void spi_tran_rec(	SPI_HandleTypeDef *spi_transmit,
					SPI_HandleTypeDef *spi_receive,
					uint8_t data_length,
					uint8_t *transmit_buff,
					uint8_t *receive_buff )
{
	HAL_SPI_Receive_DMA(spi_receive, receive_buff, data_length);
	HAL_SPI_Transmit_DMA(spi_transmit, transmit_buff, data_length);
}
