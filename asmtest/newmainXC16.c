/*
 * File:   newmainXC16.c
 * Author: Administrador
 *
 * Created on 6 de abril de 2016, 12:29
 */


#include <stdio.h>
#include <stdlib.h>
#include "p33FJ256GP710.h"

int var = 1;

int var, *varP;

void config(){
	
    T1CON = 0;				// limpio el timer
	T1CONbits.TCKPS = 1;	// prescaler a 1:8
	PR1 = 40;			

	IFS0bits.T1IF = 0;		// bajo la bandera de interrupción
	IEC0bits.T1IE = 1;		// habilito la interrupción

	T1CONbits.TON = 1;		
}

void __attribute__((interrupt, auto_psv)) _T1Interrupt( void ) {
    int i= -2;
    for (i ;i<5;i++)
    __asm("POP w2");
    
    
    i = 5;
    IFS0bits.T1IF = 0;
    while(i++ < 5);
    rutB();
    var = 0;

}

void rutB() {
    int a = 0;
    
    for(a = 0; a <5; a++);
}

void rutA(void){
    int x,y,z;
    x= 1;
    y=1;
    while(1){
      
        z=x+y;
        
    }
 
}
int main(void) {
    config();
    rutA();
    return 0;
}
