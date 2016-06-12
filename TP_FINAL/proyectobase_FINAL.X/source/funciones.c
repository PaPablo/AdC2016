#include "common.h"
#include "delay.h"
#include "lcd.h"
#include "p33FJ256GP710.h"
extern char recibido[MAX_RX];
extern char aEnviar[MAX_TX];

extern unsigned char linea_1[MAX_LCD];
extern unsigned char linea_2[MAX_LCD];

extern VEHICULOS dataLogger[];
extern int iData;
extern int cantVehi;





int obtenerVehisGrades(void){
    int i = 0;
    int acum = 0;
    while(dataLogger[i++].ejes > 0){      //recorremos el listado (si la cant ejes es cero es porque no hay vehi registrado)
        if (dataLogger[i].ejes > 2){    
            acum++;
        }
    }
    return acum;
}



int hayVehiculos(char hora, int* pos){
    int i = 0;
    int salgo = 0;
    char horaReg;
    while((dataLogger[i++].ejes > 0) && (salgo == 0)){
        horaReg = (dataLogger[i].hora.h);
        if (horaReg == hora){
            salgo = 1;
            *pos = i;
        }
    }
    return (salgo == 1);        //Si se cumple la condicion, es porque hay almenos un vehiculo
                                //registrado que paso a la hora recibida.
}


void listarVehiculos(int hora, int pos, int* i){
    int salgo = 0;
    char horaReg;
    while(!salgo){
        horaReg = (dataLogger[pos].hora.h);
        if (horaReg == hora){
            aEnviar[*i++] = horaReg;                   //Hora
            aEnviar[*i++] = (dataLogger[pos].hora.m);  //Minutos
            aEnviar[*i++] = (dataLogger[pos].hora.s);  //Segundos
            aEnviar[*i++] = dataLogger[pos].vel;
            aEnviar[*i] = dataLogger[pos].ejes;
        }
        else{
            salgo = 1;
        }
        pos++;
    }
}




void PaqueteA(void){
    aEnviar[0] = SOF;
    aEnviar[1] = 8;
    aEnviar[2] = recibido[POS_SRC];
    aEnviar[3] = DST;
    aEnviar[4] = recibido[POS_SEC];
    aEnviar[5] = recibido[POS_CMD];
    aEnviar[6] = cantVehi;
    
    int i;
    int acum = 0;
    for (i = 0; i < 6; i++){
        acum = acum + (aEnviar[i] * 0x0100);
        i++;
        acum = acum + aEnviar[i];
    }
    aEnviar[6] = acum / 100;
    aEnviar[7] = acum & 100;
}


void PaqueteC(void){
    aEnviar[0] = SOF;
    aEnviar[1] = 8;
    aEnviar[2] = recibido[POS_SRC];
    aEnviar[3] = DST;
    aEnviar[4] = recibido[POS_SEC];
    aEnviar[5] = recibido[POS_CMD];
    aEnviar[6] = obtenerVehisGrades();
    
    int i;
    int acum = 0;
    for (i = 0; i < 6; i++){
        acum = acum + (aEnviar[i] * 0x0100);
        i++;
        acum = acum + aEnviar[i];
    }
    aEnviar[6] = acum / 100;
    aEnviar[7] = acum & 100;
}


void PaqueteD(void){
    aEnviar[0] = SOF;
    aEnviar[2] = recibido[POS_SRC];
    aEnviar[3] = DST;
    aEnviar[4] = recibido[POS_SEC];
    aEnviar[5] = recibido[POS_CMD];
    int i = 6;
    int pos;
    if(hayVehiculos(recibido[POS_CMD + 1], &pos)){
        listarVehiculos(recibido[POS_CMD + 1], pos, &i);         // E/S int i, devuelve en donde se quedo el indice
    }
    else{
        aEnviar[i] = 0;
    }
    
    int j;
    int acum = 0;
    for (j = 0; j < 6; j++){
        acum = acum + (aEnviar[j] * 0x0100);
        j++;
        acum = acum + aEnviar[j];
    }
    aEnviar[i++] = acum / 100;
    aEnviar[i] = acum & 100;
}

















void actualizoReloj(void){
    unsigned int horas = linea_1[0] * 10 + linea_1[1];
    unsigned int minutos = linea_1[3] * 10 + linea_1[4];
    unsigned int segundos = linea_1[6] * 10 + linea_1[7];
    
    if (segundos == 59){
        if(minutos == 59){
            if(horas == 23){
                horas = 0;
            }
            else{
                horas++;
            }
            minutos = 0;
        }
        else{
            minutos++;
        }
        segundos = 0;        
    }
    else{
        segundos++;
    }
    
    linea_1[0] = horas / 10;
    linea_1[1] = horas & 10;
    linea_1[3] = minutos / 10;
    linea_1[4] = minutos & 10;
    linea_1[6] = segundos / 10;
    linea_1[7] = segundos & 10;
    
    puts_lcd( (unsigned char*) &linea_1[0], sizeof(linea_1) -1 );
    
}


void accionarCamara(void){
    LATAbits.LATA0 = 1;
    Delay(10);
    LATAbits.LATA0 = 0;
}


void conseguirTimeStamp(HORARIO* ts){
    (*ts).h = linea_1[0]*10 + linea_1[1];
    (*ts).m = linea_1[3]*10 + linea_1[4]; //en las posiciones 2 y 5 estan los ':'
    (*ts).s = linea_1[6]*10 + linea_1[7];
}


void logearVehi(HORARIO ts, int vel, int ejes){
    
    dataLogger[iData].hora = ts; 
    dataLogger[iData].vel = vel;
    dataLogger[iData].ejes = ejes;
    iData++;
}


void actualizarInfo(HORARIO ts, int vel, int ejes){
    linea_1[12] = (cantVehi / 1000);
    linea_1[13] = ((cantVehi & 1000) / 100);
    linea_1[14] = (((cantVehi & 1000) & 100) / 10);
    linea_1[15] = (((cantVehi & 1000) & 100) & 10);
    
    linea_2[0] = (vel / 100);
    linea_2[1] = ((vel & 100) / 10);
    linea_2[2] = ((vel & 100) & 10);
    linea_2[3] = 'K';
    linea_2[4] = 'H';
    linea_2[5] = ' ';
    linea_2[6] = ejes;
    linea_2[7] = ' ';
    linea_2[8] = (ts.h) / 10;
    linea_2[9] = (ts.h) & 10;
    linea_2[10] = ':'; 
    linea_2[11] = (ts.m) / 10;
    linea_2[12] = (ts.m) & 10;
    linea_2[13] = ':';
    linea_2[14] = (ts.s) / 10;
    linea_2[15] = (ts.s) & 10;
    
    /*HH:MM:SS    CCCC*/
    /*VVVKH E HH:MM:SS*/
    
    home_it();
	puts_lcd( (unsigned char*) &linea_1[0], sizeof(linea_1) -1 );
	line_2();
	puts_lcd( (unsigned char*) &linea_2[0], sizeof(linea_2) -1 );
    
}


void chequearVelocidad (int vel){
    if(vel >= MAX_VEL){
        accionarCamara();
    }
}


int CalcVel (int cant){
    return ((DISTANCIA_SENSORES / ((cant * ((ValPR4 * 256)/ FCY)) + ((TMR4 * 256)/FCY))) * (3600/1000));
}


int checkDST(void){
    return (recibido[POS_DST] == DST);
}


int checkSEC(unsigned int *dirSec){
    if (*dirSec == SEC1){
        return (recibido[POS_SEC] == SEC2);
        *dirSec = SEC2;
        
    }
    else if (*dirSec == SEC2){
        return (recibido[POS_SEC] == SEC1);
        *dirSec = SEC1;
    }
    else{
        return 0;   //Contemplamos el caso de que nos envien un valor de SEC
                    //distinto de 0 y 80h
    }
}


int checkCMD(void){
    if( (recibido[POS_CMD] == CMD_1) || (recibido[POS_CMD] == CMD_2) || (recibido[POS_CMD] == CMD_3) || (recibido[POS_CMD] == CMD_5) || (recibido[POS_CMD] == CMD_6) || (recibido[POS_CMD] == CMD_7) ){
        return 1;
    }
    else{
        if(recibido[POS_CMD] == 'D'){
            return ( (recibido[POS_CMD + 1] >= 0) && (recibido[POS_CMD + 1] <= 23) );
        }
        else{
            return 0;
        }
    }
}


int checkBCC(void){
    int qty = recibido[POS_QTY];
    int checksum = (recibido[qty - 1] * 0x0100) + (recibido[qty]);
    unsigned int acum = 0;
    int i;
    if (qty % 2){
        for (i = 0; i < (qty-3); i++){
            acum = acum + (recibido[i] * 0x0100);
            i++;
            acum = acum + recibido[i];
            
        }
        acum = acum + recibido[i];
    }
    else{
        for (i = 0; i < (qty-2); i++){
            acum = acum + (recibido[i] * 0x0100);
            i++;
            acum = acum + recibido[i];
        }
    }
    
    return (acum == checksum);
        
}

int paqueteCorrecto(unsigned int sec){
    return (checkDST() && checkSEC(&sec) && checkCMD() && checkBCC());
}


void limpiarPaquete(char* cad, int tope){
    int i;
    for (i = 0; i < tope; i++){
        cad[i] = 0;
    }
}


void envioNACK (void){
    aEnviar[0] = 0x00FE;
    aEnviar[1] = 8;
    aEnviar[2] = recibido[POS_SRC];    //fuente del mensaje recibido
    aEnviar[3] = DST;
    aEnviar[4] = SEC_NACK;
    aEnviar[5] = CMD_NACK;
    
    int i;
    int acum = 0;
    for (i = 0; i < 6; i++){
        acum = acum + (aEnviar[i] * 0x0100);
        i++;
        acum = acum + aEnviar[i];
    }
    aEnviar[6] = acum / 100;
    aEnviar[7] = acum & 100;
}


void envioACK (void){
    aEnviar[0] = 0x00FE;
    aEnviar[1] = 8;
    aEnviar[2] = recibido[POS_SRC];    //fuente del mensaje recibido
    aEnviar[3] = DST;
    aEnviar[4] = SEC_ACK;
    aEnviar[5] = CMD_ACK;
    
    int i;
    int acum = 0;
    for (i = 0; i < 6; i++){
        acum = acum + (aEnviar[i] * 0x0100);
        i++;
        acum = acum + aEnviar[i];
    }
    aEnviar[6] = acum / 100;
    aEnviar[7] = acum & 100;
}


void armarRespuesta(void){
    switch(recibido[POS_CMD]){
        case (CMD_1): 
            PaqueteA();
            break;
        case (CMD_2):
            iData = 0;
            cantVehi = 0;
            envioACK();
            break;
        case (CMD_3):
            PaqueteC();
            break;
        case (CMD_4): 
            PaqueteD();
            break;
        case (CMD_5):
            accionarCamara();
            break;
        case (CMD_6):
            envioACK();
            break;
        case(CMD_7):
            envioNACK();
            break;
    }
}

