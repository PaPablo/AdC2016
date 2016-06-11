
/**********************************************************************
 FileName:        main.c
 Dependencies:    p33FJ256GP710.h
 Processor:       dsPIC33F
 Compiler:        MPLAB® C30 v2.01 or higher

 Ejemplo de funcionamiento de:
 	Timer1
 	LCD
 	PORT A Output
 	PORT D Input

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


const char mytext[] =   "TP FINAL AC 2016";  //Largo 16 chars
const char mytext1[] =  "Pulsar S3       ";
const char time_msg[] = "00:00:00        ";
int counterTog = 0;

char cadena[MAX_CHAR];		//Cadena para almacenar el marco recibido

extern int paqueteRecibido;
extern char recibido[MAX_RX];
extern char aEnviar[MAX_TX];

int ejes = 0;
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
			counterTog = 0;
}

int main ( void )
{
   	config();
    
    //config timer 1 y 2
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
	puts_lcd( (unsigned char*) &time_msg[0], sizeof(time_msg) -1 );
#endif // USAR_LCD

	 /* Loop infinito */
    while ( 1 ) 
    { 
	  
     //IMPLEMENTAR ACTUALIZACION DE HORA Y RELOJ
     //DALE IMPLEMENTADOR DALE

  	  if( PORTDbits.RD13 ) 
  	  {
        //conseguirTimeStamp
        while(!PORTDbits.RD6);  //primer sensor
        //prendemo timer
        while(!PORTDbits.RD7);  //segundo sensor
        //apagamo timer
        //calculo velocidad
        ejes++;
        while(PORTDbits.RD13){  //preguntamos si sigue activo el lazo
            if(PORTDbits.RD6){  //contamos los ejes
                ejes++;
            }
        }
        //chequearVelocidad(); //acciona camar si velocidad >60km/h
        //logearVehi();        //registra vehiculo en el logger
        //actualizarInfo();   // actualizar info en LCD

	  }
      if (paqueteRecibido){
        //if (paqueteCorrecto()){
        //      armarRespuesta();
        //      paqueteRecibido = 0;
        //}
        //else{
        //   paqueteNACK();              
        //}
        IEC1bits.U2TXIE = 1;
        IFS1bits.U2TXIF = 1;
              
      }    
	}
}


