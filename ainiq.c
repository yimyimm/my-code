/*
 * Author : FlyingWhale (Aiman R.)
 * Date : 11 . 05 . 2025
 *
 * Komponen yang digunakan dalam coding ini:
 * 2 Push Button Active Low
 * LCD HD44780
 * 7 Segment
 *
 * Functionality:
 * LCD dan 7seg akan memamparkan Counter (0-9)
 * Push Button 1 (RA0) akan auto countdown 0 hingga 9
 * Push Button 2 (RA1) akan reset counter ke 0
 */

//write define here!
#define SEGMENT PORTD
#define HD44780     //IC LCD yang digunakan
#define ETN804

//write include file here!
#include "LibraryHardware.h"
#include "LibraryPeripheral.h"
#include "LibraryUniversalDisplay.h"

const static char segment[] = {     //Config for 7 segment Display
//.abcdefg
0b01111110,0b00110000,0b01101101,0b01111001,0b00110011,
0b01011011,0b01011111,0b01110000,0b01111111,0b01111011,
};


void setup()
{
    initialize();
    //GPIO =  76543210
    TRISA = 0b00000011; //0 = OUTPUT / 1 = INPUT
    TRISB = 0b00000000;
    TRISC = 0b00000000;
    TRISD = 0b00000000;
    TRISE = 0b00000000;
//    lcd_init();     //To calling LCD
    BUZZER=1;       /* Kenapa BUZZER disetkan 1(HIGH) kerana buzzer dalam litar
                     * kerana BUZZER dalam litar ini disetkan kepada Active low
                     * logic
                     */
}

void loop()
{
    int counter = 0; //default state counter adalah 0

    while(1)
    {

//        lcd_goto(0,0);  //setkan lcd punya (pos,row)
//        lcd_number(counter, DEC, 1);
//        lcd_string(" ");
        /* LCD akan display Counter mengikut nombor
         * decimal dengan 1 digit
         */
        SEGMENT = segment[counter];
        /*output segment akan mengikut setting yang
         * diberi, tapi bersyarat mengikut counter
         */

        // Auto counter UP
        if(RA0 == 0)
        {
            __delay_ms(20); //DEBOUNCE
            if(RA0 == 0)
            {
                while(counter < 9)
                {
                    counter++;
//                    lcd_goto(0,0);
//                    lcd_number(counter, DEC, 1);
//                    lcd_string(" ");
                    SEGMENT = segment[counter];
                    __delay_ms(1000);
                }

                while(RA0 == 0);
                __delay_ms(20);
            }
        }

        //RESET
        if(RA1 == 0)
        {
            __delay_ms(20);
            if(RA1 == 0)
            {
                counter = 0;

                while(RA1 == 0);
                __delay_ms(20);
            }
        }
    }
}
