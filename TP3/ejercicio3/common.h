/* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author            Date      Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Richard Fischer   07/14/05  general variable linkage information
* Priyabrata Sinha  01/27/06  Ported to non-prototype devices
* Marcelo G�mez     09/03/14  Portado a MPLAB.X
* Sebasti�n Wahler  25/04/14  Agregado de ADC
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
* 1. This file contains definitions commonly used in this project.
*
**********************************************************************/


/* variables used in raw ADC data to hex */
extern void advolt( unsigned int adc_conv_data );
extern volatile unsigned char adones;
extern volatile unsigned char adtens;
extern volatile unsigned char adhunds;
extern volatile unsigned int temp1;
extern volatile unsigned char adc_update;

#define USAR_LCD
#ifdef USAR_LCD
/*****	LCD COMMAND FUCNTION PROTOTYPES  *****/
#define cursor_right()  lcd_cmd( 0x14 )
#define cursor_left()   lcd_cmd( 0x10 )
#define display_shift() lcd_cmd( 0x1C )
#define home_clr()      lcd_cmd( 0x01 ) 
#define home_it()       lcd_cmd( 0x02 ) 
#define line_2()        lcd_cmd( 0xC0 ) // (0xC0)

#endif // USAR_LCD