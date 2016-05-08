
#include "p33FJ256GP710.h"
#define CONFIG_TRISD 0x20C0


void configADC(void) {
//COMENTARIOS CON L ADELANTE SON DE "LOS HIZO LUCIANO"	
	
	// ---------- CONFIGURACION ADC ----------
	
    //10bits no signado
    AD1CON1bits.AD12B = 0; 
    
    //seleccionar fuente de comienzo de sampling (comienzo automatico cuando el contador termina los tads)
	
	AD1CON1bits.SSRC = 7;

	//sampleo sumultaneo del canal CH0 y CH1
	AD1CON1bits.SIMSAM = 0;	
    
	//Sampleo comienza automaticamente luego de la ultima conversion
	AD1CON1bits.ASAM = 1;

	//Buffer DMA es escrito en orden de conversión
	AD1CON1bits.ADDMABM = 1;

	//Convierte CH0 (pero al tener el scan lee AN0 y AN1)
	AD1CON2bits.CHPS = 0;

	//comienza a llenar buffer siempre desde el principio
	AD1CON2bits.BUFM = 0;

	// Escanea CH0+ en el los distintos ANx especificados
	AD1CON2bits.CSCNA = 1;	

	// Escanea AN0 Y AN1
	AD1CSSH = 0x0000;
	AD1CSSL = 0x0003; //AN0 y AN1

	//incrementa el buffer de DMA luego de cada conversion (1 buffer)
	AD1CON2bits.SMPI = 0;
    
	//Always uses channel input selects for Sample A
	AD1CON2bits.ALTS = 0;

	//4 tads de sampleo = 1 microsegundo
	AD1CON3bits.SAMC = 4;			
																
	//(7+1) * TCY = TAD = 0.2 microsegundos
	AD1CON3bits.ADCS = 7;		

	//DONE SE PONEN EN UNO CUANDO TERMINARON TODAS LAS CONVERSIONES DEL ADC (en nuestro caso cuando termina AN0 y AN1)

	//necesitamos 1 buffer de 2 words
	AD1CON4bits.DMABL = 1;									
							

	// No queremos que el ADC interrumpa
	IFS0bits.AD1IF = 0;
	IEC0bits.AD1IE = 0;
    
    AD1CON1bits.ADON = 1;
}

void confPort(void){
	//configuramos PORTD
    //RD6 RD7 RD13 digital input
	TRISD = CONFIG_TRISD;															

}
