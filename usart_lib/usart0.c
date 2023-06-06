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



/*




void usart_write(char byte_tx)
{
	while(!usart_run);
	
	usart_run = 0;
	
	UDR0 = byte_tx;
}


void usart_print(char *str)
{
	uint16_t i;
	
	for(i=0;str[i]!='\0';i++)
	{
		usart_write(str[i]);
	}
	
}


void usart_println(char *str)
{
	uint16_t i;
	
	for(i=0;str[i]!='\0';i++)
	{
		usart_write(str[i]);
	}
	usart_write(0x0A);
	usart_write(0x0D);
}


char usart_read()
{
	static uint16_t buffer_local = 0;
	char byte_rx = 0;

	byte_rx = rx_buffer[buffer_local];
	buffer_local++;
	rx_buff--;
	
	if(buffer_local>=BUFFER_LENGTH)
	{
		buffer_local = 0;
	}
	
	return byte_rx;	
}

uint8_t USART_ReceivePolling()
{
	uint8_t DataByte;
	while (( UCSR0A & (1<<RXC0)) == 0) {}; // Do nothing until data have been received
	DataByte = UDR0 ;
	return DataByte;
}
*/


/*
ISR(USART_RX_vect)
{
	static uint16_t cnt_buff = 0;
	
	rx_buffer[cnt_buff] = UDR0;
	rx_buff++;
	cnt_buff++;
	
	if(cnt_buff>=BUFFER_LENGTH)
		cnt_buff = 0;


//USART interruption
ISR(USART_TX_vect)
{
	usart_run = 1;	
}
}*/
