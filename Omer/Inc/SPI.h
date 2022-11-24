/**
 * This file will be responsible for all SPI definitions and functions.
 */

#ifndef RTG_ARM_PROJECT_SPI
#define RTG_ARM_PROJECT_SPI

/// Extern SPI HANDLES
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi4;
extern SPI_HandleTypeDef hspi5;


/// SPI handles
#define SPI_MASTER &hspi1			//SPI Master
#define SPI_SLAVE &hspi4			//SPI Slave

#define CS_PER GPIOA				//CS configured to per A
#define CS_PIN GPIO_PIN_4			//CS configured to pin 4

/// Used to check that entered the callback correct number of times before
/// test condition.
#define CORRECT_CALLBACK_CNT 2

/** TODO - EDIT desc!
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
void reset_buffers();

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
 * This function will check if the data received after the transmit and receive
 * is the same as the original data, and that the data actually moved during
 * the function.
 * @param data - the original data that was received from the packet.
 * @param data_length - the length of the data.
 * @return TRUE (1) if checks passed, FALSE (0) otherwise.
 */
uint8_t test_conditions(uint8_t data_length ,uint8_t *data);

#endif
