/*
 * File: config_pwm.c
 *
 * Author: Catarina Borges, 73865
 * Author: Ricardo Torres, 64507
 *
 * Created on 8 de Março de 2019, 12:30
*/

#include "config_pwm.h"
#include "../Timers_poll/config_timer.h"

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

void config_pwm (void)
{
    // Set OC1
    OC1CONbits.OCM = 6; // OCM = 0b110 : OC1 in PWM mode,
    OC1CONbits.OCTSEL = 1; // Timer 3 is clock source of OCM
    OC1RS = 0; // Compute OC1xRS value
    OC1CONbits.ON = 1;     // Enable OC1
}

void setPWM(unsigned int dutyCycle)
{
    // duty_cycle must be in the range [0, 100]
    OC1RS = ((DIVIDER_CONST3+1)*(dutyCycle))/100; // Evaluate OC1RS as a function of "dutyCycle"
}