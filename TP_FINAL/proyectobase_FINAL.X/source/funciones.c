#include "common.h"
#include "p33FJ256GP710.h"
extern int paqueteRecibido;
extern char recibido[MAX_RX];
extern char aEnviar[MAX_TX];
extern unsigned char linea_1[];

void actualizoReloj(){
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
void conseguirTimeStamp(char* ts){
    int i;
    for(i = 0; i <= 8; i++){
        ts[i] = linea_1[i];
    }
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
    if( (recibido[POS_CMD] == 'A') || (recibido[POS_CMD] == 'B') || (recibido[POS_CMD] == 'C') || (recibido[POS_CMD] == 'E') ){
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

void limpiarPaquete(char* cad, int tope){
    int i;
    for (i = 0; i < tope; i++){
        cad[i] = 0;
    }
}

int paqueteCorrecto(unsigned int sec){
    return (checkDST() && checkSEC(&sec) && checkCMD() && checkBCC());
}