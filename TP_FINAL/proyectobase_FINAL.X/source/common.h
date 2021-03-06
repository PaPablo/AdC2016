/* REVISION HISTORY:
common.h
*
* ADDITIONAL NOTES:
* 1. This file contains definitions commonly used in this project.
*
**********************************************************************/
#define USAR_LCD


#define ValPR4	39062
#define ValPR6	39062

#define FCY 40000000.0
#define BAUDRATE 9600
#define BRGVAL ((FCY / BAUDRATE) / 16) -1
#define ESPERA_1BIT (1/BAUDRATE)
#define CANT_BITSxBYTE 10
#define ESPERA_1BYTE ((ESPERA_1BIT) * CANT_BITSxBYTE)


#define SOF 0xFE

#define CMD_1                   'A'
#define CMD_2                   'B'
#define CMD_3                   'C'
#define CMD_4                   'D'
#define CMD_5                   'E'
#define CMD_6                   'F'
//#define CMD_7                   'G'

#define QTY_PAQ                 9
#define QTY_ACK_NACK            8

#define DST                     3
#define SEC1                    0x20
#define SEC2                    0x80
#define SEC_ACK                 0x40
#define CMD_ACK                 0x46
#define SEC_NACK                0x60
#define CMD_NACK                0x47


#define DISTANCIA_SENSORES      10

#define OFFSET_CARAC            0x30

#define MAX_VEL                 60
#define MAX_VEHI                1000
#define MAX_LCD                 16
//Maximo de bytes a recibir 
#define MAX_RX 					9

//Maximo de bytes a enviar
#define MAX_TX 					256


typedef struct{
    unsigned char   h;
    unsigned char   m;
    unsigned char   s;
}HORARIO;

typedef struct{
    HORARIO          hora;
    unsigned char    vel;
    unsigned char    ejes;
}VEHICULOS;

typedef volatile unsigned char tipoPaquete;



#ifdef USAR_LCD
/*****	LCD COMMAND FUCNTION PROTOTYPES  *****/
#define cursor_right()  lcd_cmd( 0x14 )
#define cursor_left()   lcd_cmd( 0x10 )
#define display_shift() lcd_cmd( 0x1C )
#define home_clr()      lcd_cmd( 0x01 ) 
#define home_it()       lcd_cmd( 0x02 ) 
#define line_2()        lcd_cmd( 0xC0 ) // (0xC0)

#endif // USAR_LCD


