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
#include "config.h"

//UART

int paqueteRecibido;
char recibido[MAX_RX];
char aEnviar[MAX_TX];
#define SOF 0xFE
#define POS_QTY 1

/*---------------------------------------------------------------------
  Function Name: UART2Interrupt
  Description:   UART2 Interrupt Handler
  Inputs:        None
  Returns:       None
-----------------------------------------------------------------------*/

int iRx, iTx;
int qty = 0;

//Interrupciones de la UART2

void __attribute__((interrupt, auto_psv)) _U2RXInterrupt( void )
{
	IFS1bits.U2RXIF = 0;
    
    if ( (U2RXREG == SOF) && (recibido[0] != SOF) )
    {
        iRx = 0;
        recibido[iRx++] = U2RXREG;
        qty = 1; // como para que no entre la primera vez
    }
    else{
        if (recibido[0] == (char)SOF )
        {
            recibido[iRx] = U2RXREG;
            if (iRx == 1)
            {
                qty = U2RXREG - 2; //Ya recibimos el SOF y el Qty
            }
            else
            {
                qty--;
            }
            iRx++;
        }
    }
    
    if (qty == 0)
    {
        IEC1bits.U2TXIE = 0; //cuando se termino de recibir el paquete
                             //la recepcion no interrumpe
        paqueteRecibido = 1;
    }
    
    
}
    
	

//Rutina de INT para transmisión (no hace nada)
//envia el caracter recibido y avisa 
//que hay un caracter nuevo para mostrar por lcd
void __attribute__((interrupt, auto_psv)) _U2TXInterrupt(void)
{
    IFS1bits.U2TXIF = 0;
    if(qty == 0)
    {
        iTx = 0;
        qty = aEnviar[POS_QTY];
    }
    else
    {
        U2TXREG = aEnviar[iTx++];
    }
    
    if (iTx == qty)
    {
        IEC1bits.U2TXIE = 0;
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
