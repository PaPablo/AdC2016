/*
 * File:   adcdma.c
 * Author: Administrador
 *
 * Created on 6 de mayo de 2016, 18:42
 */


#include <stdio.h>
#include <stdlib.h>
#include "p33FJ256GP710.h"
#include "common.h"
#include "lcd.h"
#include <xc.h>
#include "confbits.h"
#include "delay.h"



int main(void) {
    
    configADC();    //
    Init_DMA();
    
    
    return 0;
}
