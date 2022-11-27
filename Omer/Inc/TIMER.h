/**
 * @author Omer Penso
 *
 * This file will be responsible for all TIMER definitions and functions.
 */

#ifndef RTG_ARM_PROJECT_TIMER
#define RTG_ARM_PROJECT_TIMER

/// Extern Timer handle
extern TIM_HandleTypeDef htim3;

// Timer handle
#define TIMER &htim3

#define TIMER_DEVIEATION 10U
#define TIMER_DELAY SECOND_IN_MILLISECONS + TIMER_DEVIEATION

/**
 * This is the main function of timer test.
 * I test the timer in the following way:
 * The timer is configured to count 1 second, and when the PeriodElapsedCallback
 * reached (1 second passed), it stops the timer and switch the second_passed
 * flag to TRUE.
 * Right before I start the timer, I get the current system tick ( HAL_GetTick -
 * returns the time in milliseconds since system startup). I then pass the tick
 * to count_1_second function.
 * If by the time the function ends the flag is up, it means that the timer
 * is functioning and we return SUCCESS. (I allow 10% deviation rate based on
 * function calls and return operations).
 * @param iter - the number of iterations for the test
 * @return 0x01 if the tests passed successfully, or 0xff if tests failed.
 */
uint8_t timer_test(uint8_t iter);

/**
 * This function counts 1 second. It does that by receiving the current system
 * tick from the main timer test function, and running in a loop until
 * HAL_GetTick() - tickstart >= 1000. HAL_GetTick returns the current tick
 * count elapsed since system startup (milliseconds passed from startup).
 * 1000 milliseconds equal 1 second, so if HAL_GetTick - tickstart >= 1000 it
 * means that 1 second has passed.
 * @param tickstart - The tick count we get in the timer_test function, right
 * 						before starting our timer.
 */
void count_1_second(uint32_t tickstart);


#endif
