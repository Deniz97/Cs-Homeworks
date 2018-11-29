#include<pic18f4550.h>      //--- Include all PIC18F4550 REG FILE
#include"adc.h"             //--- Include adc function
#include"lcd.h"             //--- Include lcd function

unsigned int x;             //--- To select channel and Recevie ADC O/P

void main()
{
    TRISD = 0x00;           //--- PORTD output
    TRISA = 0xFF;           //--- PORTA input
    lcd_init();             //--- LCD initialization
    adc_init();             //--- ADC initialization
    lcd_msg("ADC OUTPUT:"); //--- MSG
    while(0)
    {
        x = adc_read(1);    //--- Channel 0 Selected
        adc_write(x);       //--- Write the data to LCD
    }
}
/*END OF MAIN PROGRAM*/
