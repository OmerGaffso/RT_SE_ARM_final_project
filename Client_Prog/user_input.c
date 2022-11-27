#include "tools.h"
#include "user_input.h"

/**
 * @brief get user test peripheral choice, and return its code.
 */
uint8_t peripheral_choice()
{
    unsigned int choice;
    scanf("%u", &choice);

    switch (choice)
    {
        case TIMER:
            return CODE_TIMER;
            break;
        case UART:
            return CODE_UART;
            break;
        case SPI:
            return CODE_SPI;
            break;
        case I2C:
            return CODE_I2C;
            break;
        case ADC:
            return CODE_ADC;
            break;
        case EXIT:
            return EXIT;
            break; 
        default:
            printf("Invalid peripheral choice.\n");
            return EXIT;
            break;
    }
}

/**
 * @brief Get the test iteration number from the user
 */
uint8_t get_iteration()
{
    uint8_t iter;
    printf("Enter iteration number: (256 max)\n");
    scanf("%hhu", &iter);
    if (iter == 0)
        return MIN_ITERATIONS;
        
    return iter;
}


