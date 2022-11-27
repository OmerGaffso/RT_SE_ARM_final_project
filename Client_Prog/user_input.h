#ifndef ARM_PROJECT_USER_INPUT
#define ARM_PROJECT_USER_INPUT

#include <inttypes.h>

// Max size of transmit test packet
#define TX_BUF_SIZE 263     
// Max size of receive test packet
#define RX_BUF_SIZE 5 
#define ID_LEN 4                        // The test id length is 4 bytes
#define CONTROL_FIELDS 1                // Size of control fields
#define MAX_BITFIELD_LEN 256            // Data max length in bytes
#define MIN_ITERATIONS 1                // Sets minimum allowed iterations

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

#endif