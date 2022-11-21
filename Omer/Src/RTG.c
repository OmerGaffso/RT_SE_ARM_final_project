#include "RTG.h"

uint8_t uart_flag = FALSE; 					// UART operation flag
uint8_t i2c_flag = FALSE;					// I2C operation flag
uint8_t spi_flag = FALSE;					// SPI operation flag
uint8_t op_switch_flag = FALSE;

// array to store the data received via the protocols
uint8_t rx_uart_data[DATA_SIZE];
uint8_t rx_i2c_data[DATA_SIZE];
uint8_t rx_spi_data[DATA_SIZE];

// messages to send to each protocol
uint8_t tx_uart_data[] = "HELLO FROM UART\r\n";	// message for UART transmition
uint8_t tx_i2c_data[] = "HELLO FROM I2C\r\n";	// message for I2C transmition
uint8_t tx_spi_data[] = "HELLO FROM SPI\r\n";	// message for SPI transmition

// counters
unsigned int uart_cnt = INIT_VALUE;
unsigned int i2c_cnt = INIT_VALUE;
unsigned int spi_cnt = INIT_VALUE;

void rtg_main()
{
	char choice;
	init_receive();
	while(TRUE)
	{
		print_separator();
		printf("Please enter a communication protocol name:(U/I/S)\r\n");
		scanf("%c", &choice);
		choice = tolower(choice);

		switch(choice)
		{
		case 'u':
			uart_flag = TRUE;
			break;
		case 'i':
			i2c_flag = TRUE;
			break;
		case 's':
			spi_flag = TRUE;
			break;
		default:
			printf("\r\nPlease input a valid option (U/I/S).\r\n");
			continue;
		}

		print_separator();

		/// The flags were what cause the errors. moved the receives in the
		/// rx callbacks.

		if(uart_flag)
		{
			HAL_UART_Transmit_DMA(UART_TRANSMIT, tx_uart_data, DATA_SIZE);
			print_msg();
			uart_flag = FALSE;
		}

		else if(i2c_flag)
		{
			HAL_I2C_Master_Transmit_DMA(I2C_TRANSMIT,SLAVE_ADDR,tx_i2c_data,DATA_SIZE);
			print_msg();
			i2c_flag = FALSE;
		}
		else if(spi_flag)
		{
			HAL_SPI_Transmit_DMA(SPI_TRANSMIT, tx_spi_data, DATA_SIZE);
			print_msg();
			spi_flag = FALSE;
		}

		HAL_Delay(300);
	}
}

// Enters here upon completed i2c receive.
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if (hi2c == I2C_RECEIVE)
		HAL_I2C_Slave_Receive_DMA(I2C_RECEIVE, rx_i2c_data, DATA_SIZE);
}

// Enters here upon completed spi receive.
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi == SPI_RECEIVE)
		HAL_SPI_Receive_DMA(SPI_RECEIVE, rx_spi_data, DATA_SIZE);

}

void switch_op()
{
	if(uart_flag)
	{
		uart_flag = FALSE;
		i2c_flag = TRUE;
	}
	else if (i2c_flag)
	{
		i2c_flag = FALSE;
		spi_flag = TRUE;
	}
	else if (spi_flag)
	{
		spi_flag = FALSE;
		uart_flag = TRUE;
	}
	else
		uart_flag = TRUE;
}

void init_receive()
{
	HAL_UART_Receive_DMA(UART_RECEIVE, rx_uart_data, DATA_SIZE);
	HAL_I2C_Slave_Receive_DMA(I2C_RECEIVE, rx_i2c_data, DATA_SIZE);
	HAL_SPI_Receive_DMA(SPI_RECEIVE, rx_spi_data, DATA_SIZE);
}


