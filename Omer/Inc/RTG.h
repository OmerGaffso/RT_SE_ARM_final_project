/**
 * author: Omer Penso
 *
 * TODO - Add project description and edit the changes to pinout
 *
 */
#ifndef RTG_ARM_PROJECT_MAIN
#define RTG_ARM_PROJECT_MAIN
#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// DEBUG UART
extern UART_HandleTypeDef huart3;
#define UART_DEBUG &huart3				//Debug UART

// GENERAL DEFINITIONS:
//Max size of data for UDP received string
#define DATA_SIZE 256U
//length for id field in packet
#define ID_LEN		4U
//length for iterations, bitfield length and peripheral fields.
#define CONTROL_FIELD_LEN	1U
//Initiation value counters/flags
#define INIT_VALUE 0

// UDP configuration handle
extern struct netif gnetif;

// BOOLS:
#define TRUE 1
#define FALSE 0

// PEREPHERIAL TEST CODE:
#define TIMER_TEST	0x01				//Timer test = 1
#define UART_TEST	0x02				//UART test = 2
#define SPI_TEST	0x04				//SPI test = 4
#define I2C_TEST	0x08				//i2C test = 8
#define ADC_TEST	0x10 				//ADC test = 16

// TEST_RETURNS:
#define SUCCESS 0x01					//The test ended successfully
#define FAILURE 0xff					//The test ended in failure

#define SECOND_IN_MILLISECONS 1000U // Timeout

/**
 * The packet received from client, separated to fields
 */
typedef struct packet {
	uint8_t test_id[ID_LEN];
	uint8_t test_per;			// Chosen Peripheral
	uint8_t test_iter;			// Number of iterations for the test
	uint8_t test_bitfield_len;	// Length of the data
	uint8_t test_bitfield_data[DATA_SIZE];	// Data for comm protocols tests.
}packet_t;

// FUNCTIONS:

/**
 * rtg_main is used instead of main function so my code won't be deleted by
 * mistake when editing the .ioc file.
 */
void rtg_main();

/**
 * Read the chosen peripheral byte to choose the correct test.
 * For every test, send the corresponding field from the packet struct for
 * computations.
 * @param test_packet - the struct created with the data received from client.
 * @return	0x01 if the test passed successfully, 0xff if the test failed.
 */
uint8_t send_to_test(packet_t *test_packet);

#endif
