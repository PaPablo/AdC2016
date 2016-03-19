/* 
 * File:   Polling.c
 * Author: Luciano
 *
 * Created on 19 de marzo de 2016, 14:40
 */

#include <stdio.h>
#include <stdlib.h>
#include "p33FJ256GP710.h"

/*
 * 
 */



void config (void)
{
    TRISD = 192; //1100 0000
    TRISA = 0;
    PORTA = 0;  //Inicializamos el puerto en cero
}

void inspecciona1 (void)
{
    
    if (PORTDbits.RD6 == 0) // Pregunta si el botón está pulsado
    {
        while (PORTDbits.RD6 == 0); //Espera hasta que se suelte
        if (PORTAbits.RA0 == 0)
        {
            PORTAbits.RA0 = 1; //Si está apagado lo prende
        }
        else
        {
            PORTAbits.RA0 = 0; //Si está prendido, lo apaga
        }
    }
    

}
void inspecciona2 (void)
{

    
    if (PORTDbits.RD7 == 0)
    {
        while (PORTDbits.RD7 == 0);
        if (PORTAbits.RA1 == 0)
        {
            PORTAbits.RA1 = 1;
        }
        else
        {
            PORTAbits.RA1 = 0;
        }
    }
    
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

