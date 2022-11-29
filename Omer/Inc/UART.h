/**
 * @author Omer Penso
 *
 * This file will be responsible for all UART definitions and functions.
 * The UART will work with DMA when transmitting or receiving.
 *
 *		 ---UART---
 * UART4_TX PC10 DMA1 Stream 4
 * UART4_RX PC11 DMA1 Stream 2
 * UART6_TX	PC6  DMA2 Stream 7
 * UART6_RX	PC7  DMA2 Stream 1
 *
 */

#ifndef RTG_ARM_PROJECT_UART
#define RTG_ARM_PROJECT_UART

/// Extern UART Handles
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart6;

/// UART handles
#define UART_MASTER &huart4					//UART4 Handle
#define UART_SLAVE &huart6					//UART6 Handle

/**
 * This is the main function for the UART testing.
 * The data received from server will be received initially by UART4, transmit
 * to UART6, and then transmit back to UART4 to check if the data is the same.
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
 *  and change the flag state to false.
 */
void uart_delay_till_transmited();

/**
 *  Uses while loop to delay the program until enters HAL_UART_RxCpltCallback
 *  and changes rx_done_flag to true (indicates that the receive was completed)
 *  and change the flag state to false.
 */
void uart_delay_till_received();

/**
 * This function uses the memcpy to set the master and slave buffers to "empty"
 * (filled with zeros) in the end of every loop iteration (iteration where the
 * data checks passed).
 */
void uart_reset_buffers(uint8_t *slave_buff, uint8_t *master_buff);

#endif
