/*
 * IncFile1.h
 *
 * Created: 01/05/2022 14:08:25
 *  Author: h3v0x
 */ 

//CPU clock
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


#define   set_bit(reg,bit)		(reg |= (1<<bit))
#define   clr_bit(reg,bit)    (reg &= ~(1<<bit))

