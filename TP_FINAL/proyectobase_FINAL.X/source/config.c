/**********************************************************************
config.c
**********************************************************************/
#include "p33FJ256GP710.h"
#include "common.h"
#include "lcd.h"
#include "config.h"
#include "delay.h"

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

void Init_CNInterrupt(void){
    CNEN1bits.CN15IE = 1; //CN15 - RD6
    CNEN2bits.CN16IE = 1; //CN16 - RD7
    CNEN2bits.CN19IE = 1; //CN19 - RD13
    IEC1bits.CNIE = 1;
    IFS1bits.CNIF = 0;
}



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

#ifdef USAR_LCD
	//Manejo del Xtal de la aplicación
	CLKDIV = 0;
	PLLFBD = 38;
	
	//En placa Explorer 16 con Xtal físico de 8 MHZ
	//se obtiene velocidad de 40 Mhz con PLL
	__builtin_write_OSCCONH(0x03);		/*	Initiate Clock Switch to Primary Oscillator with PLL (NOSC=0b011)*/
	__builtin_write_OSCCONL(0x01);
	while (OSCCONbits.COSC != 0b011);	/*	Wait for Clock switch to occur	*/
	while(!OSCCONbits.LOCK);
#endif // USAR_LCD
        
	//Variables
	//Initialize some general use variables
	//hours, minutes, seconds = 0;

	//Inicialización de PORTS I/O
	/* set LEDs (D3-D10/RA0-RA7) drive state low */
	//LATA  = 0xFF00; 
	/* set LED pins (D3-D10/RA0-RA7) as outputs */
	TRISA = 0xFF00; 
	//LATA  = 0xFF0E;  //Enciendo los 1,2 y 3 
    LATA = 0;
		
	/* Initialize UART2*/
	InitUART2();

	/* Inicializar Timers necesarios */
	Init_Timer4();
    
    TRISD = 0x20C0;
    //RD6, 7 y 13 como input

#ifdef USAR_LCD
	/* Inicializar LCD Display */
	Init_LCD();
#endif // USAR_LCD
}

