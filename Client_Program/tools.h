#ifndef ARM_PROJECT_TOOLS
#define ARM_PROJECT_TOOLS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

// Max size of transmit test packet
#define TX_BUF_SIZE 263     
// Max size of receive test packet
#define RX_BUF_SIZE 5 
#define ID_LEN 4                        // The test id length is 4 bytes
#define CONTROL_FIELDS 1                // Size of control fields
#define MAX_BITFIELD_LEN 256            // Data max length in bytes
#define MIN_ITERATIONS 1                // Sets minimum allowed iterations

#define FIRST_INDEX 0       // first index in id as chars
#define SECOND_INDEX 1      // second index in id as chars
#define THIRD_INDEX 2       // third index in id as chars
#define FOURTH_INDEX 3      // fourth index in id as chars
#define GET_FIRST_BYTE 24   // for bit moves in id
#define GET_SECOND_BYTE 16  // for bit moves in id
#define GET_THIRD_BYTE 8    // for bit moves in id

// #define PERP_INDEX 4        // peripheral saved in index 4 of the buff
// #define ITER_INDEX 5        // iteration number saved in index 5 
// #define LENGTH_INDEX 6      // bitfield length saved in index 6 
// #define DATA_INDEX 7        // data saved from index 7 till end of buffer
// #define TEST_RESULT_INDEX 4  // index of test result in rx_buff

// Default values for automated tests
#define DEFAULT_ITERATIONS              10
#define DEFAULT_DATA_LEN                26 //len of "abcdefghijklmnopqrstuvwxyz"

// packet to send to the server 
typedef struct packet
{     
        uint32_t test_id;
        uint8_t test_peri;
        uint8_t test_iter;
        uint8_t test_bitfield_len;
        char test_bitfield_data[MAX_BITFIELD_LEN];
} packet_t;

/**
 * @brief helper function to print the menu for the testing app
 */
void print_test_menu();

/**
 * @brief helper function to print the main menu
 * 
 */
void print_main_menu();

/**
 * @brief This function will receive the user input and assign the fields
 * to the packet received as parameter before transmiting it to the server.
 * 
 * @param packet - The packet to be transmited
 * @param next_test_id - the id for the test packet
 * @return true - if the packet was assignd for transmiting
 * @return false - if the user entered 0 (wants to exit the test program)
 */
bool manual_test(packet_t * packet, uint32_t next_test_id);

// TODO: Maybe add a parameter to tests function for ID and build the entire
// packet in those functions.

/**
 * @brief This function will assign the fields of the packet received as 
 * parameter with default values before transmiting it to the server.
 * 
 * @param packet - The packet to be transmited
 * @param next_test_id - the id for the test packet
 * @return true - if the packet was assignd for transmiting
 * @return false - if the user entered 0 (wants to exit the test program)
 */
bool automated_test(packet_t * packet, uint32_t next_test_id);

#endif