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

extern VEHICULOS nuevoVehi;


void ToggleTest (void)
{
			__builtin_btg((unsigned int *)&LATA, 7);
			__builtin_btg((unsigned int *)&LATA, 6);
			__builtin_btg((unsigned int *)&LATA, 5);
			__builtin_btg((unsigned int *)&LATA, 4);
			__builtin_btg((unsigned int *)&LATA, 3);
			__builtin_btg((unsigned int *)&LATA, 2);	
			__builtin_btg((unsigned int *)&LATA, 1);
			__builtin_btg((unsigned int *)&LATA, 0);
}


int armarCheksum(int inicio, int tope, char* arreglo){
		int i;
        int chk = 0;
		if (tope % 2){
			for (i = inicio; i < (tope-1); i++){
				chk = chk + (arreglo[i] * 0x0100);
				i++;
				chk = chk + arreglo[i];
			}
			chk = chk + arreglo[i] * 0x100;
		}
		else{
			for (i = inicio; i < tope; i++){
				chk = chk + (arreglo[i] * 0x0100);
				i++;
				chk = chk + arreglo[i];
			}
		}
		return chk;
	}

void limpiarRegVehi(void){
    nuevoVehi.ejes = 0;
    nuevoVehi.vel = 0;
    nuevoVehi.hora.h = 0;
    nuevoVehi.hora.m = 0;
    nuevoVehi.hora.s = 0;
}

int obtenerVehisGrandes(void){
    int i = 0;
    int acum = 0;
    while(dataLogger[i++].ejes > 0){      //recorremos el listado (si la cant ejes es cero es porque no hay vehi registrado)
        if (dataLogger[i].ejes > 2){    
            acum++;
        }
    }
    return acum;
}

void limpiarDataLogger(void){
    iData = 0;
    cantVehi = 0;
    int i;
    for(i = 0; i <= MAX_VEHI; i++){
        dataLogger[i].ejes = 0;
        dataLogger[i].vel = 0;
        dataLogger[i].hora.h = 0;
        dataLogger[i].hora.m = 0;
        dataLogger[i].hora.s = 0;
    }
}

int hayVehiculos(char hora, int* pos){
    int i = 0;
    _Bool siHay = 0;
    while((dataLogger[i].ejes > 0) && (!siHay)){
        if (dataLogger[i].hora.h == (unsigned char)hora){      //buscamos en el dataLogger si hay al menos un vehiculo registrado a la hora ingresada
            siHay = 1;
            *pos = i;
        }
        i++;
    }
    return (siHay);        //Si se cumple la condicion, es porque hay al menos un vehiculo
                                //registrado que paso a la hora recibida.
}


void listarVehiculos(int hora, int pos, int* i){
    _Bool salgo = 0;
    int j = *i;
    while(!salgo){
        if (dataLogger[pos].hora.h == hora){
            //tiramos al arreglo de carac a enviar los datos registrados
            //de los vehiculos que pasaron en la hora ingresada
            aEnviar[j++] = dataLogger[pos].hora.h;  //Hora
            aEnviar[j++] = dataLogger[pos].hora.m;  //Minutos
            aEnviar[j++] = dataLogger[pos].hora.s;  //Segundos
            aEnviar[j++] = dataLogger[pos].vel;     //Velocidad
            aEnviar[j++] = dataLogger[pos].ejes;      //Ejes
        }
        else{
            salgo = 1;
        }
        pos++;
    }
    *i = j;
}




void PaqueteA(void){
    aEnviar[0] = SOF;
    aEnviar[1] = QTY_PAQ;
    aEnviar[2] = recibido[POS_SRC];
    aEnviar[3] = DST;
    aEnviar[4] = recibido[POS_SEC];
    aEnviar[5] = recibido[POS_CMD];
    aEnviar[6] = cantVehi;
    
    
    int acum = armarCheksum(0, (QTY_PAQ - 2), aEnviar);

	
    aEnviar[QTY_PAQ - 2] = (acum / 0x0100) - 1;
    aEnviar[QTY_PAQ - 1] = acum % 0x0100;
}


void PaqueteC(void){
    aEnviar[0] = SOF;
    aEnviar[1] = QTY_PAQ;
    aEnviar[2] = recibido[POS_SRC];
    aEnviar[3] = DST;
    aEnviar[4] = recibido[POS_SEC];
    aEnviar[5] = recibido[POS_CMD];
    aEnviar[6] = obtenerVehisGrandes();
    
    int acum = armarCheksum(0, (QTY_PAQ - 2), aEnviar);


    aEnviar[QTY_PAQ - 2] = (acum / 0x0100) - 1;
    aEnviar[QTY_PAQ - 1] = acum % 0x0100;
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
        aEnviar[i++] = 0;	//No se registraron vehiculo en la hora ingresada
    }
    aEnviar[1] = i+2;     //QTY, el +2 se debe a los lugares para el checksum
    
    int acum = armarCheksum(0, i, aEnviar);
	
    aEnviar[i++] = (acum / 0x0100);
    aEnviar[i++] = acum % 0x0100;
    
    
}















void actualizoReloj(void){
    unsigned char horas = (((linea_1[0] - OFFSET_CARAC) * 10) + (linea_1[1] - OFFSET_CARAC));
    unsigned char minutos = (((linea_1[3] - OFFSET_CARAC) * 10) + (linea_1[4] - OFFSET_CARAC));
    unsigned char segundos = (((linea_1[6] - OFFSET_CARAC) * 10) + (linea_1[7] - OFFSET_CARAC));
    
    if (segundos < 59){
        segundos++;
    }
    else{
        segundos = 0;
        if(minutos < 59){
            minutos++;
        }
        else{
            minutos = 0;
            if(horas < 23){
                horas++;
            }
            else{
                horas = 0;
            }
        }
    }
   
    
    linea_1[0] = ((horas / 10) + OFFSET_CARAC);
    linea_1[1] = ((horas % 10) + OFFSET_CARAC);
    linea_1[3] = ((minutos / 10) + OFFSET_CARAC);
    linea_1[4] = ((minutos % 10) + OFFSET_CARAC);
    linea_1[6] = ((segundos / 10) + OFFSET_CARAC);
    linea_1[7] = ((segundos % 10) + OFFSET_CARAC);
    
    home_it();
    puts_lcd( (unsigned char*) &linea_1[0], sizeof(linea_1) -1 );
    
}


void accionarCamara(void){
    LATAbits.LATA0 = 1;
    Delay(10);
    LATAbits.LATA0 = 0;
}


void conseguirTimeStamp(HORARIO* ts){
    
    (*ts).h = (((linea_1[0] - OFFSET_CARAC) * 10) + (linea_1[1] - OFFSET_CARAC));
    (*ts).m = (((linea_1[3] - OFFSET_CARAC) * 10) + (linea_1[4] - OFFSET_CARAC));//en las posiciones 2 y 5 estan los ':'
    (*ts).s = (((linea_1[6] - OFFSET_CARAC) * 10) + (linea_1[7] - OFFSET_CARAC));
 
}


void logearVehi(VEHICULOS vehi){
    
    dataLogger[iData] = vehi;
    iData++;
    cantVehi++;
}


void actualizarInfo(VEHICULOS vehi){
    linea_1[13] = (cantVehi / 10) + OFFSET_CARAC;
    /*linea_1[13] = ((cantVehi % 1000) / 100) + OFFSET_CARAC;
    linea_1[14] = (((cantVehi % 1000) % 100) / 10) + OFFSET_CARAC;
    linea_1[15] = (((cantVehi % 1000) % 100) % 10) + OFFSET_CARAC;*/
    linea_1[14] = cantVehi + OFFSET_CARAC;
    
    linea_2[0] = (vehi.vel / 100) + OFFSET_CARAC;
    linea_2[1] = ((vehi.vel % 100) / 10) + OFFSET_CARAC;
    linea_2[2] = ((vehi.vel % 100) % 10) + OFFSET_CARAC;
    linea_2[3] = 'K';
    //linea_2[4] = 'H';
    linea_2[4] = ' ';
    linea_2[5] = vehi.ejes + OFFSET_CARAC;
    linea_2[6] = ' ';
    linea_2[7] = ((vehi.hora.h) / 10) + OFFSET_CARAC;
    linea_2[8] = ((vehi.hora.h) % 10) + OFFSET_CARAC;
    linea_2[9] = ':'; 
    linea_2[10] = ((vehi.hora.m) / 10) + OFFSET_CARAC;
    linea_2[11] = ((vehi.hora.m) % 10) + OFFSET_CARAC;
    linea_2[12] = ':';
    linea_2[13] = ((vehi.hora.s) / 10) + OFFSET_CARAC;
    linea_2[14] = ((vehi.hora.s) % 10) + OFFSET_CARAC;
    
    /*HH:MM:SS    CCCC*/
    /*VVVKH E HH:MM:SS*/
    
    home_it();
	puts_lcd( (unsigned char*) &linea_1[0], sizeof(linea_1) -1 );
	line_2();
	puts_lcd( (unsigned char*) &linea_2[0], sizeof(linea_2) -1 );
    
}


void chequearVelocidad (unsigned int vel){
    if(vel >= MAX_VEL){
        accionarCamara();
    }
}





int checkDST(void){
    return (recibido[POS_DST] == DST);
}


int checkSEC(unsigned int* dirSec){
    if (*dirSec == SEC1){
        *dirSec = SEC2;
        return (recibido[POS_SEC] == (char)SEC2);
    }
    else if (*dirSec == SEC2){
        *dirSec = SEC1;
        return (recibido[POS_SEC] == (char)SEC1);
    }
    else{
        return 0;   //Contemplamos el caso de que nos envien un valor de SEC
                    //distinto de 0 y 80h
    }
}

unsigned char CalcVel (unsigned int cant){
    
    float tR = 256.0/(float)FCY;
    float tiempo_parcial = (float)TMR4 * tR;
    float t = (float)cant * (float)ValPR4 * tR;
    float tiempo_total = tiempo_parcial + t;
    return (unsigned char)((DISTANCIA_SENSORES / tiempo_total) * (3600/1000));
    
    /*tiempo total = tParcial + t
    tParcial = TMR4 * (PRSC / FCY)
    t = (cant * (ValPR4)) * (PRSC / FCY)
    
    float t1 = ((float)cant * ((float)ValPR4 * (float)TMR4));
    float t2 = (float)(tmr * (float)TMR4);
    float kmh = (float)(3600/1000);
    float dist = (10.0 / ((float)DISTANCIA_SENSORES));
    float tFinal = t1+t2;
    float mtss = (float)((0.3)/((float)tFinal));
    float velocidad = ((float)mtss*kmh);
    return velocidad;
    return 0;*/
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
    int checksum = (recibido[qty - 2] * 0x0100) + (recibido[qty-1]);
    int acum = armarCheksum(0, (qty-2), recibido);
    
    return (acum == checksum);
        
}

int paqueteCorrecto(unsigned int sec){
    return (checkDST() && checkSEC(sec) && checkCMD() && checkBCC());
}


void limpiarPaquete(char* cad, int tope){
    int i;
    for (i = 0; i < tope; i++){
        cad[i] = 0;
    }
}


void envioNACK (void){
    aEnviar[0] = SOF;
    aEnviar[1] = QTY_ACK_NACK;
    aEnviar[2] = recibido[POS_SRC];    //fuente del mensaje recibido
    aEnviar[3] = DST;
    aEnviar[4] = SEC_NACK;
    aEnviar[5] = CMD_NACK;
    
    int acum = armarCheksum(0, (QTY_ACK_NACK - 2), aEnviar);
   
    aEnviar[QTY_ACK_NACK - 2] = (acum / 0x0100);
    aEnviar[QTY_ACK_NACK - 1] = acum % 0x0100;
    
}


void envioACK (void){
    aEnviar[0] = SOF;
    aEnviar[1] = QTY_ACK_NACK;
    aEnviar[2] = recibido[POS_SRC];    //fuente del mensaje recibido
    aEnviar[3] = DST;
    aEnviar[4] = SEC_ACK;
    aEnviar[5] = CMD_ACK;
    
    int acum = armarCheksum(0, (QTY_ACK_NACK - 2), aEnviar);
	
    aEnviar[QTY_ACK_NACK - 2] = (acum / 0x0100);
    aEnviar[QTY_ACK_NACK - 1] = acum % 0x0100;
}


void armarRespuesta(void){
    switch(recibido[POS_CMD]){
        case (CMD_1): 
            PaqueteA();
            break;
        case (CMD_2):
            envioACK();
            limpiarDataLogger();
            break;
        case (CMD_3):
            PaqueteC();
            break;
        case (CMD_4): 
            PaqueteD();
            break;
        case (CMD_5):
            envioACK();
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

