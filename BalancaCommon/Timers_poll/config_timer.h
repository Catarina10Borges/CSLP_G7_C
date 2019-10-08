/**
 * @file config_timer.h
 *
 * @author Catarina Borges, 73865
 * @author Ricardo Torres, 64507
 *
 * @date Created on 9 de Marco de 2019, 10:02
 * @brief Define prototypes and constants of config_timer.c 
*/

#ifndef ConfigTIMER_H
#define ConfigTIMER_H

#include <stdint.h>

//Define constants
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz
#define FREQ2 100  // define sampling frequency
#define FREQ3 1500
#define PRESCALER2 4 
#define PRESCALER3 4
#define PRESCALER4 2
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
#define DIVIDER_CONST3 19999 
#define DIVIDER_CONST4 499 // 80KHz

// Define prototypes (public interface)
void config_timer2(void);
void config_timer3(void);
void config_timer4(void);

#endif /* ConfigTIMER_H */

