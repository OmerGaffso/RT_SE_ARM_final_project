#ifndef ARM_PROJECT_FILES
#define ARM_PROJECT_FILES
#include <stdint.h>

#define FILE_PATH "./source/"

#define NAME_LEN 255
#define UINT32_MAX_CHAR 11  // buffer to save the id in a string ('\0' included)

// for time to be correct
#define MONTH_FIX 1
#define YEAR_FIX 1900

/**
 * @brief Get the id of the next text from id_cnt.txt file before starting 
 * the main loop of the main function.
 * 
 * @return uint32_t - the id of the next test
 */
uint32_t get_id();

/**
 * @brief saves the new id counter to id_cnt.txt file in the end of the loop 
 * iteration, replacing the old value.
 * 
 * @param id - the next id for the next test
 */
void save_id(uint32_t id);

/**
 * @brief save the test info to the file. creates a file with a name as the 
 * test id, and saves the time the test was initiated, the test id, the 
 * result of the test (1 is success, 255 is failure) and the time it took 
 * for the test to be completed and sent back to the client.
 * 
 * @param test_id - the test id received from the server after the test.
 * @param test_result - the result of the test
 * @param time_delta - the time it took to the test to be completed.
 */
void save_test_to_file(uint32_t test_id, uint8_t test_result, double time_delta);


#endif