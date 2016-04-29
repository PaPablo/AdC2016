#include "p33FJ256GP710.h"
#include "config.h"

#define ValPR3  4999;
#define ValPR4	10000
#define ValPR6	0


volatile unsigned char hours;
volatile unsigned char minutes;
volatile unsigned char seconds;
extern int CounterTog;


/*---------------------------------------------------------------------
  Function Name: Init_Timer3
  Description:   Initialize Timer3
  Inputs:        None
  Returns:       None
-----------------------------------------------------------------------*/
void Init_Timer3( void )
{
    // Trigger ADC1 every 125usec
    PR2 = ValPR3;
    TMR3 = 0x0000;
    // Clear Timer 3 interrupt
    IFS0bits.T3IF = 0;
    // Disable Timer 3 interrupt
    IEC0bits.T3IE = 0;
    //Start Timer 3
    T3CONbits.TON = 1;
}


/*---------------------------------------------------------------------
  Function Name: _T4Interrupt
  Description:   Timer4 Interrupt Handler

Comments:
El Timer 4 se utiliza a la recepción para detección de un intervalo excesivo
entre caracteres entrantes.39062 
-----------------------------------------------------------------------*/
void __attribute__((interrupt, auto_psv)) _T4Interrupt( void )
{
	/* reset Timer 4 interrupt flag */
 	IFS1bits.T4IF = 0;
	//T4CONbits.TON = 0; 	//Deshabilito Timer
	CounterTog ++;

}

/*---------------------------------------------------------------------
  Function Name: Init_Timer4
  Description:   Initialize Timer4
  Inputs:        None
  Returns:       None
-----------------------------------------------------------------------*/
void Init_Timer4( void )
{
	/* ensure Timer 4 is in reset state */
	T4CON = 0;
	T4CONbits.TCKPS = 3; //Prescaler 256

	/* reset Timer 4 interrupt flag */
 	IFS1bits.T4IF = 0;
 	
 	/* set Timer interrupt priority level */
	IPC6bits.T4IP = 5;

	/* enable Timer interrupt */
 	IEC1bits.T4IE = 1;
 	  	
	/* set Timer period register */
	PR4 = ValPR4;
	T4CONbits.TON = 1; 	//habilito Timer

}


/*---------------------------------------------------------------------
  Function Name: _T6Interrupt
  Description:   Timer6 Interrupt Handler

Comments:
El Timer 6 se utiliza para medir el tiempo existente entre la escritura del último caracter
y la salida del STOP bit desde el Shift register.
-----------------------------------------------------------------------*/
void __attribute__((interrupt, auto_psv)) _T6Interrupt( void )
{
	/* reset Timer 6 interrupt flag */
 	IFS2bits.T6IF = 0;
	T6CONbits.TON = 0;	//Deshabilito Timer6

}

/*---------------------------------------------------------------------
  Function Name: Init_Timer6
  Description:   Initialize Timer6
  Inputs:        None
  Returns:       None
-----------------------------------------------------------------------*/
void Init_Timer6( void )
{
	
	/* ensure Timer 6 is in reset state */
	T6CON = 0;
	T6CONbits.TCKPS = 1; //Prescaler 8

	/* reset Timer 6 interrupt flag */
 	IFS2bits.T6IF = 0;
 	
 	/* set Timer interrupt priority level */
	IPC11bits.T6IP = 5;

	/* enable Timer interrupt */
 	IEC2bits.T6IE = 1;
 	  	
	/* set Timer period register */
	PR6 = ValPR6;
	T6CONbits.TON = 1; 	//habilito Timer

}
