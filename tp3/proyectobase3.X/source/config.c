/**********************************************************************
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author            Date      Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Ricardo L�pez     03/11/2011  1ra. versi�n
* Sebasti�n Wahler  08/05/2013  2da. versi�n
* Marcelo G�mez     08/03/2014  Portado a MPLAB.X
* Sebasti�n Wahler  25/04/2014  Agregado de ADC
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
*
**********************************************************************/
#include "p33FJ256GP710.h"
#include "common.h"
#include "lcd.h"
#include "config.h"

void config( void )
{
	//Velocidad del proceso con Xtal de 8 Mhz
 
	/*Set up the oscillator and PLL for 40 MIPS as follows:
	Para Fin = 8MHZ (que trae la placa EXPLORER 16
	Elegimos:
	PLLPRE = N1 = 2, con lo que VCO input= (Fin/N1) = 4 MHZ (ACEPTABLE)
	PLLDIV = M = 40, con lo que VCO output= (VCO in * M) = 160 MHZ (ACEPTABLE)
	PLLPOST = N2 = 2 (valor inferior) Luego,
	                  Fin           M (PLLDIV)         8 MHZ * 40 
	 Fcy = Fosc /2 = ----------  *  --------------- =  ---------- = 40 MIPS
	                 N1(PLLPRE)     2 * N2(PLLPOST)	   2 * 2 * 2
    */
	//Cristal de Fosc = 8 MHZ y FCY = 40 MIPS,	o sea,
	//CLKDIV = 0x0000; //  PLLPOST = N2 = 2 , PLLPRE = N1 = 2
	//PLLFBD = 0x0026; // PLLDIV = M = 40  

	//Manejo del Xtal de la aplicaci�n
	CLKDIV = 0;
	PLLFBD = 38;

#ifdef USAR_LCD

	//En placa Explorer 16 con Xtal f�sico de 8 MHZ
	//se obtiene velocidad de 40 Mhz con PLL
	__builtin_write_OSCCONH(0x03);		/*	Initiate Clock Switch to Primary Oscillator with PLL (NOSC=0b011)*/
	__builtin_write_OSCCONL(0x01);
	while (OSCCONbits.COSC != 0b011);	/*	Wait for Clock switch to occur	*/
	while(!OSCCONbits.LOCK);

#endif

	//Variables
	/* Initialize some general use variables */
	hours, minutes, seconds = 0;

	//Inicializaci�n de PORTS I/O
	/* set LEDs (D3-D10/RA0-RA7) drive state low */
	LATA  = 0xFF00; 
	/* set LED pins (D3-D10/RA0-RA7) as outputs */
	TRISA = 0xFF00; 
	LATA  = 0xFF0E;  //Enciendo los 1,2 y 3 

	/* Initialize ADC  */
	Init_ADC();
        	
	/* Inicializar Timers necesarios */

        //EJEMPLO PARA USO DE DMA
        Init_Timer3();
        
	Init_Timer4();
	//Init_Timer6();

        /* Inicializar DMA*/
        Init_DMA();

#ifdef USAR_LCD
	/* Inicializar LCD Display */
	Init_LCD();
#endif
   	
}

void Init_Capture1(void)
{
    /* Reset IC module */
    IC1CON = 0;

    /* Select Timer2 contents for capture */
    IC1CONbits.ICTMR = 1;

    /* Generate DMA request on every capture event */
    IC1CONbits.ICI = 0;

    /* Capture in every edge */
    IC1CONbits.ICM = 1;

}