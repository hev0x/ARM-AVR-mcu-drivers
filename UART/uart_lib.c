/*
 * usart0.c
 *
 * Created: 04/06/2023 01:23:15
 *  Author: h3v0x
 */ 

//Includes
#include "uart_lib.h"

//Global
volatile char rx_buffer[BUFFER_LENGTH] = {0};
volatile uint16_t rx_buff = 0;

//USART initialization
void uart_init(uint16_t bps, uint8_t fast)
{
	if(fast)
	{ //double speed mode
		UCSR1A |= (1<<U2X0);
		UBRR1 = (F_CPU/(8UL * bps))-1;
	}
	else
	{ //default operation USART
		UCSR1A &= ~(1<<U2X0);
		UBRR1 = (F_CPU/(16UL * bps))-1;		
	}
	UCSR1B = (1<<RXEN1) | (1<<TXEN1);   //Enable USART transmitter/receiver		  	  
	UCSR1C = 0x06; // USART assinc, no parity, 8 data bits, 1 stop bit	
}


uint8_t uart_tx_sts()
{
	return (UCSR1A & (1<<UDRE1));
}

uint8_t uart_rx_sts()
{
	return (UCSR1A & (1<<RXC1));
}

void uart_tx(uint8_t tx_data)
{
	UDR1 = tx_data;
}

uint16_t uart_read()
{
	return UDR1;
}


void uart_write(char *byte_tx)
{
	for (; *byte_tx!=0; byte_tx++)
	{
		while(!uart_tx_sts());
		uart_tx(*byte_tx);
	}		
}
