#include "asf.h"

Byte GetChar();
void PutChar(const uint8_t c);

int main()
{
SystemInit();
WDT->WDT_MR |= WDT_MR_WDDIS;

/*Enable clock for USART*/
PMC->PMC_PCER0 = 1 << ID_USART0;

/*Enable clock for peripheral*/
REG_PMC_PCER0 = PMC_PCER0_PID11;
REG_PMC_PCER0 = PMC_PCER0_PID10;

/*Disable Rx Tx PIO line*/
PIOA->PIO_PDR |= PIO_PA10A_RXD0;
PIOA->PIO_PDR |= PIO_PA11A_TXD0;

/*Set pins to use peripheral A*/
PIOA->PIO_ABSR &= ~PIO_PA10A_RXD0;
PIOA->PIO_ABSR &= ~PIO_PA11A_TXD0;

//Enable the pull up on the Rx and Tx pins
PIOA->PIO_PUER |= PIO_PA10A_RXD0;
PIOA->PIO_PUER |= PIO_PA11A_TXD0;

/*Disable PDC Requests*/
USART0->US_PTCR = US_PTCR_RXTDIS | US_PTCR_TXTDIS;

/*Reset receiver ,transmitter & Status register, Disable RX and TX*/
USART0->US_CR= US_CR_RSTRX | US_CR_RSTTX | US_CR_RXDIS | US_CR_TXDIS |US_CR_RSTSTA;

/*Disable all Interrupt*/
USART0->US_IDR = 0xFFFFFFFF;

/*Select USART Normal Mode No Parity and Clock Source Internal MCU*/
USART0->US_MR = US_MR_USART_MODE_NORMAL | US_MR_USCLKS_MCK| US_MR_CHMODE_NORMAL | US_MR_CHRL_8_BIT| US_MR_PAR_NO;

/*Set the baud rate to 300 value*/
//uint32_t baude = 300;
USART0->US_BRGR = (84000000/300*16);

/*Enable Rx and Tx communication port*/
USART0->US_CR &= ~(US_CR_RSTRX | US_CR_RSTTX | US_CR_RXDIS | US_CR_TXDIS | US_CR_RSTSTA);

/*Enable receiver and transmitter*/
USART0->US_CR= US_CR_RXEN | US_CR_TXEN;

while(1)
{
PutChar('N');
}
}

Byte GetChar()
{
//Wait until receiver ready
while((USART0->US_CSR & US_CSR_RXRDY)==US_CSR_RXRDY)

return USART0->US_RHR;
}

void PutChar(const uint8_t c)
{
// Check if the transmitter is ready
while(!(USART0->US_CSR & US_CSR_TXRDY));
// Send the character
USART0->US_THR = c;

}
