/*
 * File: config_adc.c
 *
 * Author: Catarina Borges, 73865
 * Author: Ricardo Torres, 64507
 *
 * Created on 4 de Março de 2019, 11:47
*/

#include "config_adc.h"

#include <xc.h>
#include <stdlib.h>
#include <stdint.h>


void config_adc (void)
{
    //Disable JTAG interface
    //DDPCONbits.JTAGEN = 0;

    // Generic part
    AD1CON1bits.SSRC = 7; // Internal counter ends sampling and starts conversion
    AD1CON1bits.CLRASAM = 1; //Stop conversion when 1st A/D converter interrupt is generated and clears ASAM bit automatically
    AD1CON1bits.FORM = 0; // Integer 16 bit output format
    
    AD1CON2bits.VCFG = 0; // VR+=AVdd; VR-=AVss
    AD1CON2bits.SMPI = 2; // Number (+1) of consecutive conversions, stored in ADC1BUF0...ADCBUF{SMPI}
    
    AD1CON3bits.ADRC = 1; // ADC uses internal RC clock
    AD1CON3bits.SAMC = 16; // Sample time is 16TAD ( TAD = 100ns)
    
    AD1CON2bits.CSCNA = 1; // Enable Scan mode to BUF
    
    //Weight
    //AD1CHSbits.CH0SA = 0; // Select AN0 as input for A/D converter
    TRISBbits.TRISB0 = 1; // Set AN0 to input mode
    AD1PCFGbits.PCFG0 = 0; // Set AN0 to analog mode
    AD1CSSLbits.CSSL0 = 1; // select AN0
    AD1CON1bits.ON = 1; // Enable A/D module
    
    // Set AN1 as input Temperature
    //AD1CHSbits.CH0SA = 1; // Select AN1 as input for A/D converter
    TRISBbits.TRISB1 = 1; // Set AN1 to input mode
    AD1PCFGbits.PCFG1 = 0; // Set AN1 to analog mode
    AD1CSSLbits.CSSL1 = 1; // select AN1
    AD1CON1bits.ON = 1; // Enable A/D module
    
     //Height
    TRISBbits.TRISB2 = 1; // Set AN2 to input mode
    AD1PCFGbits.PCFG2 = 0; // Set AN2 to analog mode
    AD1CSSLbits.CSSL2 = 1; // select AN2
    AD1CON1bits.ON = 1; // Enable A/D module
}

