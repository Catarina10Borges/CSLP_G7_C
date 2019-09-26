/* 
 * File:   main.c // IMC
 * 
 * Author: Catarina Borges, 73865
 * Author: Ricardo Torres, 64507
 *
 * Created on 26 de Março de 2019, 11:47
 */

#include "../BalancaCommon/ConfigBits/config_bits.h"
#include "../BalancaCommon/Timers_poll/config_timer.h"
#include "../BalancaCommon/ADC/config_adc.h"
#include "../BalancaCommon/UART/uart.h"
#include "../BalancaCommon/Temperature/temperature.h"
#include "../BalancaCommon/Weight/weight.h"

#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


void printMenu(void);
unsigned char ReadChar(void);
void print_Value(void);

#define SYSCLK  80000000L // System clock frequency, in Hz
#define PBCLOCK 40000000L // Peripheral Bus Clock frequency, in Hz


static uint16_t ticks;
uint8_t counter_timer4;
uint16_t counter_timer2;
uint8_t imprimiu_menu = 0;
uint32_t peso = 0;
float altura = 0;
float altura_US = 2;
uint32_t time = 0;
uint32_t tension = 0;
uint32_t c = 0;
uint32_t count=0;
uint32_t sum = 0;
float distancia;
uint32_t avg = 0;
//uint64_t IMC;

void EnableInterrupts() {
    asm volatile("ei");
}

void __ISR(_TIMER_2_VECTOR,IPL7AUTO) Timer2_Handler(void)
{
    counter_timer4 = 0;
 
    T3CONbits.TON = 0;  // disable timer 3
    T4CONbits.TON = 1;	// enable timer 4

    IFS0bits.T2IF = 0; // timer flag reset
}

void __ISR(_TIMER_3_VECTOR,IPL5AUTO) Timer3_Handler(void)
{
    ticks = ticks +1;
    
    if(ticks >= 12)
    {
        
        AD1CON1bits.ASAM = 1; // Start conversion
        while (IFS1bits.AD1IF == 0); // Wait for EOC

        tension = (ADC1BUF2*3300)/1023;
        //printf("Value: %d\n",tension);

        if(tension >= 600)
        {
            //c = (20.6 * sqrt(temperature() + 273)*1000);
            time = ticks*50;
            distancia = ((346.3*time)/2)/1000000;
            altura = altura_US - distancia;
            //printf("\n\r Distancia: %dmm",distancia);
        }
        IFS1bits.AD1IF = 0; // Reset interrupt flag
    }       
    IFS0bits.T3IF = 0; // timer flag reset
}

void __ISR(_TIMER_4_VECTOR,IPL5AUTO) Timer4_Handler(void)
{
    counter_timer4 ++;
    
    PORTGbits.RG14 = ~PORTGbits.RG14;
    
    //printf("OK\n");
    if(counter_timer4 >= 40)
    {
        PORTGbits.RG14 = 0;
        T4CONbits.TON = 0;	// disable timer 4
        ticks = 0;
        T3CONbits.TON = 1;  // enable timer 3
    }
    IFS0bits.T4IF = 0; // timer flag reset
}

void init()
{
    INTCONSET = _INTCON_MVEC_MASK;
    
    config_adc();

    // Init UART and redirect tdin/stdot/stderr to UART
    if(UartInit(PBCLOCK, 115200) != UART_SUCCESS) 
    {
        PORTAbits.RA3 = 1; // If Led active error initializing UART
        while(1);
    }
    __XC_UART = 1; //Init UART and Redirect stdint/stdot/stderr to UART
}  


int main(void)
{     
    INTCONSET = _INTCON_MVEC_MASK;

    // ------------------------
    // Configuration of I/O
    // ------------------------
    TRISAbits.TRISA3 = 0; // A3 as output
    TRISGbits.TRISG14 = 0; // A3 as output
    TRISBbits.TRISB5 = 0; // A3 as output
    
    // ------------------------
    // Configuration ADC
    // ------------------------    
    config_adc();

    // ------------------------
    // Configuration of TIMER2
    // ------------------------
	T2CONbits.TON = 0;		//disable timer
    IFS0bits.T2IF = 0;
    IPC2bits.T2IP = 7;
    IEC0bits.T2IE = 1;
	T2CONbits.TCKPS = PRESCALER2; 
	PR2 = 24999;
	TMR2 = 0;				// reset timer2 count register
	T2CONbits.TON = 1;		// enable timer  

    // ------------------------
    // Configuration of TIMER3
    // ------------------------   
	T3CONbits.TON = 0; // stop timer 3
    IFS0bits.T3IF = 0;
    IPC3bits.T3IP = 5; 
    IEC0bits.T3IE = 1;
	T3CONbits.TCKPS = PRESCALER2;
    PR3 = 124;
	TMR3 = 0;				// reset timer2 count register
      
    
    // ------------------------
    // Configuration of TIMER4
    // ------------------------
	T4CONbits.TON = 0;		//disable timer
    IFS0bits.T4IF = 0;
    IPC4bits.T4IP = 5;
    IEC0bits.T4IE = 1;
	T4CONbits.TCKPS = PRESCALER4; 
	PR4 = 124;
	TMR4 = 0;				// reset timer2 count register
    
    
    // ------------------------
    // Configuration UART
    // ------------------------
    if(UartInit(PBCLOCK, 115200) != UART_SUCCESS) 
    {
        PORTAbits.RA3 = 1; // If Led active error initializing UART
        while(1);
    }
    __XC_UART = 1; //Init UART and Redirect stdint/stdot/stderr to UART
    
    
    
    EnableInterrupts();
    printMenu();
    

    while(1)
    {
        print_Value();
    }
}

void printMenu(void)
{
    //Show menu
    printf("\n\n");
    printf("-------------------------------------\n");
    printf("|                MENU                 |\n");
    printf("-------------------------------------\n");
    printf("| 1 : Height\t\t|\n");
    printf("| 2 : Temperature\t|\n");
    printf("| 3 : Weight\t\t|\n");
    printf("| 4 : IMC\t\t\t|\n");
    printf("| 5 : Exit\t\t\t|\n");
    printf("-------------------------------------\n\n\r");
 
}

void print_Value(void)
{
    uint8_t number;
    float IMC;
    
    //IMC = (weight()) /((distancia/10)*(distancia/10));
    number = ReadChar();
    
    if(number == '1')
    {
        printf("Your Height: %.2f m \n\r", altura);
        //printf("\n\r Distancia: %.2fm\n\r",distancia);
    }
    else if(number == '2')
    {
        printf("Current Temperature: %d ºC \n\r", temperature());
    }
    else if(number == '3')
    {
        printf("Your Weight: %.2f Kg\n\r", Cal_Weight());
    }
    else if(number == '4')
    {
        IMC = Cal_Weight() / (altura * altura);
        //printf("%f\n",IMC);
        
        if(IMC >= 13 && IMC < 16)
        {
            printf("Your Height: %.2f m \n\r", altura);
            printf("Your Weight: %.2f Kg\n\r", Cal_Weight());
            printf("IMC Value: %.2f Kg/m^2\n\r", IMC);
            printf("Nutritional Value --> Class III Malnutrition  \n\r");
        }
        if(IMC >= 16 && IMC < 17)
        {
            printf("Your Height: %.2f m \n\r", altura);
            printf("Your Weight: %.2f Kg\n\r", Cal_Weight());
            printf("IMC Value: %.2f Kg/m^2\n\r", IMC);
            printf("Nutritional Value --> Class II Malnutrition  \n\r");
        }
        if(IMC >= 17 && IMC < 18)
        {
            printf("Your Height: %.2f m \n\r", altura);
            printf("Your Weight: %.2f Kg\n\r", Cal_Weight());
            printf("IMC Value: %.2f Kg/m^2\n\r", IMC);
            printf("Nutritional Value --> Class I Malnutrition \n\r");
        }
        if(IMC >= 19 && IMC < 25)
        {
            printf("Your Height: %.2f m \n\r", altura);
            printf("Your Weight: %.2f Kg\n\r", Cal_Weight());
            printf("IMC Value: %.2f Kg/m^2\n\r", IMC);
            printf("Nutritional Value --> Normal \n\r");
        }
        if(IMC >= 25 && IMC < 30)
        {
            printf("Your Height: %.2f m \n\r", altura);
            printf("Your Weight: %.2f Kg\n\r", Cal_Weight());
            printf("IMC Value: %.2f Kg/m^2\n\r", IMC);
            printf("Nutritional Value --> Pre-Obesity \n\r");
        }
        if(IMC >= 30 && IMC < 35)
        {
            printf("Your Height: %.2f m \n\r", altura);
            printf("Your Weight: %.2f Kg\n\r", Cal_Weight());
            printf("IMC Value: %.2f Kg/m^2\n\r", IMC);
            printf("Nutritional Value --> Class I Obesity \n\r");
        }
        if(IMC >= 35 && IMC < 40)
        {
            printf("Your Height: %.2f m \n\r", altura);
            printf("Your Weight: %.2f Kg\n\r", Cal_Weight());
            printf("IMC Value: %.2f Kg/m^2\n\r", IMC);
            printf("Nutritional Value --> Class II Obesity \n\r");
        }
        if(IMC >= 40)
        {
            printf("Your Height: %.2f m \n\r", altura);
            printf("Your Weight: %.2f Kg\n\r", Cal_Weight());
            printf("IMC Value: %.2f Kg/m^2\n\r", IMC);
            printf("Nutritional Value --> Class III Obesity \n\r");
        }
    }
    else if(number == '5')
    {
       printf("Turning off .... \n\r");
       printf("Goodbye\n\r");
       exit; 
    }
}

unsigned char ReadChar(void)
{
    if(U1STAbits.OERR)
    U1STAbits.OERR; // Reset Overrun Eror Flag - if set UART does not receive any chars
    while(!U1STAbits.URXDA); // Wait for char available

    return(U1RXREG); // Return char
}

