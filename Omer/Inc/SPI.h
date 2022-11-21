/**
 * This file will be responsible for all SPI definitions and functions.
 */

#ifndef RTG_ARM_PROJECT_SPI
#define RTG_ARM_PROJECT_SPI

/// Extern SPI HANDLES
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi4;

/// SPI handles
#define SPI_1 &hspi1					//SPI Master
#define SPI_4 &hspi4					//SPI Slave

/**
 * This is the main function for the SPI testing.
 * The data received from server will be received initially by SPI1, transmit
 * to SPI4, and then transmit back to SPI1 to check if the data is the same.
 * @param iter - number of iteration for the test
 * @param data_length - the length of string to transmit and receive
 * @param data - the string data to transmit and receive
 * @return 0x01 if the tests passed successfully, or 0xff if tests failed.
 */
uint8_t spi_test(uint8_t iter, uint8_t data_length, uint8_t *data);

/**
 * This function will transmit data between SPI to SPI.
 * @param spi_transmit - the SPI peripheral to transmit the data
 * @param spi_receive - the SPI peripheral to receive the data
 * @param data_length - the length of the string
 * @param transmit_buff - the buffer from which we'll transmit the data
 * @param receive_buff - the buffer which we'll receive the data into
 */
void spi_transmit_receive(	SPI_HandleTypeDef *spi_transmit,
							SPI_HandleTypeDef *spi_receive,
							uint8_t data_length,
							uint8_t *transmit_buff,
							uint8_t *receive_buff );

/**
 *  Uses while loop to delay the program until enters HAL_SPI_TxCpltCallback
 *  and changes tx_done_flag to true (indicates that the transmit was completed)
 */
void spi_delay_till_transmited();

/**
 *  Uses while loop to delay the program until enters HAL_SPI_RxCpltCallback
 *  and changes rx_done_flag to true (indicates that the receive was completed)
 */
void spi_delay_till_received();

#endif
