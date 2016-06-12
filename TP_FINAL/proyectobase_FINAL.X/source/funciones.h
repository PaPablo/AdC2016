int obtenerVehisGrades(void);

int hayVehiculos(char hora, int* pos);

void listarVehiculos(int hora, int pos, int* i);

void PaqueteA(void);

void PaqueteC(void);

void PaqueteD(void);

void actualizoReloj(void);

void accionarCamara(void);

void conseguirTimeStamp(unsigned char* ts);

void logearVehi(unsigned char* ts, int vel, int ejes);

void actualizarInfo(unsigned char* ts, int vel, int ejes);

void chequearVelocidad (int vel);

int CalcVel (int cant);

int checkDST(void);

int checkSEC(unsigned int *dirSec);

int checkCMD(void);

int checkBCC(void);

int paqueteCorrecto(int sec);

void limpiarPaquete(char* cad, int tope);

void envioNACK(void);

void armarRespuesta(void);