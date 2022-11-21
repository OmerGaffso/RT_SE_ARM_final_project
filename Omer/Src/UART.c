#include "RTG.h"
#include "UART.h"

/**
 * This is the main function for the UART testing.
 * The data received from server will be received initially by UART4, transmit
 * to UART2, and then transmit back to UART4 to check if the data is the same.
 */
uint8_t uart_test(uint8_t iter, uint8_t data_length, uint8_t *data)
{
	uint8_t uart2_buff[data_length] = { 0 };
	uint8_t uart4_buff[data_length] = { 0 };
	uint8_t result = RETURN_SUCCESS;

	for(uint8_t i = 0; i < iter; i++)
	{
		uart_tran_rec(UART_4, UART_2, data_length, data, uart2_buff);
		uart_tran_rec(UART_2, UART_4, data_length, uart2_buff, uart4_buff);

		if(strncmp((char *)uart4_buff, (char *)data, data_length) != 0)
		{
			result = RETURN_FAILURE;
			break;
		}
	}

	return result;
}

/**
 * This function will send the data from UART to UART.
 */
void uart_tran_rec(	UART_HandleTypeDef *uart_transmit,
					UART_HandleTypeDef *uart_receive,
					uint8_t data_length,
					uint8_t *transmit_buff,
					uint8_t *receive_buff )
{
	HAL_UART_Receive_DMA(uart_receive, receive_buff, data_length);
	HAL_UART_Transmit_DMA(uart_transmit, transmit_buff, data_length);
}

// Enters here upon completed UART receive.
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if (huart == UART_2)
//		HAL_UART_Receive_DMA(UART_2, rx_uart_data, DATA_SIZE);
//
//}

