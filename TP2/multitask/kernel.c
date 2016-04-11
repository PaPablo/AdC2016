/* 
 * File:   kernel.c
 * Author: GRIFFITHS, Anahí 
 *         SERRUYA ALOISI, Luciano
 *         TOLEDO MARGALEF, Pablo
 * Created on 9 de abril de 2016, 16:09
 */


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
    unsigned int SPLIM;
} resguardo;

resguardo procs[3];

const int MAX_QUANTUM = 3;
extern unsigned int Proc2, Proc3;
unsigned int *puntPila;
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

}

void confReloj(void)
{
    
    T1CON = 0;
    T1CONbits.TCKPS = 1;    //Prescales 1:8
    PR1 = 5000;             //Espera 1000 micro seg
    
    IFS0bits.T1IF = 0;      //Bajamos bandera de interrupcion
    IEC0bits.T1IE = 1;      //habilitamos interrupcion del timer
    
    T1CONbits.TON = 1;       //Ponemos a correr el timer
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
        iProc = 0;      //Cambia el indice de arreglo de los procesos
    }
    else                
    {
        iProc++;        //Pasa del A al B, del B al C, y del C al A
    }
       
}

void __attribute__((interrupt, auto_psv)) _T1Interrupt( void )
{
    IFS0bits.T1IF = 0;
    
   
    
    if (contQuantum >= MAX_QUANTUM)                   
    {  
        contQuantum = 0;
        puntPila = WREG15;
        --puntPila;
        procs[iProc].SPLIM = *puntPila;         //Se hace el respaldo del proceso activo
        puntPila--;
        procs[iProc].PSVPAG = *puntPila;
        puntPila--;
        procs[iProc].W7 = *puntPila;
        puntPila--;
        procs[iProc].W6 = *puntPila;
        puntPila--;
        procs[iProc].W5 = *puntPila;
        puntPila--;
        procs[iProc].W4 = *puntPila;
        puntPila--;
        procs[iProc].W3 = *puntPila;
        puntPila--;
        procs[iProc].W2 = *puntPila;
        puntPila--;
        procs[iProc].W1 = *puntPila;
        puntPila--;
        procs[iProc].W0 = *puntPila;
        puntPila--;
        procs[iProc].RCOUNT = *puntPila;
        puntPila--;
        procs[iProc].IPL = *puntPila;
        puntPila--;
        procs[iProc].dirRetorno = *puntPila;
        puntPila--;
        procs[iProc].var3 = *puntPila;
        puntPila--;
        procs[iProc].var2 = *puntPila;
        puntPila--;
        procs[iProc].var1 = *puntPila;
        
        planificador();
        
        procs[iProc].SPLIM = puntPila;          //Se restaura el contexto del proceso siguiente
        *puntPila = procs[iProc].var1;
        puntPila++;
        *puntPila = procs[iProc].var2;
        puntPila++;
        *puntPila = procs[iProc].var3;
        puntPila++;
        *puntPila = procs[iProc].dirRetorno;
        puntPila++;
        *puntPila = procs[iProc].IPL;
        puntPila++;
        *puntPila = procs[iProc].RCOUNT;
        puntPila++;
        *puntPila = procs[iProc].W0;
        puntPila++;
        *puntPila = procs[iProc].W1;
        puntPila++;
        *puntPila = procs[iProc].W2;
        puntPila++;
        *puntPila = procs[iProc].W3;
        puntPila++;
        *puntPila = procs[iProc].W4;
        puntPila++;
        *puntPila = procs[iProc].W5;
        puntPila++;
        *puntPila = procs[iProc].W6;
        puntPila++;
        *puntPila = procs[iProc].W7;
        puntPila++;
        *puntPila = procs[iProc].PSVPAG;
        puntPila++;
        *puntPila = procs[iProc].SPLIM;
    }
    else
    {
        contQuantum++;
    }    
}
