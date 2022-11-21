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
 * UART2_TX	PD5
 * UART2_RX	PD6
 * UART4_TX PC10
 * UART4_RX PC11
 *
 * ---I2C---
 * I2C2 - PB11 SDA , PB10 SCL
 * I2C4 - PD13 SDA , PD12 SCL
 *
 * ---SPI---
 * SPI1_SCK - PB3
 * SPI1_MOSI - PB5
 * SPI1_MISO - PB4
 * SPI1_CS - PA4
 * SPI4_SCK - PE2
 * SPI4_MOSI - PE6
 * SPI4_MISO - PE5
 * SPI4_CS - PE4
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

// UART HANDLES:
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart4;

// I2C HANDLES:
extern I2C_HandleTypeDef hi2c2;
extern I2C_HandleTypeDef hi2c4;

// SPI HANDLES:
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi4;

// DEFINITIONS:
// UART
#define UART_DEBUG &huart3				//Debug UART
#define UART_2 &huart2					//UART2 Handle
#define UART_4 &huart4					//UART2 Handle

// I2C
#define I2C_2 &hi2c2					//I2C Master
#define I2C_4 &hi2c4					//I2C Slave
#define SLAVE_ADDR 44					//Slave address

// SPI
#define SPI_1 &hspi1					//SPI Master
#define SPI_2 &hspi4					//SPI Slave

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
#define DATA_SIZE 20					//Size of data for transmission
#define TIMEOUT_TIME 100				//Timeout for UART TRANSMIT
#define DELAY_TIME 500					//Delay time for end of loop
#define INIT_VALUE 0					//Initiation value for counters and pin connected flag
#define OP_UART 0						//UART operation code
#define OP_I2C 1						//I2C operation code
#define OP_SPI 2						//SPI operation code

// BOOLS:
#define TRUE 1
#define FALSE 0

// FUNCTIONS:

// rtg_main is used instead of main function so my code won't be delted by mistake
// when making changes on the .ioc file.
void rtg_main();

// turns off all the LEDs.
void turn_off_leds();

// turns on all the LEDs.
void turn_on_leds();

// toggle the LED states
void toggle_leds();

// helper function that switch the current operation flag to the next
void switch_op();

// helper function. receives 1 or 0 for every led and switching it on or off
// based on the values of the parameters.
void leds(int green, int blue, int red);

// helper function that prints the message.
void print_msg();

// helper function that checks the transmit and received message flags.
// returns true if both flags are true, and false otherwise.
int check_msg_flags();

// helper function that calls i2c master transmit dma and i2c slave receive dma.
void i2c_transmit_receive();

// helper function that calls uart receive dma and uart transmit dma.
void uart_transmit_receive();

// helper function that calls spi receive dma and spi transmit dma.
void spi_transmit_receive();

/**
 * Initiates UART, I2C and SPI receive
 */
void init_receive();

/**
 * Helper function that prints a separator.
 */
void print_separator();

#endif /* INC_RTG_H_ */
