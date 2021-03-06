
#include "p33FJ256GP710.h"
#define CONFIG_TRISD 0x20C0


void configADC(void) {
//COMENTARIOS CON L ADELANTE SON DE "LOS HIZO LUCIANO"	
	
	
	
	// ---------- CONFIGURACION ADC ----------
	//seleccionar fuente de comienzo de sampling (comienzo automatico cuando el contador termina los tads)
	
	AD1CON1bits.SSRC = 7;										//L: ESTO ESTA RE BIEN

	//sampleo sumultaneo del canal CH0 y CH1
	AD1CON1bits.SIMSAM = 0;										//L: NO HACE FALTA PERO ESTA BIEN IGUALMENTE

	//Sampleo comienza automaticamente luego de la ultima conversion
	AD1CON1bits.ASAM = 1;										//L: RE BIEN

	//Buffer DMA es escrito en orden de conversión
	AD1CON1bits.ADDMABM = 1; 									//L: MMMMMMMMMMMMMMMMM......................

	//Convierte CH0 (pero al tener el scan lee AN0 y AN1)
	AD1CON2bits.CHPS = 0;										//L: ESTO TAMBIEN

	//comienza a llenar buffer siempre desde el principio
	AD1CON2bits.BUFM = 0;										//L: SI TMABIEN

	// Escanea CH0+ en el los distintos ANx especificados
	AD1CON2bits.CSCNA = 1;										//L: ESTO SI

	// Escanea AN0 Y AN1
	AD1CSSH = 0x0000;
	AD1CSSL = 0x0003; //AN0 y AN1								//L: MUCHO MUY BIEN

	//incrementa el buffer de DMA luego de cada conversion (1 buffer)
	AD1CON2bits.SMPI = 0;										//L: SI TRABAJAMOS CON UN BLOQUE DE MEMORIA DE 1 BUFFER ESTO QUEDA ASI

	//Always uses channel input selects for Sample A
	AD1CON2bits.ALTS = 0;										//L: SI TAMBIEN

	//4 tads de sampleo = 1 microsegundo
	AD1CON3bits.SAMC = 4;			
																/*ESTOS DOS ME PARECE QUE HABRIA QUE DARLE 
																UN POQUITO MAS DE TIEMPO DE SAMPLEO*/
	//(7+1) * TCY = TAD = 0.2 microsegundos
	AD1CON3bits.ADCS = 7;		

	//DONE SE PONEN EN UNO CUANDO TERMINARON TODAS LAS CONVERSIONES DEL ADC (en nuestro caso cuando termina AN0 y AN1)

	//necesitamos 1 buffer de 2 words
	AD1CON4bits.DMABL = 1;										/*L: ESTO ME PARECE QUE TENDRIA QUE ESTAR EN 1 SI VAMOS A TRABAJAR
																CON UN SOLO BLOQUE, DE 1 BUFFER Y 2 WORDS*/
							
    //configuramos PORTD
    //RD6 RD7 RD13 digital input
	TRISD = CONFIG_TRISD;															

	// No queremos que el ADC interrumpa
	// Clear the A/D interrupt flag bit
	IFS0bits.AD1IF = 0;
	// Do Not Enable A/D interrupt
	IEC0bits.AD1IE = 0;
}

//buffer: 1 buffer de 2 words
struct {
	unsigned int Adc1Ch0[2];
} BufferA __attribute__((space(dma)));


void Init_DMA( void )
{
// ---------- CONFIGURACION DMA ----------
    // DMA0 configuration
    // Direction: Read from peripheral address 0-x300 (ADC1BUF0) and write to DMA RAM
    // AMODE: Peripheral Indirect Addressing Mode
    // MODE: Continuous
    // IRQ: ADC Interrupt

    // Configure DMA for Peripheral indirect mode
    DMA0CONbits.AMODE = 2;						
    // Configure DMA for Continuous mode
    DMA0CONbits.MODE = 0;										//L: SI TRABAJMOS CON UN SOLO BLOQUE DE MEMORIA PARA ALMACENAR, ESTO QUEDARIA ASI.
																//L: MODO CONTINUO, PING PONG DESHABILITADO

    // Point DMA to ADC1BUF0
    DMA0PAD = (unsigned int)&ADC1BUF0;
    
    // 2 requerimientos de DMA (1 buffer ; 2 words)
    DMA0CNT = 1;
    // Select ADC1 as DMA Request source
    DMA0REQ = 13;												/*ESTA TODO RE BIEN*/

    //localizo el buffer
    DMA0STA = __builtin_dmaoffset(&BufferA);

    //Clear the DMA interrupt flag bit
    IFS0bits.DMA0IF = 0;

    //Clear the DMA interrupt enable bit
    //No queremos que interrumpa cuando lo complete
    IEC0bits.DMA0IE = 0;
    
    // Enable DMA
    DMA0CONbits.CHEN=1;
}
