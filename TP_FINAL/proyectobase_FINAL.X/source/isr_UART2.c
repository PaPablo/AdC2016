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
#include "funciones.h"

//UART

int paqueteRecibido;
char recibido[MAX_RX];
char aEnviar[MAX_TX];


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
        IEC1bits.U2RXIE = 0; //cuando se termino de recibir el paquete
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
        IEC1bits.U2TXIE = 0;    //Cuando termina de enviar el paquete de respuesta
        IEC1bits.U2RXIE = 1;    //volvemos a recibir datos
        limpiarPaquete(recibido, MAX_RX);
    }
}

/*---------------------------------------------------------------------
  Function Name: InitUART2
  Description:   Inicializar UART2
  Inputs:        None
  Returns:       None
-----------------------------------------------------------------------*/



