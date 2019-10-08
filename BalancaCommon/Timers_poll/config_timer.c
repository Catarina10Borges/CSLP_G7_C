/**
 *
 * @file config_timer.c
 *
 * @author Catarina Borges, 73865
 * @author Ricardo Torres, 64507
 *
 * @date Created on 9 de Marco de 2019, 10:01
 * @brief Timer configuration of Timer 2 and 3 with interruptions and timer 4 with polling.
*/

#include "config_timer.h"

#include <xc.h>
#include <stdlib.h>
#include <stdint.h>


/**
* <br>Function: 	config_timer2()
* <br>Precondition: Prescaler2 defined
* <br>Input: 		None
* <br>Output:		None
* <br>Returns:      Nothing		
* <br>Side Effects:	None
* <br>Overview:     Configurates Timer2 with interruptions.
* <br>Note:			None
*/
void config_timer2(void)
{
	// Configuration of TIMER2
	T2CONbits.TON = 0;		//disable timer
    
    // Interruption configurations
    IFS0bits.T2IF = 0;		// interrupt flag
    IPC2bits.T2IP = 1;		// interrupt priority
    IEC0bits.T2IE = 1;		// interrupt enable
    
	T2CONbits.TCKPS = PRESCALER2;
    
	PR2 = 2499;				//PR2 = DIVIDER_CONST2
	TMR2 = 0;				// reset timer2 count register
	T2CONbits.TON = 1;		// enable timer     
}


/**
* <br>Function: 	config_timer3()
* <br>Precondition: Prescaler2 defined
* <br>Input: 		None
* <br>Output:		None
* <br>Returns:      Nothing		
* <br>Side Effects:	None
* <br>Overview:     Configurates Timer3 with interruptions.
* <br>Note:			None
*/
void config_timer3(void)
{
	// Configuration of TIMER3
	T3CONbits.TON = 0; // stop timer 3
    
    // Interruption configurations
    IFS0bits.T3IF = 0;	// interrupt flag
    IPC3bits.T3IP = 1;  // interrupt priority

	T3CONbits.TCKPS = PRESCALER2;
    PR3 = 124;
	TMR3 = 0;				// reset timer3 count register

    IEC0bits.T3IE = 1;		// interrupt enable

    T3CONbits.TON = 1;
}


/**
* <br>Function: 	config_timer4()
* <br>Precondition: Prescaler4 defined with the DIVIDER_CONST4
* <br>Input: 		None
* <br>Output:		None
* <br>Returns:      Nothing		
* <br>Side Effects:	None
* <br>Overview:     Configurates Timer4 with polling.
* <br>Note:			None
*/
void config_timer4(void)
{
	// Configuration of TIMER4
	T4CONbits.TON = 0;		//disable timer
	T4CONbits.TCKPS = PRESCALER4;
    uint32_t prx = DIVIDER_CONST4;
	PR4 = prx;
	TMR4 = 0;				// reset timer4 count register
	T4CONbits.TON = 0;		// enable timer
}
/***************************************End Of File*************************************/