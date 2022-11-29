#ifndef ARM_PROJECT_USER_INPUT
#define ARM_PROJECT_USER_INPUT

#include <inttypes.h>

// test mode choices
#define AUTOMATIC 1
#define MANUAL 2

// peripheral choices
#define TIMER 1
#define UART 2
#define SPI 3
#define I2C 4
#define ADC 5

// peripheral test code
#define CODE_TIMER 0x01
#define CODE_UART 0x02
#define CODE_SPI 0x04
#define CODE_I2C 0x08
#define CODE_ADC 0x10

#define EXIT 0

/**
 * @brief get the user choice for test mode (automated or manual)
 * 
 * @return uint8_t - the action code.
 */
uint8_t test_mode_choice();

/**
 * @brief get user choice for test peripheral choice.
 * 
 * @return uint8_t - peripheral test code indicated above
 */
uint8_t peripheral_choice();

/**
 * @brief Get the number of iterations the peripheral test will run.
 * 
 * @return uint8_t - the number of iterations.
 */
uint8_t get_iteration();

/**
 * @brief Get the string data for the test packet
 * 
 * @param buff - the buffer to hold the data entered by the user.
 */
void get_bitfield_data(char *buff);

#endif