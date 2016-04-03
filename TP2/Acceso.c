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
	Configurar el timer
		habilitar
		bajar bandera
		fijar tope   pr = 1000
		prescaler

	main
		iniciar el timer
		polling sobre PORTA
			deposita valores en un arreglo en caso de que sean distintos con respecto al valor anterior
			repite esto hasta que salta el TMR1
		
	Cuando interrumpe
		bajar la bandera
		TMR1 = 0

		si rd14 == 0
			rd15 = 1
			envia por el byte bajo del PORTD
			rd15 = 0
			limpiararreglo
			pr = 1000
						
		si no
			si esta en 1000
				pr = 100
			si esta en 100
				pr = 200
			si esta en 200 
				pr = 400
			si esta en 400
				pr = 800
			si esta en 800
				nada
			fincoso
		finsi
		TMR1 = 0
		TON = 1


*/
typedef struct
{
	unsigned int activo : 1;
	unsigned int valor : 8;
	unsigned int : 7;

} tEntrada;

const int MAXENTRADAS = 100;
const int PRSTD = 5000;     //1000 microseg
const int ESPERA1 = 500;    //100 microseg
const int ESPERA2 = 1000;   //200 microseg
const int ESPERA3 = 2000;   //400 microseg
const int ESPERA4 = 4000;   //800 microseg

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

    TRISA = 0X00FF;	// byte bajo como entrada
	TRISD = 0x4000; //se configura solamente el pin14 como entrada

	T1CON = 0;				// limpio el timer
	T1CONbits.TCKPS = 1;	// prescaler a 1:256
	PR1 = PRSTD;				// 1000 microsegundos

	IFS0bits.T1IF = 0;		// bajo la bandera de interrupción
	IEC0bits.T1IE = 1;		// habilito la interrupción

	T1CONbits.TON = 1;	

	limpiarDatos();
	
}

void __attribute__((interrupt, auto_psv)) _T1Interrupt( void ) {

		int i = 0;

		IFS0bits.T1IF = 0;

		if (PORTDbits.RD14) {
			
			switch (PR1) {
				PRSTD: PR1 = ESPERA1;		// espera igual a 100 microseg
								break;

				ESPERA1: PR1 = ESPERA2;     // espera igual a 200 microseg
								break;

				ESPERA2: PR1 = ESPERA3;     // espera igual a 400 microseg
								break;

				ESPERA3: PR1 = ESPERA4;     // espera igual a 800 microseg
								break;

				// En caso de que ya esté esperando 800 microseg
				// se mantiene en ese tiempo indefinidamente
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
