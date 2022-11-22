/**
 * author: Omer Penso
 *
 * This project is communication training project (I invented it to test my
 * knowledge).
 * This project uses timer, which counts 5 seconds. Each cycle (5 seconds)
 * the interrupt will switch the communication protocol to send a basic message
 * and print it to the terminal.
 * Each protocol will have a LED color associated with it which will turn on
 * when the protocol is used:
 * UART - Green LED
 * I2C - Blue LED
 * SPI - Red LED
 *
 * ---UART---
 * UART4_TX PC10
 * UART4_RX PC11
 * UART6_TX	PC6
 * UART6_RX	PC7
 *
 * ---I2C---
 * I2C1 - PB9 SDA , PB8 SCL
 * I2C2 - PB11 SDA , PB10 SCL
 *
 * ---SPI---
 * SPI1_SCK - PB3
 * SPI1_MOSI - PB5
 * SPI1_MISO - PB4
 * SPI1_CS - PA4
 * SPI4_SCK - PE12
 * SPI4_MOSI - PE14
 * SPI4_MISO - PE13
 * SPI4_CS - PE11
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

// TIMER
#define TIMER &htim3

// LED PERIPHERAL & PINS
#define GPIO_LED_PER GPIOB				//LED PERIPHERAL
#define GPIO_LED_1 LD1_Pin				//Sets the first led's pin number
#define GPIO_LED_2 LD2_Pin				//Sets the second led's pin number
#define GPIO_LED_3 LD3_Pin				//Sets the third led's pin number

#define GPIO_PIN_UP	1					//To set the led up
#define GPIO_PIN_DOWN 0					//To set the led down

// GENERAL DEFINITIONS:
//Max size of data for UDP received string
#define DATA_SIZE 255
#define TIMEOUT_TIME 100				//Timeout for UART TRANSMIT
#define DELAY_TIME 500					//Delay time for end of loop
#define INIT_VALUE 0					//Initiation value for counters and pin connected flag
#define OP_UART 0						//UART operation code
#define OP_I2C 1						//I2C operation code
#define OP_SPI 2						//SPI operation code

// BOOLS:
#define TRUE 1
#define FALSE 0

// TEST_RETURNS:
#define RETURN_SUCCESS 0x01				//The test ended successfully
#define RETURN_FAILURE 0xff				//The test ended in failure

// FUNCTIONS:

// rtg_main is used instead of main function so my code won't be delted by mistake
// when making changes on the .ioc file.
void rtg_main();

/// turns off all the LEDs.
void turn_off_leds();

/// turns on all the LEDs.
void turn_on_leds();

/// toggle the LED states
void toggle_leds();

/// helper function. receives 1 or 0 for every led and switching it on or off
/// based on the values of the parameters.
void leds(int green, int blue, int red);

/**
 * Helper function that prints a separator.
 */
void print_separator();

/**
 * Helper function that prints newline
 */
void new_line();
#endif /* INC_RTG_H_ */
