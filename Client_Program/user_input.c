#include "tools.h"
#include "user_input.h"

uint8_t test_mode_choice()
{
    unsigned int choice;
    scanf("%u", &choice);

    switch (choice)
    {
        case AUTOMATIC:
            return AUTOMATIC;
        case MANUAL:
            return MANUAL;
        case EXIT:
            return EXIT;
        default:
            printf("Invalid test choice.\n");
            return EXIT;
    }
} 

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
        case UART:
            return CODE_UART;
        case SPI:
            return CODE_SPI;
        case I2C:
            return CODE_I2C;
        case ADC:
            return CODE_ADC;
        case EXIT:
            return EXIT;
        default:
            printf("Invalid peripheral choice.\n");
            return EXIT;
    }
}

/**
 * @brief Get the test iteration number from the user
 */
uint8_t get_iteration()
{
    uint8_t iter;
    printf("Enter iteration number: (255 max)\n");
    scanf("%hhu", &iter);
    if (iter == 0)
        return MIN_ITERATIONS;
        
    getchar();
    return iter;
}

/// @brief get the data string from user
void get_bitfield_data(char *buff)
{
   char ch;
   int cnt = 0;
   // get chars until user presses ENTER or user enters 255 chars
   while((ch = getchar()) != '\n' && cnt < MAX_BITFIELD_LEN)
   {
      buff[cnt] = ch;
      ++cnt;
   }
}

