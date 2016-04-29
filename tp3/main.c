/* 
 * File:   main.c
 * Author: pablo
 *
 * Created on 29 de abril de 2016, 11:35
 */

#include <stdio.h>
#include <stdlib.h>
#include "p33FJ256GP710.h"

int endSampling = 0;
int countInterrupt = 0;
unsigned int adcValue = 0;
void config(){
    //config del timer1 para int cada 250 ms
    PR1 = 39062;    //interrumpe cada 250ms
    TMR1 = 0;
    
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
       
    T1CONbits.TCKPS = 3; //prescaler 1:256
    T1CONbits.TON = 1;  //encedemos timer 1

    
    
    //configuracion ADC

    AD1CON1 = 0x0000;	// SAMP bit = 0 ends sampling ...
    AD1PCFGL = 0xFFDF;	// RB5 = analog
    AD1CHS0 = 0x0005;	// Connect RB5/AN5 as CH0 input ..
      
    AD1CSSL = 0;
    AD1CON3 = 0x0003;	// Manual Sample, Tad = internal 2 Tcy
    AD1CON2 = 0;
    
    AD1CON1bits.ADON = 1;
}





void __attribute__((interrupt, auto_psv)) _T1Interrupt( void )
{
 	IFS0bits.T1IF = 0;

	countInterrupt++;
    if (countInterrupt == 2){
        
        AD1CON1bits.SAMP = 1;
        
    } else if (countInterrupt > 3){

        AD1CON1bits.SAMP = 0;
       
           
        adcValue = ADC1BUF0;
        countInterrupt = 0;
    }

}
/*
 * 
 */
int main(int argc, char** argv) {
    
    config();
    
    while(1);
    
    return (EXIT_SUCCESS);
}

