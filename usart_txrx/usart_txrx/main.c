/*
 * usart_send.c
 *
 * Created: 01/05/2022 01:11:45
 * Author : h3v0x
 */ 

#include "macros.h"


extern void usart_config();
extern void usart_tx(uint8_t datab);

int main(void)
{
    
	usart_config();
	
    while (1) 
    {
		
    }
}

