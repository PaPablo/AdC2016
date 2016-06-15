
/**********************************************************************
 FileName:        main.c
 Dependencies:    p33FJ256GP710.h
 Processor:       dsPIC33F
 Compiler:        MPLAB® C30 v2.01 or higher

 Trabajo Final Arquitectura de Computadoras
 UNPSJB Sede Trelew, 2016

 REVISION HISTORY:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Author            Date      Comments on this revision
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Richard Fischer   07/14/05  Initial Release
 Priyabrata Sinha  01/27/06  Ported to non-prototype devices 
 Ricardo López     05/24/10  Adaptación para uso general
 Sebastián Wahler  08/05/13  Nuevas adaptaciones
 Marcelo Gómez     09/03/14  Portado a MPLAB.X

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**********************************************************************/
#include "common.h"
#include <xc.h>
#include "confbits.h"
#include "p33FJ256GP710.h"
#include "lcd.h"
#include "config.h"
#include "funciones.h"



const char mytext[] =   "TP FINAL AC 2016";  //Largo 16 chars
const char mytext1[] =  "Pulsar S3       ";

extern int paqueteRecibido;         //Bandera para indicar que se completo de recibir un paquete
extern int cont_tmr4;               //Contador del TMR utilizado para calcular la velocidad de un vehiculo
extern char recibido[MAX_RX];       //Arreglo para armar paquete recibido
extern char aEnviar[MAX_TX];        //Arreglo para armar paquete a enviar (respuesta)

int cantVehi = 0;           //Contador de vehiculo
extern unsigned int seg;    //Variable a usar para actualizar reloj

unsigned char linea_1[MAX_LCD] = "21:38:49        ";
unsigned char linea_2[MAX_LCD] = "                ";

VEHICULOS dataLogger[MAX_VEHI];
int iData = 0;                  //indice del dataLogger


void ToggleTest (void)
{
			__builtin_btg((unsigned int *)&LATA, 7);
			__builtin_btg((unsigned int *)&LATA, 6);
			__builtin_btg((unsigned int *)&LATA, 5);
			__builtin_btg((unsigned int *)&LATA, 4);
			__builtin_btg((unsigned int *)&LATA, 3);
			__builtin_btg((unsigned int *)&LATA, 2);	
			__builtin_btg((unsigned int *)&LATA, 1);
			__builtin_btg((unsigned int *)&LATA, 0);
}

int main ( void )
{
    
    int ejes;
    float velocidad;
    HORARIO timeStamp;
    
    unsigned int ultSec = 0;
    
   	config();
    limpiarDataLogger();
    
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

	/* Espera hasta que el switch S3 es presionado (se haga 1) */
	while ( PORTDbits.RD6 )
		;

#ifdef USAR_LCD
	home_clr();
	puts_lcd( (unsigned char*) &linea_1[0], sizeof(linea_1) -1 );
#endif // USAR_LCD

	 /* Loop infinito */
    while ( 1 ) 
    { 
	  if (seg == 4){
          seg = 0;
          actualizoReloj();
          
      }

  	  if( PORTDbits.RD13 ) 
  	  {
        conseguirTimeStamp(&timeStamp);
        cantVehi++;
        while(!PORTDbits.RD6);  //primer sensor
        cont_tmr4 = 0;
        T4CONbits.TON = 1;
        while(!PORTDbits.RD7);  //segundo sensor
        T4CONbits.TON = 0;
      
        velocidad = CalcVel(cont_tmr4);
        //CNEN1bits.
        
        
        
        ejes = 1;
        while(PORTDbits.RD13){  //preguntamos si sigue activo el lazo
            if(PORTDbits.RD6){  //contamos los ejes
                ejes++;
                while(PORTDbits.RD6);   //Esperamos a que pase el eje, para no contar repetidas veces un solo eje
            }
        }
        
        chequearVelocidad(velocidad);                  //acciona camar si velocidad >60km/h
        logearVehi(timeStamp, velocidad, ejes);        //registra vehiculo en el logger
        actualizarInfo(timeStamp, velocidad, ejes);    //actualizar info en LCD

	  }
      if (paqueteRecibido){
        if (paqueteCorrecto(&ultSec)){
          armarRespuesta();
        }
        else{
            envioNACK();              
        }
        paqueteRecibido = 0;
        IEC1bits.U2TXIE = 1;    //Empezamos a transmitir
        IFS1bits.U2TXIF = 1;
              
      } 
      
      
      
	}
}

