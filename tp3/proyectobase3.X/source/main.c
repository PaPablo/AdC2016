/**********************************************************************
 FileName:        main.c
 Dependencies:    p33FJ256GP710.h 
 Processor:       dsPIC33F
 Compiler:        MPLAB® C30 v2.01 or higher

 Ejemplo de funcionamiento de:
 	Timer4
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
 Marcelo Gómez     08/03/14  Portado a MPLAB.X
 Sebastián Wahler  25/04/14  Agregado de ADC
 Sebastián Wahler  19/04/16  Agregado de DMA

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**********************************************************************/

#include "p33FJ256GP710.h"
#include "common.h"
#include "lcd.h"
#include "config.h"
#include <xc.h>
#include "confbits.h"

#define TRUE	1

const char mytext[] =   "TP3      AC 2016";  //Largo 16 chars
const char mytext1[] =  "Pulsar S3       ";
const char time_msg[] = "00:00:00        ";
int CounterTog = 0;

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
			CounterTog= 0;
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
#endif

	/* Espera hasta que el switch S3 es presionado (se haga 1) */
	while ( PORTDbits.RD6 )
		;

#ifdef USAR_LCD
    /* Nuevo mensaje al LCD */
	home_clr();
	puts_lcd( (unsigned char*) &time_msg[0], sizeof(time_msg) -1 );
#endif

    /* Loop infinito */
    while ( TRUE ) 
    { 
	  //Testigo: Toggle LEDs at X rate
	  if (CounterTog > 3)
		{
			/* Actualizar Hora */
			seconds=seconds+1;
			if (seconds > 59)
			{
				seconds=0;
				minutes=minutes+1;
			}
			if (minutes > 59)
			{
				minutes=0;
				hours=hours+1;
			}
			if (hours == 24)
			{
				hours=0;
			}		
			ToggleTest();
#ifdef USAR_LCD
	 		Update_Time();	//Refresco la hora
#endif
		}

#ifdef USAR_LCD
      /* Hay caracteres del ADC para LCD? */
  	  if ( adc_update ) 
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
            adc_update = 0;
	  }
#else
  	  if ( adc_update )
  	  {
              advolt( temp1 );
              adc_update = 0;
          }

#endif // USAR_LCD
	}
}


