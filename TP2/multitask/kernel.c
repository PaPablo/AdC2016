/* 
 * File:   kernel.c
 * Author: GRIFFITHS, Anahí 
 *         SERRUYA ALOISI, Luciano
 *         TOLEDO MARGALEF, Pablo
 * Created on 9 de abril de 2016, 16:09
 */


#include <p33FJ256GP710.h>
#include "kernel.h"



unsigned int procs[3][16]; //3 procedimientos, 16 registros a almacenar

/*0 - 2: variables
 3: dirRetorno
 4: IPL/SR????
 5: RCOUNT
 6 - 13: W0 - W7
 14: PSVPAG
 15: SPLIM*/

const int MAX_QUANTUM = 3;
const int MAX_PILA = 15;
extern unsigned int Proc2, Proc3;
unsigned int *puntPila;
int contQuantum = 0;
int iProc, iReg = 0;

void init(void)
{    
    int i, j;
    for(i = 1; i <= 2; i++){
        for(j = 0; j <= (MAX_PILA); j++){
            if (i == 1){
                if (j == 3){
                    procs[i][j] = Proc2;        //Si el indice esta en la posicion de la direccion de retorno 
                }
                /*else if (j == 4){
                    procs[i][j] = 0x0100;
                }*/
                else{
                    procs[i][j] = 0;
                }
            }
            else{
                if (j == 3){
                    procs[i][j] = Proc3;        //almacenamos la direccion de la primer instruccion de cada proceso
                }
                /*else if(j == 4){
                    procs[i][j] = 0x0100;
                }*/
                else{
                    procs[i][j] = 0;
                }
            }
        }
    }
}

void confReloj(void)
{
    
    T1CON = 0;
    T1CONbits.TCKPS = 1;    //Prescaler 1:8
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
        iReg = MAX_PILA;                                //Empieza en la ultima posicion
        puntPila = WREG15;                              //Conseguimos a lo que apunta W15 y nos paramos en la posicion anterior
        --puntPila;         
        procs[iProc][iReg] = *puntPila;                 //Tiramos el SPLIM a la ultima posicion del arreglo
        --puntPila;
        --iReg;             
        while (puntPila >= procs[iProc][MAX_PILA]){     //Resguardo de contexto
            procs[iProc][iReg] = *puntPila;             
            --puntPila;                                 //Mientras que la direccion a la que apunta puntPila sea mayor o igual al SPLIM
            --iReg;                                     //Hace los resguardos
        }
        planificador();
        puntPila++;
        iReg++;
        if (iProc != 0){                                //Pregunta que proceso hay que recuperar y carga el SPLIM correspondiente
            procs[iProc][MAX_PILA] = procs[iProc - 1][MAX_PILA] ;  
        }
        else{
            procs[iProc][MAX_PILA] = procs[2][MAX_PILA] ;       //EN ESTE CASO ES SIEMPRE EL MISMO
        }
        while(*puntPila != procs[iProc][MAX_PILA]){     //Cargamos los datos del proceso
            *puntPila = procs[iProc][iReg];     
            puntPila++;                                 //Mientras que lo APUTADO por puntPila sea distinto del SPLIM, se cargan los valores
            iReg++;
        }
    }
    else
    {
        contQuantum++;
    }    
}
