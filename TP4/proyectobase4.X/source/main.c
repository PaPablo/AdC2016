
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


const char mytext[] =   "TP4      AC 2016";  //Largo 16 chars
const char mytext1[] =  "Pulsar S3       ";
const char time_msg[] = "00:00:00        ";
int counterTog = 0;

char cadena[MAX_CHAR];		//Cadena para almacenar el marco recibido


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
	/* Nuevo mensaje al LCD */
	home_clr();
	puts_lcd( (unsigned char*) &time_msg[0], sizeof(time_msg) -1 );
#endif // USAR_LCD

	 /* Loop infinito */
    while ( 1 ) 
    { 
	  //Testigo: Toggle LEDs at X rate
	  if (counterTog)
		{
			ToggleTest();
#ifdef USAR_LCD
		 	Update_Time();	//Refresco la hora
#endif // USAR_LCD
		}
#ifdef USAR_LCD
      /* Hay caracteres del ADC para LCD?
  	  if ( adc_lcd_update ) 
  	  {
       	 //Valores al LCD
		 home_it();
		 advolt( temp1 );
       	 cursor_right();
       	 cursor_right();
       	 cursor_right();  
       	 cursor_right();
       	 cursor_right();
       	 cursor_right();  
       	 cursor_right();
       	 cursor_right();
       	 cursor_right();
       	 cursor_right();
		 lcd_data( adones );
       	 cursor_right();
	  	 lcd_data( adtens );
	  	 lcd_data( adhunds );
	     adc_lcd_update = 0;
        
	  }*/

      /*Hay caracteres de la UART para LCD? */
  	  if ( uart_lcd_update ) 
  	  {
		line_2();
	  	puts_lcd( (unsigned char*) &cadena[0], sizeof(mytext1) -1 ); 
        //Mostramos el marco por LCD
	    uart_lcd_update = 0;
	  }
      
      
      
#endif // USAR_LCD
	}
}


