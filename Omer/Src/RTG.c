#include "RTG.h"
#include "UART.h"
#include "I2C.h"
#include "SPI.h"

void rtg_main()
{
	char choice;
	uint8_t result;
	while(TRUE)
	{
		print_separator();
		printf("Please enter a communication protocol name:(U/I/S)\r\n");
		scanf("%c", &choice);
		choice = tolower(choice);

		switch(choice)
		{
		case 'u':
			result = uart_test(5,3,(uint8_t*)"abc");
			break;
		case 'i':
			result = i2c_test(5,3,(uint8_t*)"abc");
			break;
		case 's':
			result = spi_test(5,3,(uint8_t*)"abc");
			break;
		default:
			printf("\r\nPlease input a valid option (U/I/S).\r\n");
			continue;
		}
		if (result == RETURN_SUCCESS)
			printf("Test Succeded!\r\n");
		else
			printf("Test Failed!\r\n");

		print_separator();

	}
}

