/*
-- UART main registers --
- UDRn =  contain the byte to be transmitted/received;;
- UCSRnA = USART control register A (indicators);
- UCSRnB = USART control register B (enable);
- UCSRnC = USART control C register (standard used);
- UBRRnL = contain the least significant 8 bits of baud rate;
- UBRRnH = contain the 4 most significant bits of baud rate.
*/

//DEFINES
#define   F_CPU   16000000UL
#define   BUFFER_LENGTH   64

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//FUNCTIONS PROTOTYPES
void usart_init(uint16_t bps, uint8_t fast);

uint8_t usart_tx_sts(void);
void usart_tx(uint8_t tx_data);
void usart_write(char *byte_tx);

uint8_t usart_rx_sts(void);
uint8_t usart_read();



