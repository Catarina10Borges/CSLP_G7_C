/*
 * File: temperature.c
 *
 * Author: Catarina Borges, 73865
 * Author: Ricardo Torres, 64507
 *
 * Created on 26 de Março de 2019, 11:47
*/

#include "../ADC/config_adc.h"
#include "../Timers_poll/config_timer.h"
#include "temperature.h"

#include <xc.h>


uint32_t temperature(void)
{
    // Variables declaration
    uint32_t temperature = 0;
    uint32_t value = 0;
    uint32_t sum = 0;
    uint32_t avg = 0;
    uint32_t med = 100;
    uint32_t i = 0;
    
    for(i=0;i<=med;i++)
    {
    AD1CON1bits.ASAM = 1;				// Start conversion
    while( IFS1bits.AD1IF == 0 );		// Wait while conversion not done
    IFS1bits.AD1IF = 0;	//reset AD1IF flag
    
    
    value = (ADC1BUF1*3300)/1023;  
    temperature = ((value - 500) /(10)); // Convert tension to degrees, from linear regression
    
    sum = sum+temperature;
    }
    
    avg = sum/med;
    sum = 0;

    return avg;
}
