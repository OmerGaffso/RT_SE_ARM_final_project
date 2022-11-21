/**
 * This file will be responsible for all UART definitions and functions.
 * The UART will work with DMA when transmitting or receiving.
 */

#ifndef RTG_ARM_PROJECT_UART
#define RTG_ARM_PROJECT_UART

/// Extern UART Handles
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart4;

/// UART handles
#define UART_2 &huart2					//UART2 Handle
#define UART_4 &huart4					//UART2 Handle

/**
 * This is the main function for the UART testing.
 * The data received from server will be received initially by UART4, transmit
 * to UART2, and then transmit back to UART4 to check if the data is the same.
 * @param iter - number of iteration for the test
 * @param data_length - the length of string to transmit and receive
 * @param data - the string data to transmit and receive
 * @return 0x01 if the tests passed successfully, or 0xff if tests failed.
 */
uint8_t uart_test(uint8_t iter, uint8_t data_length, uint8_t *data);

/**
 *	This function will transmit data between UART to UART.
 * @param UART_transmit - the UART peripheral to transmit the data
 * @param UART_receive - the UART peripheral to receive the data
 * @param data_length - the data length to send
 * @param transmit_buff - the data to transmit
 * @param receive_buff - the data to receive
 */
void uart_transmit_receive(	UART_HandleTypeDef *uart_transmit,
							UART_HandleTypeDef *uart_receive,
							uint8_t data_length,
							uint8_t *transmit_buff,
							uint8_t *receive_buff );

/**
 *  Uses while loop to delay the program until enters HAL_UART_TxCpltCallback
 *  and changes tx_done_flag to true (indicates that the transmit was completed)
 */
void uart_delay_till_transmited();

/**
 *  Uses while loop to delay the program until enters HAL_UART_RxCpltCallback
 *  and changes rx_done_flag to true (indicates that the receive was completed)
 */
void uart_delay_till_received();

#endif
