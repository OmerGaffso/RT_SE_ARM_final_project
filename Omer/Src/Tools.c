#include "RTG.h"

// printf
int __io_putchar(int ch)
{
	HAL_UART_Transmit(UART_DEBUG, (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}

int _write(int file, char *ptr, int len)
{
	HAL_UART_Transmit(UART_DEBUG, (uint8_t *)ptr, len, 0xFFFF);
	return len;
}

// scanf
int _read(int file, char *ptr, int len)
{
	int ch=0;
	HAL_UART_Receive(UART_DEBUG, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
	HAL_UART_Transmit(UART_DEBUG, (uint8_t *)&ch, 1,HAL_MAX_DELAY);
	if(ch==13)
	{
		ch=10;
		HAL_UART_Transmit(UART_DEBUG, (uint8_t *)&ch, 1,HAL_MAX_DELAY);
	}
	else if(ch==8)
	{
		ch=0x30;
		HAL_UART_Transmit(UART_DEBUG, (uint8_t *)&ch, 1,HAL_MAX_DELAY);
	}

	*ptr=ch;

	return 1;
}

void new_line()
{
	printf("\r\n");
}

void print_separator()
{
	printf("---------------------------------\r\n");
}

void toggle_leds()
{
	static int state = FALSE;
	if (state)
	{
		turn_off_leds();
		state = FALSE;
	}
	else
	{
		turn_on_leds();
		state = TRUE;
	}
}

void leds(int green, int blue, int red)
{
	HAL_GPIO_WritePin(GPIO_LED_PER, GPIO_LED_1, green);
	HAL_GPIO_WritePin(GPIO_LED_PER, GPIO_LED_2, blue);
	HAL_GPIO_WritePin(GPIO_LED_PER, GPIO_LED_3, red);
}

void turn_on_leds()
{
	HAL_GPIO_WritePin(GPIO_LED_PER, GPIO_LED_1, GPIO_PIN_UP);
	HAL_GPIO_WritePin(GPIO_LED_PER, GPIO_LED_2, GPIO_PIN_UP);
	HAL_GPIO_WritePin(GPIO_LED_PER, GPIO_LED_3, GPIO_PIN_UP);
}

void turn_off_leds()
{
	HAL_GPIO_WritePin(GPIO_LED_PER, GPIO_LED_1, GPIO_PIN_DOWN);
	HAL_GPIO_WritePin(GPIO_LED_PER, GPIO_LED_2, GPIO_PIN_DOWN);
	HAL_GPIO_WritePin(GPIO_LED_PER, GPIO_LED_3, GPIO_PIN_DOWN);
}
