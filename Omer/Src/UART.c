#include "RTG.h"
#include "UART.h"

/// Flags to be used in call backs
uint8_t uart_tx_done_flag = FALSE;		// Flag to notify complete transmit
uint8_t uart_rx_done_flag = FALSE;		// Flag to notify complete received

/**
 * This is the main function for the UART testing.
 * The data received from server will be received initially by UART4, transmit
 * to UART6, and then transmit back to UART4 to check if the data is the same.
 */
uint8_t uart_test(uint8_t iter, uint8_t data_length, uint8_t *data)
{
	uint8_t uart_master_buff[DATA_SIZE] = { 0 };		// UART4 Buffer
	uint8_t uart_slave_buff[DATA_SIZE] = { 0 };			// UART6 BUFFER
	uint8_t result = SUCCESS;

	for(uint8_t i = 0; i < iter; i++)
	{
		uart_transmit_receive(	UART_MASTER,
								UART_SLAVE,
								data_length,
								data,
								uart_slave_buff);
		uart_delay_till_received();

		uart_transmit_receive(	UART_SLAVE,
								UART_MASTER,
								data_length,
								uart_slave_buff,
								uart_master_buff);
		uart_delay_till_received();

		if(strncmp((char *)uart_master_buff, (char *)data, data_length) != 0)
		{
			result = FAILURE;
			return result;
		}
		uart_reset_buffers(uart_slave_buff, uart_master_buff);
	}
	return result;
}

/**
 * This function will send the data from UART to UART.
 */
void uart_transmit_receive(	UART_HandleTypeDef *uart_transmit,
							UART_HandleTypeDef *uart_receive,
							uint8_t data_length,
							uint8_t *transmit_buff,
							uint8_t *receive_buff )
{
	HAL_UART_Receive_DMA(uart_receive, receive_buff, data_length);
	HAL_UART_Transmit_DMA(uart_transmit, transmit_buff, data_length);
	uart_delay_till_transmited();
}

/// Delay until enters HAL_UART_TxCpltCallback changes flag to true
void uart_delay_till_transmited()
{
	uint32_t tickstart = HAL_GetTick();
	while(uart_tx_done_flag != TRUE)
	{
		if(HAL_GetTick() - tickstart > SECOND_IN_MILLISECONS)
			break;
	}
	uart_tx_done_flag = FALSE;
}

/// Delay until enters HAL_UART_Rx_CpltCallback changes flag to true
void uart_delay_till_received()
{
	uint32_t tickstart = HAL_GetTick();
	while(uart_rx_done_flag != TRUE)
	{
		if(HAL_GetTick() - tickstart > SECOND_IN_MILLISECONS)
			break;
	}
	uart_rx_done_flag = FALSE;
}

/**
 * This function reset the buffer to "empty" buffer (filled with zeros).
 */
void uart_reset_buffers(uint8_t *slave_buff, uint8_t *master_buff)
{
	memset(master_buff, '0', DATA_SIZE);
	memset(slave_buff, '0', DATA_SIZE);
}

/// Enters here upon completed UART receive.
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == UART_MASTER || huart == UART_SLAVE)
		uart_rx_done_flag = TRUE;
}

/// Enters here upon complete UART transmit.
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == UART_MASTER || huart == UART_SLAVE)
		uart_tx_done_flag = TRUE;
}

