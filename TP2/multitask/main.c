/* 
Arquitectura de Computadoras 2016
Ejercicio multitasking con interrupciones.
Completar el código faltante.
 */
#include <p33FJ256GP710.h>
#include <stdio.h>
#include <stdlib.h>
#include "kernel.h"

unsigned int Proc2, Proc3;

void procesoA(void)
{
    int x, y, z;
    x = 1;
    y = 1;
    z = 1;

    while(1) {
        
        if (z != 0)
        {
            x = y*z;
        }
        z = x + 1;
    }
}



void procesoB(void)
{
    int a, b, c;
    a = 1;
    b = 1;
    c = 1;

    while(1) {
        
        a = c*b;
        b = c - (2*a);
    }
}

void procesoC(void)
{
    int r, s, t;
    r = 1;
    s = 1;
    t = 1;
    
    while(1) {

        r = s - t;
        s = r + (t*2);
    }
}

int main(int argc, char** argv) {
      
    Proc2 = procesoB; 
    Proc3 = procesoC;   //Se obtiene la direccion de la primer instruccion de cada proceso

    
    boot();
    procesoA();
    return (EXIT_SUCCESS);
}
