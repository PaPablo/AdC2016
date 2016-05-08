/*Configuracion y Rutinas DMA*/
void Init_DMA(void);
//rutinas de pulsadores
void promedioDMA(void); //recoge el promedio de los buffer
void mayorDMA(void);    //recoge el mayor
void menorDMA(void);    //recoge el menor

//variables externas con los valores del buffer
extern int promedio;    
extern int mayor;
extern int menor;