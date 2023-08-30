//DEFINES
#define   F_CPU   16000000UL


//Includes
#include <avr/io.h>
#include <util/delay.h>


//Defines based on Pin Registers of ATmega2560
#define CS_PIN   PB0 // Chip Select Pin
#define MISO_PIN   PB3 // Master In Slave Out (MISO) pin
#define MOSI_PIN   PB2 // Master Out Slave In (MOSI) pin
#define SCK_PIN   PB1  // Serial Clock PIN (SCK)


//
void SPI_Chip_Init();
void E2PROM_Write(uint16_t memAddress, uint8_t data);
uint8_t E2PROM_Read(uint16_t memAddress);
void Chip_Erase();

