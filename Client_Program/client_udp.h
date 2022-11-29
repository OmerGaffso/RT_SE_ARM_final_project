#ifndef ARM_PROJECT_CLIENT_UDP
#define ARM_PROJECT_CLIENT_UDP
#include <inttypes.h>
#include "tools.h"
#include "user_input.h"

#define IP_ADDRESS "192.168.1.10"       // Server IP (stm32f746zg) 
#define PORT 55555                      // Server port
#define FLAG_ZERO 0
#define EQUAL_ZERO 0
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define MILLISECONDS_CONV 1000000    // used in time delta calculations
#define SLEEP_TIME 1


// received packet from the server (after test)
typedef struct resv
{
        uint32_t test_id;
        uint8_t test_result;
} resv_t;

#endif