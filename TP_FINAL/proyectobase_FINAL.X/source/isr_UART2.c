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
VEHICULOS nuevoVehi;
extern int cont_tmr4;               //Contador del TMR utilizado para calcular la velocidad de un vehiculo

//Interrupciones de la UART2

void __attribute__((interrupt, auto_psv)) _U2RXInterrupt( void )
{
	IFS1bits.U2RXIF = 0;
    LATAbits.LATA0 = 1;
    
    if ( (U2RXREG == (char)SOF) && (recibido[0] != (char)SOF) )
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
        U2TXREG = aEnviar[iTx++];
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
        __builtin_btg((unsigned int *)&LATA, 4);
    }
}


void __attribute__ ((__interrupt__)) _CNInterrupt(void)
{
    
    IFS1bits.CNIF = 0; 
    
    if(PORTDbits.RD13){             //el lazo detecta el vehiculo
        __builtin_btg((unsigned int *)&LATA, 3);
            if(PORTDbits.RD6){          //se pisa el primer piezoelectrico
                __builtin_btg((unsigned int *)&LATA, 2);
                if(!nuevoVehi.ejes){        //si es la primera vez que lo pisa (ruedas delanteras)
                    cont_tmr4 = 0;              //empieza a correr el timer
                    T4CONbits.TON = 1;
                }
                nuevoVehi.ejes++;           //acumula un eje
            }
            else if ((PORTDbits.RD7) && (T4CONbits.TON)){   //el RD7 nos interesa solamente para el calculo de la velocidad
                T4CONbits.TON = 0;
                nuevoVehi.vel = CalcVel(cont_tmr4);
                __builtin_btg((unsigned int *)&LATA, 2);
            }
        }
    else{       //se deja de detectar el vehiculo
        __builtin_btg((unsigned int *)&LATA, 3);
        conseguirTimeStamp(&nuevoVehi.hora);
        chequearVelocidad(nuevoVehi.vel);   //acciona camar si velocidad >60km/h
        logearVehi(nuevoVehi);              //registra vehiculo en el logger
        actualizarInfo(nuevoVehi);          //Se actualiza el LCD
        limpiarRegVehi();                   //Se limpia el registro del vehiculo que paso
    }
        
    

}

    



