/*
 * usart0.c
 *
 * Created: 04/06/2023 01:23:15
 *  Author: h3v0x

 */ 

//Includes
#include "usart0.h"

//Global
volatile char rx_buffer[BUFFER_LENGTH] = {0x00};


//USART initialization
void usart_init(uint16_t bps, uint8_t fast)
{
	
	if(fast){ //double speed mode
		
		UCSR0A |= (1<<U2X0);
		UBRR0 = (F_CPU/(8UL * bps))-1;
	 
	}else{ //default operation USART
		
		UCSR0A &= ~(1<<U2X0);
		UBRR0 = (F_CPU/(16UL * bps))-1;
		
	}
	
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);   //Enable USART transmitter/receiver
			  	  
	UCSR0C = 0x06; // USART assinc, no parity, 8 data bits, 1 stop bit	
	
//	sei(); //Enable global interrupt	 
}


uint8_t usart_tx_sts()
{
	return (UCSR0A & (1<<UDRE0));
}


void usart_tx(uint8_t tx_data)
{
	UDR0 = tx_data;
}


void usart_write(char *byte_tx)
{
	for (; *byte_tx!=0; byte_tx++)
	{
		while(!usart_tx_sts());
		usart_tx(*byte_tx);
	}
		
}


uint8_t usart_rx_sts()
{
	return (UCSR0A & (1<<RXC0));
}


uint8_t usart_read()
{
	return UDR0;	
}


