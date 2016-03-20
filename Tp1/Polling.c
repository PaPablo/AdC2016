/* 
 * File:   Polling.c
 * Author: GRIFFITHS, Anahí 
 *         SERRUYA ALOISI, Luciano
 *         TOLEDO MARGALEF, Pablo
 *
 * Created on 19 de marzo de 2016, 14:40
 */

#include <stdio.h>
#include <stdlib.h>
#include "p33FJ256GP710.h"



void config (void)
{
    TRISD = 192; //1100 0000
    TRISA = 0;
    PORTA = 0;  //Inicializamos el puerto en cero
}

void inspecciona1 (void)
{
    
    while (PORTDbits.RD6 == 0)
	{
		PORTAbits.RA0 = 1;		//El led se mantendra encendido siempre y cuando se este pulsando el boton
	}
    PORTAbits.RA0 = 0;	//Cuando no se lo este pulsando mas, se apaga

}
void inspecciona2 (void)
{

    
    while (PORTDbits.RD7 == 0)
	{
		PORTAbits.RA1 = 1;	
	}
    PORTAbits.RA1 = 0;
    
}



int main(int argc, char** argv) 
{
    
    config();
    
    while(1)
    {   
        inspecciona1();
        inspecciona2();
    }
    
    return (EXIT_SUCCESS);
}

