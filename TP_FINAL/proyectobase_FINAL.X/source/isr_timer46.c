#include "p33FJ256GP710.h"
#include "config.h"
#include "common.h"


unsigned int cont_tmr4 = 0;

unsigned int seg = 0;

/*---------------------------------------------------------------------
  Function Name: _T4Interrupt
  Description:   Timer4 Interrupt Handler

Comments: 39062
-----------------------------------------------------------------------*/
void __attribute__((interrupt, auto_psv)) _T1Interrupt( void )
{
	/* reset Timer 4 interrupt flag */
 	IFS0bits.T1IF = 0;
	cont_tmr4++;
    
    
}

/*---------------------------------------------------------------------
  Function Name: Init_Timer4
  Description:   Initialize Timer4

-----------------------------------------------------------------------*/
void Init_Timer4( void )
{
	/* ensure Timer 4 is in reset state */
	T1CON = 0;
	T1CONbits.TCKPS = 3; //Prescaler 256

	/* reset Timer 4 interrupt flag */
 	IFS0bits.T1IF = 0;
 	
 	/* set Timer interrupt priority level */
	IPC0bits.T1IP = 5;

	/* enable Timer interrupt */
 	IEC0bits.T1IE = 1;
 	  	
	/* set Timer period register */
	PR1 = ValPR4;
	T1CONbits.TON = 1; 	//habilito Timer

}


/*---------------------------------------------------------------------
  Function Name: _T6Interrupt
  Description:   Timer6 Interrupt Handler

-----------------------------------------------------------------------*/
void __attribute__((interrupt, auto_psv)) _T6Interrupt( void )
{
	/* reset Timer 6 interrupt flag */
 	IFS2bits.T6IF = 0;
    seg++;   

}

/*---------------------------------------------------------------------
  Function Name: Init_Timer6
  Description:   Initialize Timer6

-----------------------------------------------------------------------*/
void Init_Timer6( void )
{
	
	/* ensure Timer 6 is in reset state */
	T6CON = 0;
	T6CONbits.TCKPS = 3; //Prescaler 256

	/* reset Timer 6 interrupt flag */
 	IFS2bits.T6IF = 0;
 	
 	/* set Timer interrupt priority level */
	IPC11bits.T6IP = 6;

	/* enable Timer interrupt */
 	IEC2bits.T6IE = 1;
 	  	
	/* set Timer period register */
	PR6 = ValPR6;
	T6CONbits.TON = 1; 	//habilito Timer

}
