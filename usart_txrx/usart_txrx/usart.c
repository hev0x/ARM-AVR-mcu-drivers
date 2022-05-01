#include "macros.h"
#include "usart_conf.h"


void usart_config();
void usart_tx(uint8_t datab);
void usart_rx(uint8_t datac);


void usart_config()
{
	//baud rate config
	UBRR0H = BAUD_PRESCALER >> 8;
	UBRR0L = BAUD_PRESCALER;
	
	//config data format
	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
	
	//enable TX and RX
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
}

//send data via USART
void usart_tx(uint8_t datab)
{
	while (( UCSR0A & (1<<UDRE0)) == 0);
	UDR0 = datab;
	
}

void usart_rx(uint8_t datac)
{
	//TODO	
}