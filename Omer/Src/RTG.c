#include "RTG.h"
#include "lwip.h"
#include "UDP.h"
#include "UART.h"
#include "I2C.h"
#include "SPI.h"
#include "ADC.h"
#include "TIMER.h"

void rtg_main()
{

	udpServer_init();				//Init UDP server
	while(TRUE)
	{
		//Handles the actual reception of bytes from the network interface
		ethernetif_input(&gnetif);
		sys_check_timeouts();		//checks timeout expiration
	}
}


uint8_t send_to_test(packet_t *test_packet)
{
	uint8_t test_result;
	switch (test_packet->test_per)
	{
		case(TIMER_TEST):
			test_result = timer_test(test_packet->test_iter);
			break;

		case(UART_TEST):
			test_result = uart_test(test_packet->test_iter,
									test_packet->test_bitfield_len,
									(char*)test_packet->test_bitfield_data);
			break;

		case(SPI_TEST):
			test_result = spi_test( test_packet->test_iter,
									test_packet->test_bitfield_len,
									(char*)test_packet->test_bitfield_data);
			break;

		case(I2C_TEST):
			test_result = uart_test(test_packet->test_iter,
									test_packet->test_bitfield_len,
									(char*)test_packet->test_bitfield_data);
			break;
		case(ADC_TEST):
			test_result = adc_test(test_packet->test_iter);
			break;

		// in case of invalid test, return failure.
		default:
			test_result = FAILURE;
			break;
	}
	return test_result;
}

