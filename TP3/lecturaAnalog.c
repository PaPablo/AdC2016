/* 
 * File:    lecturaAnalog.c
 * Author:  GRIFFITHS, Anahi
 *          SERRUYA ALOISI, Luciano
 *          TOLEDO MARGALEF, Pablo
 *
 * Created on 29 de abril de 2016, 19:07
 */

#include <stdio.h>
#include <stdlib.h>
#include "p33FJ256GP710.h"
#include "common.h"
#include "lcd.h"
#include <xc.h>
#include "confbits.h"


#define ESPERA 39062       //39062
#define MAX_CARAC 16
int cantInterrpt = 0;
unsigned int valorADC1;

char temp[MAX_CARAC];
char cadena[] = " °C";

void __attribute__((interrupt, auto_psv)) _T1Interrupt( void )
{
	IFS0bits.T1IF = 0;
    cantInterrpt++;
    
    if (cantInterrpt == 3){
        AD1CON1bits.SAMP = 1;
    }
    else if (cantInterrpt == 4){
        AD1CON1bits.SAMP = 0;
        cantInterrpt = 0;
    }
}

void config (void)
{
    AD1PCFGL = 0xFFEF;      //Configuramos el AN5 como entrada analogica
    AD1CSSL = 0;
    AD1CON1 = 0;
    AD1CON2 = 0;
    AD1CON3 = 0;
    AD1CHS0 = 0x0005;
    AD1CON1bits.ADON = 1;
    AD1CON1bits.FORM = 1;
    ADC1BUF0 = 0;
    
    T1CON = 0;				// Ponemos en 0 todo el registro de configuracion y modificamos los que nos interesan	
	T1CONbits.TCKPS = 3;	// prescaler a 1:256
	PR1 = ESPERA;			// 250 milisegundos
	IFS0bits.T1IF = 0;		// bajo la bandera de interrupción
	IEC0bits.T1IE = 1;		// habilito la interrupción

	T1CONbits.TON = 1;
    Init_LCD();
}
/*
 * 
 */

void conversion(void){
    int i = 0;
    int j;
    if(valorADC1 > 99){
        valorADC1 = 99;
    }
    
    temp[i] = (valorADC1 / 10) + 0x30;
    i++;
    temp[i] = (valorADC1 % 10) + 0x30;
    i++;    
    
    for (j = 0; j < 3; j++){
        temp[i] = cadena[j];
        i++;
    }
}
int main(int argc, char** argv) {

    config();
    
    
    while(1){
        while(!AD1CON1bits.DONE);     //espera a que termine de convertir
        AD1CON1bits.DONE = 0;
        valorADC1 = ADC1BUF0;
        conversion();
        home_clr();
        puts_lcd( (unsigned char*) &temp[0], sizeof(temp) -1 );
        
        /*CONVERTIMO Y ENVIAMO AL LCD*/
        
        
        
    }
    return (EXIT_SUCCESS);
}

