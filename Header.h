/*
 * Header.h
 *
 * Created: 3/7/2020 11:54:37 AM
 *  Author: Ebtsam
 */ 


#ifndef HEADER_H_
#define HEADER_H_

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>

# define SETBIT(reg,bit) (reg|=(1<<bit))
# define CLRBIT(reg,bit) (reg&=(~(1<<bit)))
# define TOGBIT(reg,bit) (reg^=(1<<bit))
# define GETBIT(reg,bit) (0b1& (reg>>bit))





#endif /* HEADER_H_ */