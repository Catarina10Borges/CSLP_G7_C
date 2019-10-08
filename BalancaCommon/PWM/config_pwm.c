/**
 * @file config_pwm.c
 *
 * @author Catarina Borges, 73865
 * @author Ricardo Torres, 64507
 *
 * @date Created on 8 de Março de 2019, 12:30
 * @brief Configure the PWM (Pulse Width Modulation) and it is defined to calculate the height.
*/

#include "config_pwm.h"
#include "../Timers_poll/config_timer.h"

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

/**
* <br>Function: 	config_pwm()
* <br>Precondition: Timer initialized
* <br>Input: 		None
* <br>Output:		None
* <br>Returns:      Nothing		
* <br>Side Effects:	None
* <br>Overview:     Configurates the PWM.
	<br>			Timer 3 is clock source of OCM
* <br>Note:			None
*/
void config_pwm (void)
{
    // Set OC1
    OC1CONbits.OCM = 6; // OCM = 0b110 : OC1 in PWM mode,
    OC1CONbits.OCTSEL = 1; // Timer 3 is clock source of OCM
    OC1RS = 0; // Compute OC1xRS value
    OC1CONbits.ON = 1;     // Enable OC1
}


/**
* <br>Function: 	set_pwm()
* <br>Precondition: DIVIDER_CONST3 initialized
* <br>Input: 		duty_cycle
* <br>Output:		value of PWM
* <br>Returns:      Nothing		
* <br>Side Effects:	None
* <br>Overview:     Sets the PWM.
* <br>Note:			duty_cycle must be in the range [0,100]
*/
void setPWM(unsigned int dutyCycle)
{
    // duty_cycle must be in the range [0, 100]
    OC1RS = ((DIVIDER_CONST3+1)*(dutyCycle))/100; // Evaluate OC1RS as a function of "dutyCycle"
}
/***************************************End Of File*************************************/