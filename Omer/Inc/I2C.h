/**
 * @author Omer Penso
 *
 * This file will be responsible for all I2C definitions and functions.
 *
 *	 			---I2C---
 * I2C1 - PB9 SDA
 * I2C1 - PB8 SCL
 * 					TX DMA1 Stream 6
 * 					RX DMA1 Stream 0
 *
 * I2C2 - PF0 SDA
 * I2C2 - PF1 SCL
 *					TX DMA1 Stream 7
 *					RX DMA1 Stream 3
 */

#ifndef RTG_ARM_PROJECT_I2C
#define RTG_ARM_PROJECT_I2C

/// Extern I2C handles
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

/// I2C handles
#define I2C_MASTER &hi2c2					//I2C Master
#define I2C_SLAVE &hi2c1					//I2C Slave
#define SLAVE_ADDR 14U						//Slave address

/**
 * This is the main function for the I2C testing.
 * The data received from server will be received initially by I2C2, transmit
 * to I2C1, and then transmit back to I2C2 to check if the data is the same.
 * @param iter - number of iteration for the test
 * @param data_length - the length of string to transmit and receive
 * @param data - the string data to transmit and receive
 * @return 0x01 if the tests passed successfully, or 0xff if tests failed.
 */
uint8_t i2c_test(uint8_t iter, uint8_t data_length, uint8_t *data);


/**
 * This function will send the data from I2C master to I2C slave.
 * @param i2c_transmit - the I2C peripheral to transmit the data
 * @param i2c_receive - the I2C peripheral to receive the data
 * @param data_length - the length of the string
 * @param transmit_buff - the buffer from which we'll transmit the data
 * @param receive_buff - the buffer which we'll receive the data into
 */
void i2c_transmit_to_slave(	I2C_HandleTypeDef *i2c_transmit,
							I2C_HandleTypeDef *i2c_receive,
							uint8_t data_length,
							uint8_t *transmit_buff,
							uint8_t *receive_buff );

/**
 * This function will send the data from I2C slave to I2C master.
 * @param i2c_transmit - the I2C peripheral to transmit the data
 * @param i2c_receive - the I2C peripheral to receive the data
 * @param data_length - the length of the string
 * @param transmit_buff - the buffer from which we'll transmit the data
 * @param receive_buff - the buffer which we'll receive the data into
 */
void i2c_transmit_to_master(	I2C_HandleTypeDef *i2c_transmit,
								I2C_HandleTypeDef *i2c_receive,
								uint8_t data_length,
								uint8_t *transmit_buff,
								uint8_t *receive_buff );

/**
 *  Uses while loop to delay the program until enters HAL_I2C_TxCpltCallback
 *  and changes tx_done_flag to true (indicates that the transmit was completed)
 */
void i2c_delay_till_transmited();

/**
 *  Uses while loop to delay the program until enters HAL_I2C_RxCpltCallback
 *  and changes rx_done_flag to true (indicates that the receive was completed)
 */
void i2c_delay_till_received();

#endif
