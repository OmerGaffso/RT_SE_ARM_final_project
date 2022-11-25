#include "RTG.h"
#include "UART.h"
#include "I2C.h"
#include "SPI.h"
#include "ADC.h"
#include "TIMER.h"

void rtg_main()
{
	char choice;
	uint8_t result;
	while(TRUE)
	{

		print_separator();
		printf("PLEASE CHOOSE TEST TO RUN:\r\n");
		printf("(u)art\r\n");
		printf("(s)pi\r\n");
		printf("(i)2c\r\n");
		printf("(a)dc\r\n");
		printf("(t)imer\r\n");
		scanf("%c", &choice);
		choice = tolower(choice);
		new_line();

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
		case 'a':
			result = adc_test(5);
			break;
		case 't':
			result = timer_test(5);
			break;
		default:
			printf("\r\nPlease input a valid option (U/I/S).\r\n");
			continue;
		}
		if (result == SUCCESS)
			printf("Test Succeeded!\r\n");
		else
			printf("Test Failed!\r\n");

	}
}

