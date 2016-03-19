/* 
 * File:   Automatismo.c
 * Author: GRIFFITHS, Anahí 
 *         SERRUYA ALOISI, Luciano
 *         TOLEDO MARGALEF, Pablo
 *
 * Created on 19 de marzo de 2016, 18:53
 */

#include <stdio.h>
#include <stdlib.h>
#include "p33FJ256GP710.h"


int humedad, temp, cist, elec = 0;
const int MIN_HUM = 19660; //30% de 65535 (0xFFFF)


void config(void)
{
    TRISD = 0xFFFF; // El puerto D se configura para que sean todos los bits de entrada 
    TRISA = 0x063C; // Los dos primeros pines se configuran para salida
                    // y los pines 2, 3, 4, 5, 9 y 10 como entrada.
}

void espera(int tiempo)
{
    int i = 0;
    for (i; i <= tiempo; i++);        
}

int obtieneTemp(void)
{
    if ((PORTAbits.RA2 + PORTAbits.RA3 + PORTAbits.RA4 + PORTAbits.RA5) >= 2)
    {
        return 1; //Devuelve el valor 1 si por lo menos dos de los 
                  //sensores están en ON
    }
    else
    {
        return 0;
    }
}
void entrada(void)
{
    humedad = PORTD;
    temp = obtieneTemp();
    cist = PORTAbits.RA10;
    elec = PORTAbits.RA9;    

}

int logica(void)
{
    if ((humedad < MIN_HUM) && (temp) && (cist) && (elec))
    {
        return 1; //Devuelve 1 si se cumplen las cuatro condiciones
    }
    else
    {
        return 0;
    }
}

void actualizarSalidas(int ok)
{
    if (ok)
    {
        PORTAbits.RA0 = 1; //pin de la válvula
        espera(10000);
        //Se realiza una espera teniendo en cuenta
        //el mecanismo de riego
        PORTAbits.RA1 = 1; //pin de la bomba
    }
    else
    {
        PORTAbits.RA1 = 0;
        espera(10000);
        PORTAbits.RA0 = 0;
    }
    
    
}

int main(int argc, char** argv) {
    
    int hayCambio = 0;
    int encendido = 0;
    
    config();
    
    while(1)
    {
        entrada();
        hayCambio = hayCambio ^ logica();
        //hayCambio tendrá un 1 si se produce un cambio
        //frente al estado anterior
        
        
        encendido = encendido ^ hayCambio;
        //En el caso de que haya cambio pero ya esté encendido el sistema,
        //se deberá apagar
        
        if (hayCambio)
        {
            actualizarSalidas(encendido);
        }
    }
    
    return (EXIT_SUCCESS);
}

