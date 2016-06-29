
/**********************************************************************
 FileName:        main.c
 Dependencies:    p33FJ256GP710.h
 Processor:       dsPIC33F
 Compiler:        MPLAB® C30 v2.01 or higher

 Trabajo Final Arquitectura de Computadoras
 UNPSJB Sede Trelew, 2016

**********************************************************************/
#include "common.h"
#include <xc.h>
#include "confbits.h"
#include "p33FJ256GP710.h"
#include "lcd.h"
#include "config.h"
#include "funciones.h"
#include "delay.h"



const char mytext[] =   "TP FINAL AC 2016";  //Largo 16 chars
const char mytext1[] =  "Pulsar S3       ";

extern int paqueteRecibido;         //Bandera para indicar que se completo de recibir un paquete
extern tipoPaquete recibido[MAX_RX];       //Arreglo para armar paquete recibido
extern tipoPaquete aEnviar[MAX_TX];        //Arreglo para armar paquete a enviar (respuesta)


int cantVehi = 0;           //Contador de vehiculo
extern unsigned int seg;    //Variable a usar para actualizar reloj

unsigned char linea_1[MAX_LCD] = "18:36:00        ";
unsigned char linea_2[MAX_LCD] = "                ";

VEHICULOS dataLogger[MAX_VEHI];
int iData = 0;                  //indice del dataLogger




int main ( void )
{
    
    limpiarRegVehi();
    limpiarPaquete(recibido, MAX_RX);
    limpiarDataLogger();
   
   	config();
    unsigned int ultSec = SEC1;
    
    //config timer 4 y 6
    //UART 9600 8n1
    //PORTD RD6, RD7 (piezoelectricos)
    //PORTD RD13 (lazo inductivo)
    //PORTA RA0 (camara)

#ifdef USAR_LCD
	/* Mensaje Inicial */
	home_clr();
	puts_lcd( (unsigned char*) &mytext[0], sizeof(mytext) -1 );
	line_2();
	puts_lcd( (unsigned char*) &mytext1[0], sizeof(mytext1) -1 );
#endif // USAR_LCD

	while ( PORTDbits.RD6 );
    
    Init_Timer6();
    
    /* Inicializar Change Notification*/
    Init_CNInterrupt();
#ifdef USAR_LCD
	home_clr();
	puts_lcd( (unsigned char*) &linea_1[0], sizeof(linea_1) -1 );
#endif // USAR_LCD
    
    
	 /* Loop infinito */
    while ( 1 ) 
    {    
      if (paqueteRecibido){
        __builtin_btg((unsigned int *)&LATA, 0);
        __builtin_btg((unsigned int *)&LATA, 7);
        if (paqueteCorrecto(&ultSec)){
            armarRespuesta();
            __builtin_btg((unsigned int *)&LATA, 6);
        }
        else{
            envioNACK();              
        }
        paqueteRecibido = 0;
        IEC1bits.U2TXIE = 1;    //Empezamos a transmitir
        __builtin_btg((unsigned int *)&LATA, 5);
        IFS1bits.U2TXIF = 1;
              
      } 
      
      
      
	}
}

