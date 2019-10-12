/**
 * @file config_pwm.h
 *
 * @author Catarina Borges, 73865
 * @author Ricardo Torres, 64507
 *
 * @date Created on 8 de Marco de 2019, 12:32
 * @brief Define prototypes of config_pwm.c 
*/

#ifndef ConfigPWM_H
#define	ConfigPWM_H

#include <stdint.h>

// Define prototypes (public interface)
void config_pwm (void);
void setPWM(unsigned int dutyCycle);

#endif	/* ConfigPWM_H */

