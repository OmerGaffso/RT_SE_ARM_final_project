/**
 * @author Omer Penso
 *
 * This file will be responsible for all SPI definitions and functions.
 *
 * 				---SPI---
 * SPI1_SCK - PB3
 * SPI1_MOSI - PB5
 * SPI1_MISO - PB4
 * SPI1_CS - PA4
 * 					TX DMA2 Stream 5
 * 					RX DMA2 Stream 2
 * SPI4_SCK - PE2
 * SPI4_MOSI - PE6
 * SPI4_MISO - PE5
 * SPI4_CS - PE4
 *					TX DMA2 Stream 4
 *					RX DMA2 Stream 0
 *
 */

#ifndef RTG_ARM_PROJECT_SPI
#define RTG_ARM_PROJECT_SPI

/// Extern SPI HANDLES
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi4;

/// SPI handles
#define SPI_MASTER &hspi1			//SPI Master
#define SPI_SLAVE &hspi4			//SPI Slave

#define CS_PER GPIOA				//CS configured to per A
#define CS_PIN GPIO_PIN_4			//CS configured to pin 4

/// Used to check that entered the callback correct number of times.
#define CORRECT_CALLBACK_CNT 2U

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
 * This function uses the memcpy to set the master and slave buffers to "empty"
 * (filled with zeros) in the end of every loop iteration (iteration where the
 * data checks passed).
 */
void spi_reset_buffers();

/**
 * This function will transmit data form SPI master to SPI slave.
 * @param data_length - the length of the string
 * @param data - the data to be transmitted to the slave
 */
void spi_transmit_to_slave(	uint8_t data_length,
							uint8_t *data);

/**
 * This function will transmit data form SPI slave to SPI master.
 * @param data_length - the length of the string
 */
void spi_transmit_to_master(uint8_t data_length);

/**
 * Uses while loop to delay the program until enters HAL_SPI_TransmitReceive
 * for both master and slave (changes their flags to indicate that they end the
 * transmit and receive operations). Changes the master_tx_rx slave_tx_rx flags
 * back to false after the while loop ended.
 */
void spi_delay_till_tx_rx();

#endif
