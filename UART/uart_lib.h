/*
-- USART main registers --
- UDRn =  contain the byte to be transmitted/received;;
- UCSRnA = USART control register A (indicators);
- UCSRnB = USART control register B (enable);
- UCSRnC = USART control C register (standard used);
- UBRRnL = contain the least significant 8 bits of baud rate;
- UBRRnH = contain the 4 most significant bits of baud rate.
*/

//DEFINES
#define   F_CPU   16000000UL
#define   BUFFER_LENGTH   16

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

//FUNCTIONS PROTOTYPES
void uart_init(uint16_t bps, uint8_t fast);

uint8_t uart_tx_sts(void);
void uart_tx(uint8_t tx_data);
void uart_write(char *byte_tx);

uint8_t uart_rx_sts(void);
uint16_t uart_read();
char uart_readString(void);
