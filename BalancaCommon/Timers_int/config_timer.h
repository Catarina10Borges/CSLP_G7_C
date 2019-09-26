/*
 * File: config_timer.h
 *
 * Author: Catarina Borges, 73865
 * Author: Ricardo Torres, 64507
 *
 * Created on 8 de Março de 2019, 12:34
*/

#ifndef ConfigTIMER_H
#define ConfigTIMER_H

#include <stdint.h>

//Define constants
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz
#define ADC_SAMPLING_FREQ 100   // define sampling frequency
#define PRESCALER2 3 
#define PRESCALER3 0
                        /*
                        111 = 1:256 prescale value
                        110 = 1:64 prescale value
                        101 = 1:32 prescale value
                        100 = 1:16 prescale value
                        011 = 1:8 prescale value
                        010 = 1:4 prescale value
                        001 = 1:2 prescale value
                        000 = 1:1 prescale value
                        */
//#define DIVIDER_CONST2 0xC34F // 0xFFFF
#define DIVIDER_CONST3 19999 //0x4E1F

void config_timer2(void);
void config_timer3(void);

#endif /* ConfigTIMER_H */
