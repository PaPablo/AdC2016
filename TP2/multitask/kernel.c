#include <p33FJ256GP710.h>
#include "kernel.h"

typedef struct {
	unsigned int var1;
	unsigned int var2;
	unsigned int var3;
    unsigned int dirRetorno;
    unsigned int IPL;
    unsigned int RCOUNT;
    unsigned int W0;
    unsigned int W1;
    unsigned int W2;
    unsigned int W3;
    unsigned int W4;
    unsigned int W5;
    unsigned int W6;
    unsigned int W7;
    unsigned int PSVPAG;
    unsigned int SPLIM; //WREG15 - 0X20 en este caso, puede variar si cambiamos el nro de variables
} resguardo;

resguardo procs[3];


extern unsigned int Proc1, Proc2, Proc3, *Actual;
unsigned int *gilada;
int contQuantum = 0;
int iProc = 0;

void init(void)
{    
    int i;
    for(i = 1; i <= 2; i++){
        if (i == 1){
            procs[i].dirRetorno = Proc2;
        }
        else{
            procs[i].dirRetorno = Proc3;
        }
        procs[i].W0 = 0;
        procs[i].W1 = 0;
        procs[i].W2 = 0;
        procs[i].W3 = 0;
        procs[i].W4 = 0;
        procs[i].W5 = 0;
        procs[i].W6 = 0;
        procs[i].W7 = 0;
        procs[i].RCOUNT = 0;
        procs[i].IPL = 0x0100;
        procs[i].PSVPAG = 0;
    }

	//fijar direcciones de retorno a interrupciones, en la primera vez ? ponele
}

void confReloj(void)
{
    
    T1CON = 0;
    T1CONbits.TCKPS = 1; //Prescales 1:1
    PR1 = 100; // 
    
    IFS0bits.T1IF = 0; //Bajamos bandera de interrupcion
    IEC0bits.T1IE = 1; //habilitamos interrupcion del timer
    
    T1CONbits.TON = 1; //Ponemos a correr el timer
/*
* 	Configurar Timer (ya sabemos duh...)
*	Configurar el Quantum
*/	
}

void boot(void)
{
    init();
    confReloj();
    return;
}

void planificador(void)
{
    if (iProc == 2){
        iProc = 0;
    }
    else
    {
        iProc++;
    }
        
        /*
*	Cuando lo invoca
*
*		Poder referenciar o llamar a un value
*		
*		segun el value
*			resguardarEstadoActual
*			recuperarEstadoProceso
*			procesoA
*			
*			resguardarEstadoActual
*			recuperarEstadoProceso
*			procesoB
*			
*			resguardarEstadoActual
*			recuperarEstadoProceso
*			procesoC
*
*/

}

void __attribute__((interrupt, auto_psv)) _T1Interrupt( void )
{
    IFS0bits.T1IF = 0;
    
   
    
    if (contQuantum >= 1)
    {  
        contQuantum = 0;
        gilada = WREG15;
        --gilada;
        procs[iProc].SPLIM = *gilada;
        gilada--;
        procs[iProc].PSVPAG = *gilada;
        gilada--;
        procs[iProc].W7 = *gilada;
        gilada--;
        procs[iProc].W6 = *gilada;
        gilada--;
        procs[iProc].W5 = *gilada;
        gilada--;
        procs[iProc].W4 = *gilada;
        gilada--;
        procs[iProc].W3 = *gilada;
        gilada--;
        procs[iProc].W2 = *gilada;
        gilada--;
        procs[iProc].W1 = *gilada;
        gilada--;
        procs[iProc].W0 = *gilada;
        gilada--;
        procs[iProc].RCOUNT = *gilada;
        gilada--;
        procs[iProc].IPL = *gilada;
        gilada--;
        procs[iProc].dirRetorno = *gilada;
        gilada--;
        procs[iProc].var3 = *gilada;
        gilada--;
        procs[iProc].var2 = *gilada;
        gilada--;
        procs[iProc].var1 = *gilada;
        
        planificador();
        
        procs[iProc].SPLIM = gilada;
        *gilada = procs[iProc].var1;
        gilada++;
        *gilada = procs[iProc].var2;
        gilada++;
        *gilada = procs[iProc].var3;
        gilada++;
        *gilada = procs[iProc].dirRetorno;
        gilada++;
        *gilada = procs[iProc].IPL;
        gilada++;
        *gilada = procs[iProc].RCOUNT;
        gilada++;
        *gilada = procs[iProc].W0;
        gilada++;
        *gilada = procs[iProc].W1;
        gilada++;
        *gilada = procs[iProc].W2;
        gilada++;
        *gilada = procs[iProc].W3;
        gilada++;
        *gilada = procs[iProc].W4;
        gilada++;
        *gilada = procs[iProc].W5;
        gilada++;
        *gilada = procs[iProc].W6;
        gilada++;
        *gilada = procs[iProc].W7;
        gilada++;
        *gilada = procs[iProc].PSVPAG;
        gilada++;
        *gilada = procs[iProc].SPLIM;
    }
    else
    {
        contQuantum++;
    }    
    /*
	*	Contar interrupciones
	
	*	llamar planificador si es necesario
    */

}


/*
	EN ASM?
		keonda?
		- almacenar las variables locales de cada proceso en estruct
		- switch

		- handle para la direccion para ir a la rutina



*/