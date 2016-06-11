#include "p33FJ256GP710.h"

volatile unsigned int temp1;
volatile unsigned char adc_lcd_update;

volatile unsigned char adones;
volatile unsigned char adtens;
volatile unsigned char adhunds;
volatile unsigned char adthous;

int count;
/*---------------------------------------------------------------------
  Function Name: ADCInterrupt
  Description:   ADC Interrupt Handler
  Inputs:        None
  Returns:       None
-----------------------------------------------------------------------*/
void __attribute__((interrupt, auto_psv)) _ADC1Interrupt( void )
{

	/* Se hace para percibir cuando hay muestra nueva */
	if ( count++ == 2000 ) {
		__builtin_btg( (unsigned int *)&LATA, 7 );
		count = 0;
	}
	
	/* Save the RP5 Potentiometer data */
	temp1 = ADC1BUF0;             

	/* set flag to update LCD */
	adc_lcd_update = 1;
	
	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;           
}
  
/*---------------------------------------------------------------------
  Function Name: Init_ADC
  Description:   Initialize ADC module
  Inputs:        None
  Returns:       None
-----------------------------------------------------------------------*/
void Init_ADC( void )
{
	/* set port configuration here */ 		
 	AD1PCFGLbits.PCFG4 = 0;         // ensure AN4/RB4 is analog (Temp Sensor)
 	AD1PCFGLbits.PCFG5 = 0;         // ensure AN5/RB5 is analog (Analog Pot)
 
 	/* set channel scanning here, auto sampling and convert, 
 	   with default read-format mode */
	AD1CON1 = 0x00E4;

	/* select 12-bit, 1 channel ADC operation */
	AD1CON1bits.AD12B = 1;
	
	/* No channel scan for CH0+, Use MUX A,  
	   SMPI = 1 per interrupt, Vref = AVdd/AVss */
	AD1CON2 = 0x0000;
	
	/* Set Samples and bit conversion time */
	AD1CON3 = 0x032F; 
        	
	/* set channel scanning here for AN4 and AN5 */
	AD1CSSL = 0x0000;
	
	/* channel select AN5 */
	AD1CHS0 = 0x0005;
	
	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;           

	/* enable ADC interrupts, disable this interrupt if the DMA is enabled */	  
	IEC0bits.AD1IE = 1;       

	/* turn on ADC module */
	AD1CON1bits.ADON = 1;          	
}

  
/*---------------------------------------------------------------------
  Function Name: advolt
  Description:   Convert Raw ADC data to volts for LCD display
  Inputs:        Raw ADC data 
  Returns:       None
-----------------------------------------------------------------------*/
void advolt( unsigned int adc_conv_data )
{
 adones = 0;					    // reset values
 adtens = 0;
 adhunds = 0;
 adthous = 0;
 
 while ( adc_conv_data > 0 )
 {
  	if( adc_conv_data > 1241 )		//test for 1 volt or greater
	{
		adones++;			        //increment 1 volt counter
		adc_conv_data -= 1242;		//subtract 1 volt
	}
	
	else if( adc_conv_data > 124 )	//test for 0.1 volt	
	{
		if ( adtens < 9 )
		{
		  adtens++;			//increment tenths
		}
		else 
		{
		  adones++;			//tenths has rolled over
		  adtens = 0;		//so increment ones and reset tenths
		}

		adc_conv_data -= 125;        //test for 0.01 volt
	}

	else if( adc_conv_data > 12 )		
	{
		adhunds++;			//increment hundreths
		adc_conv_data -= 13;
	}
 
	else if ( adc_conv_data <= 12 )
	{
		adthous++;
		adc_conv_data --;
	}
 }

	adones += 0x30;				
 	adtens += 0x30;
 	adhunds += 0x30;
	adthous += 0x30;
} 

