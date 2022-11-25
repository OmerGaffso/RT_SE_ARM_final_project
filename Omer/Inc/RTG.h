/**
 * author: Omer Penso
 *
 * TODO - Add project description and edit the changes to pinout
 *
 */
#ifndef INC_RTG_H_
#define INC_RTG_H_
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

//Initiation value for counters and pin connected flag
#define INIT_VALUE 0

// BOOLS:
#define TRUE 1
#define FALSE 0

// TEST_RETURNS:
#define SUCCESS 0x01				//The test ended successfully
#define FAILURE 0xff				//The test ended in failure

// FUNCTIONS:

/**
 * rtg_main is used instead of main function so my code won't be deleted by
 * mistake when editing the .ioc file.
 */
void rtg_main();

/**
 * Helper function that prints a separator.
 */
void print_separator();

/**
 * Helper function that prints newline
 */
void new_line();
#endif /* INC_RTG_H_ */
