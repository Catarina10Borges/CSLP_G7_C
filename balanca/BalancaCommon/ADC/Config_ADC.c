/**
 * 
 * @file Config_Adc.c
 *
 * @author Catarina Borges, 73865
 * @author Ricardo Torres, 64507
 * 
 * @date Created on 4 de Marco de 2019, 11:47
 *
 * MPLAB X IDE v5.10 + XC32 v2.15
 *
 * Target: Digilent chipKIT MAx32 board 
 * 
 * @brief This function has all the variables definied so the ADC can correctly work.
 *
 *
 */

#include "config_adc.h"
#include <xc.h>
#include <stdlib.h>
#include <stdint.h>


/**
* <br> Function: 	Config_Adc()
* <br> Precondition: 
* <br> Input: 		None
* <br> Output:		None
* <br> Returns:      Nothing		
* <br> Side Effects:	None
* <br> Overview:     ADC main configuration.
* <br> Note:			AN0 is used by weight()
				<br>AN1 is used by temperature()
				<br>AN2 is used by heigth()

*/	
void Config_ADC (void)
{
    //Disable JTAG interface
    //DDPCONbits.JTAGEN = 0;

    // Initialize ADC module
    // Polling mode, AN0 as input

    // Generic part
    AD1CON1bits.SSRC = 7; // Internal counter ends sampling and starts conversion
    AD1CON1bits.CLRASAM = 1; //Stop conversion when 1st A/D converter interrupt is generated and clears ASAM bit automatically
    AD1CON1bits.FORM = 0; // Integer 16 bit output format
    AD1CON2bits.VCFG = 0; // VR+=AVdd; VR-=AVss
    AD1CON2bits.SMPI = 0; // Number (+1) of consecutive conversions, stored in ADC1BUF0...ADCBUF{SMPI}
    AD1CON3bits.ADRC = 1; // ADC uses internal RC clock
    AD1CON3bits.SAMC = 16; // Sample time is 16TAD ( TAD = 100ns)
    // Set AN0 as input
    AD1CHSbits.CH0SA = 0; // Select AN0 as input for A/D converter
    TRISBbits.TRISB0 = 1; // Set AN0 to input mode
    AD1PCFGbits.PCFG0 = 0; // Set AN0 to analog mode
    // Enable module
    AD1CON1bits.ON = 1; // Enable A/D module (This must be the ***last instruction of configuration phase***)
}
/***************************************End Of File*************************************/