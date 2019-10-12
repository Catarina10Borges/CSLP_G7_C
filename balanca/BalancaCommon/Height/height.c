/** 
 * @file   height.c
 *
 * @author Catarina Borges, 73865
 * @author Ricardo Torres, 64507
 *
 * @date Created on 26 de Marco de 2019, 11:47
 * @brief Creates the bursts needed to the ultrasonic sensor work, so it is possible to calculate the height of an individual.
 */

#include "height.h"
#include "../PWM/config_pwm.h"
#include "../Timers_poll/config_timer.h"
#include "../Temperature/temperature.h"

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>



/**
* <br> Function:     height()
* <br> Precondition: timer4 configured
* <br> Input:        None
* <br> Output:       None
* <br> Returns:      None     
* <br> Side Effects: None
* <br> Overview:     Produces the burts needed by the ultrasonic sensor.
       <br>         And produces the waiting time, so it is possible to
       <br>     observe the eco.
* <br>Note:         None
*/   
void height ()
{
    config_timer4();
   
    /* config_adc();
    
    AD1CHSbits.CH0SA = 2; // Select AN0 as input for A/D converter
    TRISBbits.TRISB0 = 1; // Set AN0 to input mode
    AD1PCFGbits.PCFG2 = 0; // Set AN0 to analog mode
    AD1CON1bits.ON = 1; // Enable A/D module
    
    AD1CON1bits.ASAM = 1;				// Start conversion
    while( IFS1bits.AD1IF == 0 );		// Wait while conversion not done
    IFS1bits.AD1IF = 0;	//reset AD1IF flag*/
    
    // set RB3 as output
    TRISBbits.TRISB3 = 0;
    
    //Variable Declaration
    uint32_t burst = 20;
    uint32_t i;
    uint32_t temperature;
    uint32_t kelvin;        // temeprature in Kelvin
    uint32_t c;             // sound velocity that depends on temperature
    uint32_t distance;
    
    
    TMR4 = 0;
     
    for(i = 0; i < (2*burst); i++)
    {
        if(i%2 == 0)
        {
            PORTBbits.RB3 = 1;
        }
        else
        {
            PORTBbits.RB3 = 0;
        }
        while(IFS0bits.T4IF == 0);
        IFS0bits.T4IF = 0;
    } 
    
    // Waiting Time
    // Waits 2ms -> 160 cicles at 80KHz

    for(i=0; i < 160; i++)
    {
        while(IFS0bits.T4IF == 0);
        IFS0bits.T4IF = 0;  
    }
    
    
    /*// Device Driver
    temperature = temperature();
    kelvin = temperature + 273;
   
    c = 20.06*sqrt(kelvin);
    t = (burst*(1/40000))+ 1200 + //o que vamos receber da ADC
    
    distance = ((c * (t/1000000))/2);
    height = ultra_height - distance - 15;  // altura em cm */
}
/***************************************End Of File*************************************/

