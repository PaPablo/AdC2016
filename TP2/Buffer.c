/* 
 * File:   Buffer.c
 * Author: GRIFFITHS, Anahí 
 *         SERRUYA ALOISI, Luciano
 *         TOLEDO MARGALEF, Pablo
 * Created on 2 de abril de 2016, 16:09
 */

#include <stdio.h>
#include <stdlib.h>
#include "p33FJ256GP710.h"

/*
 * 
 * 
 *
 */


int iBuffer = 0; 
typedef struct {

		unsigned int esNuevo:1; //1 bit para la bandera que indica un caracter nuevo en buffer
		unsigned char carac: 8;	// el caracter en esa posicion del buffer
		unsigned : 7;			//resto del campo inaccesible;

	} tBuffer;
    
const int MAXBUFFER = 20;

tBuffer buffer[20];         //tamaï¿½o del buffer
unsigned char tabla[1000];  //Tabla en memoria para tirar valores ingresados por PORTA

void config (void){
    
    int i;
    AD1PCFGL = 0xFFFF;
    AD1PCFGH = 0xFFFF;
    AD2PCFGL = 0xFFFF;
    TRISA = 0X00FF;
    
    
    INTCON2bits.INT0EP = 1; //Configura INT0 para que interrumpa 
                            //en flanco descendente
    
    IFS0bits.INT0IF = 0; 	//INTERRUPT FLAG
    IEC0bits.INT0IE = 1; 	//INTERRUPT ENABLE

    for(i = 0;i < MAXBUFFER ; i++)
    {
        buffer[i].esNuevo = 0;
    }

}

//extern int iBuffer;

void __attribute__((interrupt, auto_psv)) _INT0Interrupt( void ) {

    IFS0bits.INT0IF = 0;    // Bajamos la bandera de interrupciï¿½n
    
    buffer[iBuffer].carac = PORTA;
    buffer[iBuffer].esNuevo = 1;
    
    if(iBuffer == (MAXBUFFER - 1)) {
        iBuffer = 0;        // Pregunta si ya llego a la ultima posicion
    } else {                // del buffer, si llegï¿½ reinicia el indice. 
        iBuffer++;          // En caso contrario incrementa.
    }
    
    
    
    
}


int main(int argc, char** argv) {
    config();
    int j = 0;
    int i;
	while(1){
        
        
        
        for(i = 0; i < MAXBUFFER; i++) {
            if(buffer[i].esNuevo){
                
                tabla[j] = buffer[i].carac;
                buffer[i].esNuevo = 0;
                
                j++;
                
            }
        }  
 

			// recorre el buffer buscando caracteres nuevos
			// en caso de encontrar, los desposita en la tabla
			// en memoria

	}
    return (EXIT_SUCCESS);
}

