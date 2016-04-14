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

typedef struct
{
	unsigned int activo : 1;
	unsigned int valor : 8;
	unsigned int : 7;

} tEntrada;

const int MAXENTRADAS = 100;

const int PRSTD = 5000;     //1000 microseg
const int ESPERA = 500;    //100 microseg

tEntrada datos[100];

void limpiarDatos() {

	int i;

	for(i = 0; i < MAXENTRADAS; i++) {
		datos[i].activo = 0;
		datos[i].valor = 0;
	}

}
void config(){

    AD1PCFGL = 0xFFFF;
    AD1PCFGH = 0xFFFF;
    AD2PCFGL = 0xFFFF;

    TRISA = 0X00FF;			// byte bajo como entrada
	TRISD = 0x4000; 		// se configura solamente el pin14 como entrada

	T1CON = 0;				// Ponemos en 0 todo el registro de configuracion y modificamos los que nos interesan	
	T1CONbits.TCKPS = 1;	// prescaler a 1:8
	PR1 = PRSTD;			// 1000 microsegundos

	IFS0bits.T1IF = 0;		// bajo la bandera de interrupción
	IEC0bits.T1IE = 1;		// habilito la interrupción

	T1CONbits.TON = 1;	

	limpiarDatos();
	
}

void __attribute__((interrupt, auto_psv)) _T1Interrupt( void ) {

		int i = 0;

		IFS0bits.T1IF = 0;

		if (PORTDbits.RD14) {
           
            if (PR1 == PRSTD) {
                PR1 = ESPERA;						// Se configura el PR para que el TMR1 interrumpa a los 100 microsegundos
            } else {
                if (PR1 == ESPERA){
                    PR1 = (ESPERA * 2); 			// 200 microsegundos
                } else {
                    if (PR1 == (ESPERA * 2)){
                        PR1 = (ESPERA * 4);			// 400 microsegundos
                    } else {
                        if (PR1 == (ESPERA * 4)){
                            PR1 = (ESPERA * 8);		// 800 microsegundos
                        }
                    }
                }
            }
            
		} else {

			PORTDbits.RD15 = 1;

			while (datos[i].activo) {		// Envía datos mientras haya "activos"
				PORTD = datos[i].valor;
				i++;
			}

			PORTDbits.RD15 = 0;	

			limpiarDatos();

			PR1 = PRSTD;

		}

}

int main(int argc, char** argv) {

	int i = 0;
	config();

	datos[i].valor = PORTA;
	datos[i].activo = 1;

	while(1) {

		if(datos[i].valor != PORTA) {	// si el valor en el puerto es distinto al ultimo almacenado
			i++;						// se guarda en el arreglo
			datos[i].valor = PORTA;
			datos[i].activo = 1;

		}

	}
    return (EXIT_SUCCESS);
}
