/* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author            Date      Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Ricardo López   11/6/10  UART2C module interrupt handler
* Marcelo Gómez   09/03/14 Portado a MPLAB.X
* Marcelo Gómez   20/05/15 Portado a MPLAB.X
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
*
*
**********************************************************************/

#include "p33FJ256GP710.h"
#include "common.h"
#include "delay.h"

//UART
#define FCY 40000000
#define BAUDRATE 9600
#define BRGVAL ((FCY / BAUDRATE) / 16) -1
#define ESPERA_1BIT (1/BAUDRATE)
#define CANT_BITSxBYTE 10
#define ESPERA_1BYTE ((ESPERA_1BIT) * CANT_BITSxBYTE)


volatile unsigned char qty = 0;
volatile unsigned char cantChar;

volatile unsigned char uart_lcd_update;

int i = 0;

/*---------------------------------------------------------------------
  Function Name: UART2Interrupt
  Description:   UART2 Interrupt Handler
  Inputs:        None
  Returns:       None
-----------------------------------------------------------------------*/
//Interrupciones de la UART2

void __attribute__((interrupt, auto_psv)) _U2RXInterrupt( void )
{
	IFS1bits.U2RXIF = 0;
    
    if (qty == 0){
        qty = U2RXREG;          //Tomamos el primer caracter enviado, 
        cantChar = qty - 1 ;         //que representa la cantidad de caracteres 
    }                           //que se van a enviar, pero a este no lo encadenamos
    else{
        cadena[i++] = U2RXREG;       //encadenamos el caracter recibido
        qty--;                       //y decrementamos la cantidad de caracteres
    }
    if (i == cantChar){             /*Preguntamos si ya termino de encadenar el msj
                                    (ya recibimos todo el marco)*/
        IEC1bits.U2RXIE = 0;        //Desactivamos interrupciones del receptor
        i = 0;
		Delay(6250);        		//Espera de 1 segundo
        IFS1bits.U2TXIF = 1;        //Obligo Tx*/
    }
}
    
	

//Rutina de INT para transmisión (no hace nada)
//envia el caracter recibido y avisa 
//que hay un caracter nuevo para mostrar por lcd
void __attribute__((interrupt, auto_psv)) _U2TXInterrupt(void)
{
    IFS1bits.U2TXIF = 0;
    
    if(cantChar > 0)
    {
        --cantChar;
        U2TXREG = cadena[i++];	//Simple ECO, enviamos el marco recibido
        /*Delay_Us(ESPERA_1BYTE); No se si hace falta,
                                esperar a que se envie un byte
                                para enviar el otro*/
    }
	else{
		uart_lcd_update = 1;	//Recien cuando se envia todo el marco se lo muestra por LCD
		i = 0;
        
	}

}

/*---------------------------------------------------------------------
  Function Name: InitUART2
  Description:   Inicializar UART2
  Inputs:        None
  Returns:       None
-----------------------------------------------------------------------*/
void InitUART2(void)
{
	// The HPC16 board has a DB9 connector wired to UART2, 
	// so we will be configuring this port only
	// configure U2MODE
	U2MODEbits.UARTEN = 0;	// Bit15 TX, RX DISABLED, ENABLE at end of func
	U2MODEbits.RTSMD = 1;	// Bit11 Simplex Mode
    U2MODEbits.STSEL = 0;   //1 bit de stop
    U2MODEbits.PDSEL = 0;   //8 bits de datos, sin paridad
    //8 N 1

	// Load a value into Baud Rate Generator.  Example is for 9600.
	U2BRG = BRGVAL;	// 40Mhz osc, 9600 Baud

	IPC7 = 0x4400;	// Mid Range Interrupt Priority level, no urgent reason

	IFS1bits.U2RXIF = 0;	// Clear the Recieve Interrupt Flag
	IEC1bits.U2RXIE = 1;	// Enable Recieve Interrupts

	U2MODEbits.UARTEN = 1;	// And turn the peripheral on
	U2STAbits.UTXEN = 1;	// Empieza a transmitir. Se dispara el Flag TXIF
    
	U2STAbits.UTXISEL0 = 0;	// Se genera interrupcion del transmisor cuando se serializa 
	U2STAbits.UTXISEL1 = 0;	// y se comienza a enviar un caracter
	U2STAbits.URXISEL = 0;	// Se genera interrupcion del receptor cuando se recibe un caracter
    
	IFS1bits.U2TXIF = 0;	// Clear the Transmit Interrupt Flag
	IEC1bits.U2TXIE = 1;	// Enable Transmit Interrupts
    
    Delay_Us(ESPERA_1BIT);	// Esperamos lo que lleva enviar un byte antes de empezar a transmitir
							// para asegurar que la deteccion del bit de comienzo
}
