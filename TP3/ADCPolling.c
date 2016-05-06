/* 
 * File:   ADCPolling.c
 * Author: Luciano
 *
 * Created on 30 de abril de 2016, 12:21
 */

#include <stdio.h>
#include <math.h>
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

#define SIGN_MASK_AN1 0x0400 //Mascaras para comprobar si el valor leido por ADC es negativo
#define SIGN_MASK_AN4 0x1000

#define RELLENO_AN1 0xFC00  //Valores para transformar los valores de 10 o 12 bits del ADC a 16 bits 
#define RELLENO_AN4 0xF000 

#define RESTA_AN1 0xFE00	//Valores para obtener el valor original que se ingreso
#define RESTA_AN2 0xF800

#define OFFSET_CARAC 0x0030 //Valor a sumar para conseguir el caracter correspondiente a un valor 0-9

typedef void (*FUNCION_PULSADOR)(unsigned int, char*, int);


void config (void){
    
    AD1PCFGL = CONFIG_PCFGL;
    TRISD = CONFIG_TRISD;
}

int digitos(unsigned int num){
/*Cuenta cuantos digitos tiene un numero*/
	
	int contador=1;
    while(num/10>0)
    {
        num=num/10;
        contador++;
    }
	return contador;
}


void EntACad (unsigned int num, char* cad, int cant, int i){
	
	cant--;
    int x;
	
	while (cant >= 0){
        x = pow(10, cant);
		cad[i++] = (num / x) + OFFSET_CARAC;
        num = num % x;
        cant--;
		
	}

}






void Pulsador_RD6(unsigned int valor, char* cad, int i){
    
	//es 10 bits signado
	//ahora tenemos que convertir ese valor a una cadena
	//y mostrarlo por el lcd
	cad[i++] = 'R';
	cad[i++] = 'D';
	cad[i++] = '6';
	cad[i++] = ':';
	cad[i++] = ' ';
	if(!(valor & SIGN_MASK_AN1)){
		//el valor es negativo
		cad[i++] = '-';
		valor = valor + RELLENO_AN1;
		valor = -(valor); //COMPLEMENTO A 2
	}
	else{
		cad[i++] = ' ';
		valor = valor - RESTA_AN1; 
	}
	
	EntACad (valor, cad, digitos(valor), i);
	/*cad[i++] = (valor / 100) + OFFSET_CARAC;
	cad[i++] = ((valor / 10) % 10) + OFFSET_CARAC;
	cad[i++] = (valor % 10) + OFFSET_CARAC;*/ 

}

void Pulsador_RD7 (unsigned int valor, char* cad, int i){

	//es 12 bits signado
	//ahora tenemos que convertir ese valor a una cadena
	//y mostrarlo por el lcd
	cad[i++] = 'R';
	cad[i++] = 'D';
	cad[i++] = '7';
	cad[i++] = ':';
	cad[i++] = ' ';
	if(!(valor & SIGN_MASK_AN4)){
		//el valor es negativo
		cad[i++] = '-';
		valor = valor + RELLENO_AN4;
		valor = -(valor); //COMPLEMENTO A 2
	}
	else{
		cad[i++] = ' ';
		valor = valor - RESTA_AN2; 
	}
    EntACad (valor, cad, digitos(valor), i);
	/*cad[i++] = (valor / 1000) + OFFSET_CARAC;
	cad[i++] = ((valor % 1000) / 100) + OFFSET_CARAC;
	cad[i++] = ((valor % 100) / 10) + OFFSET_CARAC;
	cad[i++] = (valor % 10) + OFFSET_CARAC;*/
    
}

void Pulsador_RD13(unsigned int valor, char* cad, int i){

	//12 bits no signado
	cad[i++] = 'R';
	cad[i++] = 'D';
	cad[i++] = '1';
	cad[i++] = '3';
	cad[i++] = ':';
	cad[i++] = ' ';
    
    EntACad (valor, cad, digitos(valor), i);
	
    /*cad[i++] = (valor / 1000) + OFFSET_CARAC;
	cad[i++] = ((valor % 1000) / 100) + OFFSET_CARAC;
	cad[i++] = ((valor % 100) / 10) + OFFSET_CARAC;
	cad[i++] = (valor % 10) + OFFSET_CARAC;*/
    
	
}


void rutinaADC(unsigned int CON, unsigned int CH0, FUNCION_PULSADOR pulsador){
	
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
	
	pulsador(valorADC, cad, i);	//Ejecutamos la funcion que se paso por parametro en el main
    
    
    
    //MOSTRAR EN LED LA CAD
    home_clr();
    puts_lcd( (unsigned char*) &cad[0], sizeof(cad) -1 );
}
int main(int argc, char** argv) {

    config();
    
    FUNCION_PULSADOR pulsador6, pulsador7, pulsador13;
    pulsador6 = Pulsador_RD6;
    pulsador7 = Pulsador_RD7;
    pulsador13 = Pulsador_RD13;
    
    while(1){
        if(PORTDbits.RD6){
            rutinaADC(CON1_AN1, CHS0_AN1, pulsador6);
        }
        if(PORTDbits.RD7){
            rutinaADC(CON1_AN4, CHS0_AN4, pulsador7);
        }
        if(PORTDbits.RD13){
            rutinaADC(CON1_AN5, CHS0_AN5, pulsador13);
        }
        
    }

    
    return (EXIT_SUCCESS);
}

