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

/*Variables globales*/

int encendido1 = 0;
int encendido2 = 0;
int anterior1 = 1;
int actual1 = 1;
int anterior2 = 1;
int actual2 = 1;
int hayCambio1 = 1;
int hayCambio2 = 1;


void config (void)
{
    TRISD = 192; //1100 0000
    TRISA = 0;
    PORTA = 0;  //Inicializamos el puerto en cero
}

void inspecciona1 (void)
{
	actual1 = PORTDbits.RD6;
	hayCambio1 = anterior1 ^ actual1;
		
		
	if (hayCambio1) 
	{
		encendido1 = encendido1 ^ hayCambio1;
		PORTAbits.RA0 = encendido1;
	}
	
	anterior1 = actual1;
}
void inspecciona2 (void)
{
	actual2 = PORTDbits.RD7;
	hayCambio2 = anterior2 ^ actual2;
		
		
	if (hayCambio2) 
	{
		encendido2 = encendido2 ^ hayCambio2;
		PORTAbits.RA1 = encendido2;
	}
	
	anterior2 = actual2;
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

