#include "p33FJ256GP710.h"

//buffer: 1 buffer de 2 words
struct {
	unsigned int Adc1Ch0[2];
} BufferA __attribute__((space(dma), aligned(4)));


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
    // Configure DMA for Continuous mode, Ping Pong disabled
    DMA0CONbits.MODE = 0;	
    
    //Se lee del periferico y se tira en memoria
    DMA0CONbits.DIR = 0;

    // Point DMA to ADC1BUF0
    DMA0PAD = (unsigned int)&ADC1BUF0;
    
    // 2 requerimientos de DMA (1 buffer ; 2 words)
    DMA0CNT = 1;
    // Select ADC1 as DMA Request source
    DMA0REQ = 13;											

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

//variables para los valores en DMA
unsigned int promedio;
unsigned int mayor;
unsigned int menor;

/*Rutinas para recolección de valores*/

void promedioDMA(){
    //recoger el promedio del buffer DMA
    int i, sum;
    for (i = 0 ; i < 2 ; i++){
        sum = sum + BufferA.Adc1Ch0[i];
    }
    promedio = sum / 2;
    
}

void mayorDMA(){
    //recoger el mayor del buffer DMA
    int i = 1;
    mayor = BufferA.Adc1Ch0[0];

    while (i < 2) {
        if(mayor < BufferA.Adc1Ch0[i]){
            mayor = BufferA.Adc1Ch0[i];
        }
		i++;
    }

}

void menorDMA(){
    //recoger el menor del buffer DMA
    int i = 1;
    menor = BufferA.Adc1Ch0[0];

     while (i < 2) {
        if(menor > BufferA.Adc1Ch0[i]){
            menor = BufferA.Adc1Ch0[i];
        }
		i++;
    }
}