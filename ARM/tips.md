## printf and scanf over STM32 UART

* The code below is intended to redirect the printf function to a UART for debugging messages:

```C
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

GETCHAR_PROTOTYPE
{
  uint8_t ch = 0;

  /* Clear the Overrun flag just before receiving the first character */
  __HAL_UART_CLEAR_OREFLAG(&huart2);

  /* Wait for reception of a character on the USART RX line and echo this
   * character on console */
  HAL_UART_Receive(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}


//User application code example

  /* USER CODE BEGIN 2 */
/*
  setvbuf(stdin, NULL, _IONBF, 0); //

  char str[80];
  int i;
  printf("Enter your family name: ");
  scanf("%79s", str);
  printf("\r\n");

  printf("Enter your age: ");
  scanf("%d", &i);
  printf("\r\n");

  printf("Mr. %s, %d years old.\n", str, i);
  printf("\r\n");
*/
```


