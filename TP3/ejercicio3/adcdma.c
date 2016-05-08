/*
 * File:   adcdma.c
 * Author: Administrador
 *
 * Created on 6 de mayo de 2016, 18:42
 */


#include <stdio.h>
#include <stdlib.h>
#include "p33FJ256GP710.h"
#include "common.h"
#include "lcd.h"
#include <xc.h>
#include "confbits.h"
#include "delay.h"
#include "confAdcPort.h"
#include "confRutDMA.h"


//cadenas a modo de titulo para el display lcd
char TITULO_RD6[8] = "Promedio";
char TITULO_RD7[5] = "Mayor";
char TITULO_RD13[5] = "Menor";

//cadena para mostrar el resultado de las operaciones de los pulsadores
char aMostrar[4];


/*Rutinas para formateo y mostrar por LCD*/


void encadenar(int nro){
    aMostrar[3] = nro % 10;             //unidad
    aMostrar[2] = ((nro %100) / 10);    //decena
    aMostrar[1] = ((nro / 100) % 10);    //centena
    aMostrar[0] = nro / 1000;           //millar
}


//MOSTRAMOS POR LCD TENIENDO EN CUENTA EL TITULO
void mostrar(char* TITULO, int valor) {
    //mostrar por lcd el titulo de promedio
    home_clr();
    puts_lcd( (unsigned char*) &TITULO[0], sizeof(TITULO) -1 );
    //formateamos cadena con el valor a mostrar
    encadenar(valor);
    //nos posicionamos en la linea 2 del display
    line_2();
    //mostramos por LCD
    puts_lcd( (unsigned char*) &aMostrar[0], sizeof(aMostrar) -1 );
}


int main(void) {
 
    
    //configuracion de ADC, DMA y PORT
    configADC();    
    Init_DMA();
   
    while(1){
        if(PORTDbits.RD6){
            promedioDMA(); //promedio de los valores en buffer de DMA
            mostrar(TITULO_RD6, promedio);  //mostramos titulo y el valor
         
        } else if (PORTDbits.RD7){
            mayorDMA(); //mayor de los valores en buffer DMA
            mostrar(TITULO_RD7, mayor); //mostramos titulo y el valor

        } else if (PORTDbits.RD13) {
            menorDMA(); //menor de los valores en buffer DMA
            mostrar(TITULO_RD13, menor);    //mostramos titulo y el valor
        }
        
        
    }
    
    return 0;
}
