/* 
 * File:   ADCPolling.c
 * Author: Luciano
 *
 * Created on 30 de abril de 2016, 12:21
 */

#include <stdio.h>
#include <stdlib.h>
#include "p33FJ256GP710.h"
#include "common.h"
#include "lcd.h"
#include <xc.h>
#include "confbits.h"
#include "delay.h"

#define CON1_AN1 0x0100     //Configura el ADC1 para 10 bits entero signado
#define CON1_AN4 0x0500     //Configura el ADC1 para 12 bits entero signado
#define CON1_AN5 0x0400     //Configura el ADC1 para 12 bits entero no signado
#define CHS0_AN1 0x0001     //Enlaza el CH0 del ADC1 con el AN1
#define CHS0_AN4 0x0004     //Enlaza el CH0 del ADC1 con el AN4
#define CHS0_AN5 0x0005     //Enlaza el CH0 del ADC1 con el AN5
#define CONFIG_PCFGL 0xFFCD
#define CONFIG_TRISD 0x20C0

#define SIGN_MASK_AN1 0x0200 //Mascaras para comprobar si el valor leido por ADC es negativo
#define SIGN_MASK_AN4 0x0800

#define RELLENO_AN1 0xFC00  //Valores para transformar los valores de 10 o 12 bits del ADC a 16 bits 
#define RELLENO_AN4 0xF000 

/*
 * 
 */
void config (void){
    
    AD1PCFGL = CONFIG_PCFGL;
    TRISD = CONFIG_TRISD;
}


void rutinaADC(unsigned int CON, unsigned int CH0){
    unsigned int valorADC;
    char cad[16];
    int i = 0;
    AD1CON1 = CON;
    AD1CHS0 = CH0;
    
    AD1CON1bits.ADON = 1;
    AD1CON1bits.SAMP = 1;
    
    Delay_Us(1000);
    AD1CON1bits.SAMP = 0;
    while(!AD1CON1bits.DONE);
    
    valorADC = ADC1BUF0;
    
    if(CON == CON1_AN1){
        //es 10 bits signado
        //ahora tenemos que convertir ese valor a una cadena
        //y mostrarlo por el lcd
        cad[i++] = 'R';
        cad[i++] = 'D';
        cad[i++] = '6';
        cad[i++] = ':';
        cad[i++] = ' ';
        int asdas = valorADC & SIGN_MASK_AN1;
        if(asdas >= 0x0100){
            //el valor es negativo
            cad[i++] = '-';
            valorADC = valorADC + RELLENO_AN1;
            valorADC = -(valorADC); //COMPLEMENTO A 2
        }
        else{
            cad[i++] = ' ';
            valorADC = valorADC - 0xFE00;
        }
        cad[i++] = (valorADC / 100) + 0x0030;
        cad[i++] = ((valorADC / 10) % 10) + 0x0030;
        cad[i++] = (valorADC % 10) + 0x0030;
    }
    else if (CON == CON1_AN4){
        //es 12 bits signado
        //ahora tenemos que convertir ese valor a una cadena
        //y mostrarlo por el lcd
        cad[i++] = 'R';
        cad[i++] = 'D';
        cad[i++] = '7';
        cad[i++] = ':';
        cad[i++] = ' ';
        if(valorADC & SIGN_MASK_AN4){
            //el valor es negativo
            cad[i++] = '-';
            valorADC = valorADC + RELLENO_AN4;
            valorADC = -(valorADC); //COMPLEMENTO A 2
        }
        else{
            cad[i++] = ' ';
        }
        cad[i++] = (valorADC / 1000) + 0x0030;
        cad[i++] = ((valorADC % 1000) / 100) + 0x0030;
        cad[i++] = ((valorADC % 100) / 10) + 0x0030;
        cad[i++] = (valorADC % 10) + 0x0030;
    }
    else{
        cad[i++] = 'R';
        cad[i++] = 'D';
        cad[i++] = '1';
        cad[i++] = '3';
        cad[i++] = ':';
        cad[i++] = ' ';
        cad[i++] = (valorADC / 1000) + 0x0030;
        cad[i++] = ((valorADC % 1000) / 100) + 0x0030;
        cad[i++] = ((valorADC % 100) / 10) + 0x0030;
        cad[i++] = (valorADC % 10) + 0x0030;
    }
    
    //MOSTRAR EN LED LA CAD
    home_clr();
    puts_lcd( (unsigned char*) &cad[0], sizeof(cad) -1 );
}
int main(int argc, char** argv) {

    config();
    
    while(1){
        if(PORTDbits.RD6){
            rutinaADC(CON1_AN1, CHS0_AN1);
        }
        if(PORTDbits.RD7){
            rutinaADC(CON1_AN4, CHS0_AN4);
        }
        if(PORTDbits.RD13){
            rutinaADC(CON1_AN5, CHS0_AN5);
        }
        
    }
    
    return (EXIT_SUCCESS);
}

