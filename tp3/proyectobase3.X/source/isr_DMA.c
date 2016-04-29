#include "p33FJ256GP710.h"

unsigned int DmaBuffer = 0;

struct
{
    unsigned int Adc1Ch0[8];
    unsigned int Adc1Ch1[8];
    unsigned int Adc1Ch2[8];
    unsigned int Adc1Ch3[8];
} BufferA __attribute__((space(dma)));

struct
{
    unsigned int Adc1Ch0[8];
    unsigned int Adc1Ch1[8];
    unsigned int Adc1Ch2[8];
    unsigned int Adc1Ch3[8];
} BufferB __attribute__((space(dma)));;

/*
 * 
 */
void ProcessADCSamples(unsigned int * AdcBuffer)
{

    /* Do something with ADC Samples */

}

/*---------------------------------------------------------------------
  Function Name: DMA0Interrupt
  Description:   DMA0 Interrupt Handler
  Inputs:        None
  Returns:       None
-----------------------------------------------------------------------*/
void __attribute__((interrupt, auto_psv)) _DMA0Interrupt( void )
{

    if(DmaBuffer == 0)
    {
        ProcessADCSamples(BufferA.Adc1Ch0);
        ProcessADCSamples(BufferA.Adc1Ch1);
        ProcessADCSamples(BufferA.Adc1Ch2);
        ProcessADCSamples(BufferA.Adc1Ch3);
    }
    else
    {
        ProcessADCSamples(BufferB.Adc1Ch0);
        ProcessADCSamples(BufferB.Adc1Ch1);
        ProcessADCSamples(BufferB.Adc1Ch2);
        ProcessADCSamples(BufferB.Adc1Ch3);
    }

    DmaBuffer ^= 1;

    IFS0bits.DMA0IF = 0;
}



/*---------------------------------------------------------------------
  Function Name: Init_DMA
  Description:   Initialize DMA module
  Inputs:        None
  Returns:       None
-----------------------------------------------------------------------*/
void Init_DMA( void )
{

    // DMA0 configuration
    // Direction: Read from peripheral address 0-x300 (ADC1BUF0) and write to DMA RAM
    // AMODE: Peripheral Indirect Addressing Mode
    // MODE: Continuous, Ping-Pong Mode
    // IRQ: ADC Interrupt

    // Configure DMA for Peripheral indirect mode
    DMA0CONbits.AMODE = 2;
    // Configure DMA for Continuous Ping-Pong mode
    DMA0CONbits.MODE = 2;
    // Point DMA to ADC1BUF0
    DMA0PAD = (unsigned int)&ADC1BUF0;
    // 32 DMA request (4 buffers, each with 8 words)
    DMA0CNT = 31;
    // Select ADC1 as DMA Request source
    DMA0REQ = 13;

    DMA0STA = __builtin_dmaoffset(&BufferA);
    DMA0STB = __builtin_dmaoffset(&BufferB);

    //Clear the DMA interrupt flag bit
    IFS0bits.DMA0IF = 0;
    //Set the DMA interrupt enable bit
    IEC0bits.DMA0IE = 1;
    // Enable DMA
    DMA0CONbits.CHEN=1;
}
