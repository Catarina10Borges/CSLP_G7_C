/** 
 * @file   weight.c
 *
 * @author Catarina Borges, 73865
 * @author Ricardo Torres, 64507
 *
 * @date Created on 26 de Marco de 2019, 11:47
 * @brief Calculates the weight in Kg.
 */

#include "../ADC/config_adc.h"
#include "../Weight/weight.h"

#include <xc.h>

//static uint32_t weight;
//uint32_t value;
//unsigned int weight_value;

/**
* <br>Function:     Cal_Weight()
* <br>Precondition: ADC has to be configured
* <br>Input:        None
* <br>Output:       None
* <br>Returns:      Weight in Kg.     
* <br>Side Effects: None
* <br>Overview:     Converts a value of tension in eight in Kg
* <br>Note:         None
*/
float Cal_Weight(void)
{    
    // Variables Declaration
    float weight = 0;
    float value = 0; 
    uint32_t tare = 210;
    uint32_t count=10;
    uint32_t sum = 0;
    uint32_t avg = 0;
   
    uint32_t i =0;
    
    AD1CON1bits.ASAM = 1;				// Start conversion
    while( IFS1bits.AD1IF == 0 );		// Wait while conversion not done
    IFS1bits.AD1IF = 0;	//reset AD1IF flag

    value = (ADC1BUF0*3300)/1023;
    if(value >0 && value <250)
    {
        weight = 0;
    }
    else
    {
       weight = ((value/18.752)-218.62)+tare;
    }
    //weight = (((value-tare)*200)/3300);
    
    //printf("\n\r Peso: %dKg",value);
    
    return weight;
}

//uint32_t Read_Weight()
//{
//    return value;
//}

/***************************************End Of File*************************************/