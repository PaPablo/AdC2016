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

#define CON1_AN1 0x0100     //Configura el ADC1 para 10 bits entero signado
#define CON1_AN4 0x0500     //Configura el ADC1 para 12 bits entero signado
#define CON1_AN5 0x0400     //Configura el ADC1 para 12 bits entero no signado
#define CHS0_AN1 0x0001     //Enlaza el CH0 del ADC1 con el AN1
#define CHS0_AN4 0x0004     //Enlaza el CH0 del ADC1 con el AN4
#define CHS0_AN5 0x0005     //Enlaza el CH0 del ADC1 con el AN5

/*
 * 
 */
void config (void){
    
    
}
int main(int argc, char** argv) {

    config();
    return (EXIT_SUCCESS);
}

