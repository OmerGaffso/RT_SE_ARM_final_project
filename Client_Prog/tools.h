#ifndef ARM_PROJECT_TOOLS
#define ARM_PROJECT_TOOLS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define FIRST_INDEX 0       // first index in id as chars
#define SECOND_INDEX 1      // second index in id as chars
#define THIRD_INDEX 2       // third index in id as chars
#define FOURTH_INDEX 3      // fourth index in id as chars
#define GET_FIRST_BYTE 24   // for bit moves in id
#define GET_SECOND_BYTE 16  // for bit moves in id
#define GET_THIRD_BYTE 8    // for bit moves in id

#define PERP_INDEX 4        // peripheral saved in index 4 of the buff
#define ITER_INDEX 5        // iteration number saved in index 5 
#define LENGTH_INDEX 6      // bitfield length saved in index 6 
#define DATA_INDEX 7        // data saved from index 7 till end of buffer
#define TEST_RESULT_INDEX 4  // index of test result in rx_buff

/**
 * @brief helper function to print the menu for the testing app
 */
void print_test_menu();

#endif