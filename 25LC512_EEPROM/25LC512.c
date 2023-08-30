/*
 ---------------------------------------------------------
														 | 
 • SPI Registers to config:  							 |
														 |
 - SPCR = Control register;								 |
 - SPSR = Status register;								 |
 - SPRD = 8bit register for data transmit/receive.		 |			
														 |
 ---------------------------------------------------------
 */ 


//Includes
#include "25LC512.h"

//
void SPI_Chip_Init(){
	
	DDRB   |= (1 << MOSI_PIN) | (1 << SCK_PIN) | (1 << CS_PIN); //MOSI, SCK and CS config Pin as Output
	PORTB  |= CS_PIN;   // Init with Slave Select (SS) pin in High Logic Level
	
	SPCR   |= (0 << SPIE) | //Disable SPI INT
			  (1 << SPE)  | //Enable SPI Hardware
			  (1 << MSTR) | //Config as Master SPI
			  (0 << CPOL) | //Mode 0:
			  (0 << CPHA) |
			  (1 << SPR0); //fclk/128 (SPI BUS speed)	 
}

// SPI data transmit
void SPI_TX(uint8_t data){
	
	SPDR = data;
	
	while(!(SPSR &(1 << SPIF))); //Wait data send
}

// SPI data receive
uint8_t SPI_RX(void){
	
	SPI_TX(0xFF); //Send a byte to init data exchange
	return SPDR;
	
}

//
void E2PROM_Write(uint16_t memAddress, uint8_t data){
	
	PORTB &= ~(1 << CS_PIN); //Enable Chip Select
	
	SPI_TX(0x06); //WREN command (Write enable)
	PORTB |= (1 << CS_PIN); //Disable Chip Select
	_delay_ms(10); //Delay required to correct EEPROM operation
	
	PORTB &= ~(1 >> CS_PIN); //Enable Chip Select
	SPI_TX(0x02); //Write command
	SPI_TX((memAddress >> 8) & 0xFF); // MSB Address
	SPI_TX(memAddress & 0xFF); // LSB Address
	SPI_TX(data); // Data to write
	
	PORTB |= (1 << CS_PIN); //Disable Chip Select
	_delay_ms(10);//Delay required to correct EEPROM operation
	
}

uint8_t E2PROM_Read(uint16_t memAddress){
	
	PORTB &= ~(1 << CS_PIN);
	
	SPI_TX(0x03); //Read command
	SPI_TX((memAddress >> 8) & 0xFF); // MSB Address
	SPI_TX(memAddress & 0xFF); // LSB Address
	uint8_t data = SPI_RX();
	
	PORTB |= (1 << CS_PIN); //Disable Chip Select
	return data;

}