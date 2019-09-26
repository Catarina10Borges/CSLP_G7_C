/*
 * File: config_timer.c
 *
 * Author: Catarina Borges, 73865
 * Author: Ricardo Torres, 64507
 *
 * Created on 9 de Março de 2019, 10:01
*/

#include "config_timer.h"

#include <xc.h>
#include <stdlib.h>
#include <stdint.h>

void config_timer2(void)
{
	// Configuration of TIMER2
	T2CONbits.TON = 0;		//disable timer
    
    IFS0bits.T2IF = 0;
    IPC2bits.T2IP = 1;
    IEC0bits.T2IE = 1;
    
	T2CONbits.TCKPS = PRESCALER2;
    
	PR2 = 2499;
    //PR2 = DIVIDER_CONST2
	TMR2 = 0;				// reset timer2 count register
	T2CONbits.TON = 1;		// enable timer   
    
}

void config_timer3(void)
{
	// Configuration of TIMER2
	T3CONbits.TON = 0; // stop timer 3
    
    // Interruption configurations
    IFS0bits.T3IF = 0;
    IPC3bits.T3IP = 1;  
	T3CONbits.TCKPS = PRESCALER2;
    PR3 = 124;
	TMR3 = 0;				// reset timer2 count register
    IEC0bits.T3IE = 1;
    T3CONbits.TON = 1;


}

void config_timer4(void)
{
	// Configuration of TIMER2
	T4CONbits.TON = 0;		//disable timer
	T4CONbits.TCKPS = PRESCALER4;
    uint32_t prx = DIVIDER_CONST4;
	PR4 = prx;
	TMR4 = 0;				// reset timer2 count register
	T4CONbits.TON = 0;		// enable timer
}
