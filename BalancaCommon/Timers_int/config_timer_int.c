/*
 * File: config_timer.c
 *
 * Author: Catarina Borges, 73865
 * Author: Ricardo Torres, 64507
 *
 * Created on 8 de Março de 2019, 12:33
*/

#include "config_timer_int.h"

#include <xc.h>
#include <stdlib.h>
#include <stdint.h>


void config_timer2(void)
{
	// Configuration of TIMER2
	T2CONbits.TON = 0;		//disable timer
	T2CONbits.TCKPS = PRESCALER2;
    uint32_t prx = ((PBCLOCK/(8*(ADC_SAMPLING_FREQ)))-1);
	PR2 = prx;
    //PR2 = DIVIDER_CONST2
	TMR2 = 0;				// reset timer2 count register
	T2CONbits.TON = 1;		// enable timer

	IFS0bits.T2IF = 0; // Reset interrupt flag
    IPC2bits.T2IP = 5; //set interrupt priority (1..7) *** Make sure it matches iplx in isr declaration ***
    IEC0bits.T2IE = 0; // Enable T2 interrupts
}

void config_timer3(void)
{
	// Configuration of TIMER2
	T3CONbits.TON = 0;		//disable timer
	T3CONbits.TCKPS = PRESCALER3;
	PR3 = DIVIDER_CONST3;
	TMR3 = 0;				// reset timer2 count register
	T3CONbits.TON = 1;		// enable timer

	IFS0bits.T3IF = 0; // Reset interrupt flag
    IPC3bits.T3IP = 5; //set interrupt priority (1..7) *** Make sure it matches iplx in isr declaration ***
    IEC0bits.T3IE = 1; // Enable T3 interrupts
    
}

void config_timer4(void)
{
	// Configuration of TIMER2
	T4CONbits.TON = 0;		//disable timer
	T4CONbits.TCKPS = PRESCALER4;
    uint32_t prx = DIVIDER_CONST4;
	PR4 = prx;
	TMR4 = 0;				// reset timer2 count register
	T4CONbits.TON = 1;		// enable timer

	IFS0bits.T4IF = 0; // Reset interrupt flag
    IPC4bits.T4IP = 5; //set interrupt priority (1..7) *** Make sure it matches iplx in isr declaration ***
    IEC0bits.T4IE = 1; // Enable T4 interrupts
}