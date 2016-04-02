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
 */

typedef struct {

		unsigned int esNuevo:1; //1 bit para la bandera que indica un caracter nuevo en buffer
		unsigned char carac: 8;	// el caracter en esa posicion del buffer
		unsigned : 9;			//resto del campo inaccesible;

	} tBuffer;
    
    
int main(int argc, char** argv) {

    return (EXIT_SUCCESS);
}

