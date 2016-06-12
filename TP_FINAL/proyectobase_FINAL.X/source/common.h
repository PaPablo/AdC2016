/* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author            Date      Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Richard Fischer   07/14/05  general variable linkage information
* Priyabrata Sinha  01/27/06  Ported to non-prototype devices
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
* 1. This file contains definitions commonly used in this project.
*
**********************************************************************/
#define USAR_LCD


#define ValPR4	39062
#define ValPR6	39062
#define FCY 40000000
#define BAUDRATE 9600
#define BRGVAL ((FCY / BAUDRATE) / 16) -1
#define ESPERA_1BIT (1/BAUDRATE)
#define CANT_BITSxBYTE 10
#define ESPERA_1BYTE ((ESPERA_1BIT) * CANT_BITSxBYTE)
#define SOF 0xFE

#define POS_QTY                 1
#define DST                     3
#define POS_DST                 2
#define SEC1                    0
#define SEC2                    0x80
#define POS_SEC                 4
#define POS_CMD                 5
#define SEC_ACK                 0x40
#define SEC_NACK                0x60
#define DISTANCIA_SENSORES      0.3
#define MAX_VEL                 60
#define MAX_VEHI                1000

//Maximo de bytes a recibir 
#define MAX_RX 9

//Maximo de bytes a enviar
#define MAX_TX 256

unsigned int seg = 0;
unsigned char linea_1[] = "00:00:00        ";
unsigned char linea_2[] = "                ";

typedef struct{
    unsigned char    hora[8];
    unsigned char    vel;
    unsigned char    ejes;
}VEHICULOS;

VEHICULOS dataLogger[MAX_VEHI];
int iData = 0;                  //indice del dataLogger


#ifdef USAR_LCD
/*****	LCD COMMAND FUCNTION PROTOTYPES  *****/
#define cursor_right()  lcd_cmd( 0x14 )
#define cursor_left()   lcd_cmd( 0x10 )
#define display_shift() lcd_cmd( 0x1C )
#define home_clr()      lcd_cmd( 0x01 ) 
#define home_it()       lcd_cmd( 0x02 ) 
#define line_2()        lcd_cmd( 0xC0 ) // (0xC0)

#endif // USAR_LCD


