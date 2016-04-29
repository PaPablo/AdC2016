#include "p33FJ256GP710.h"

volatile unsigned int temp1;
volatile unsigned char adc_update;

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
	adc_update = 1;
	
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
        // Data Output Format: Signed Fraction (Q15 format)
        AD1CON1bits.FORM = 3;
        // Sample Clock Source: GP Timer starts conversion
        AD1CON1bits.SSRC = 2;
        // ADC Sample Control: Sampling begins immediately after conversion
        AD1CON1bits.ASAM = 1;
        // 10-bit ADC operation
        AD1CON1bits.AD12B = 0;
        // Samples multiple channels individually in sequence
        AD1CON1bits.SIMSAM = 0;
        AD1CON2bits.BUFM = 0;
        // Scan Input Selections for CH0+ during Sample A bit
        AD1CON2bits.CSCNA = 1;
        // Converts CH0
        AD1CON2bits.CHPS = 0;
        // ADC Clock is derived from Systems Clock
        AD1CON3bits.ADRC = 0;
        // ADC Conversion Clock
        AD1CON3bits.ADCS = 63;
                
        //AD1CHS0: A/D Input Select Register
        // MUXA +ve input selection (AIN0) for CH0
        AD1CHS0bits.CH0SA = 0;
        // MUXA -ve input selection (Vref-) for CH0
        AD1CHS0bits.CH0NA = 0;

        //AD1CHS123: A/D Input Select Register
        // MUXA +ve input selection (AIN0) for CH1
        AD1CHS123bits.CH123SA = 0;
        // MUXA -ve input selection (Vref-) for CH1
        AD1CHS123bits.CH123NA = 0;

        //AD1CSSH/AD1CSSL: A/D Input Scan Selection Register
        AD1CSSH = 0x0000;
        AD1CSSL = 0x000F;       // Scan AIN0, AIN1, AIN2, AIN3 inputs
        // DMA buffers are built in scatter/gather mode
        AD1CON1bits.ADDMABM = 0;
        // 4 ADC buffers
        AD1CON2bits.SMPI = 3;
        // Each buffer contains 8 words
        AD1CON4bits.DMABL = 3;
        // Clear the A/D interrupt flag bit
        IFS0bits.AD1IF = 0;
        // Do Not Enable A/D interrupt
        IEC0bits.AD1IE = 0;
        // Turn on the A/D converter
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

