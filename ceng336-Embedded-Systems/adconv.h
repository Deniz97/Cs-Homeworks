#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include"lcd.h"

    unsigned char l;            //--- To Store Lower 8 bit of ADC o/p
    unsigned int h,t;           //--- To Store Higher 2 bit of ADC o/p

/*ADC INITIALIZATION FUNCTION*/
    void adc_init()
    {
        ADCON0bits.ADON = 1;    //--- ADC Module Enable
        ADCON1 = 0x09;          //--- Channel 0-5 are Analog and Vref=Vdd+Vss
        ADCON2 = 0xAD;          //--- Right Adjust and Clcok = F_CPU/16
    }

/*ADC READ FUNCTION*/
    unsigned int adc_read(unsigned char x)
    {
        ADCON0 |= ((0x3C) & (x<<2));  //--- To select channel as desired
        ADCON0bits.GO = 1;            //--- Start of Conversion
        while(!ADCON0bits.DONE == 1); //--- End of Conversion Check
        ADCON0bits.GO = 1;            //--- Enable ADC Conversion once again
        l = ADRESL;                   //--- Lower 8 bit Data of ADC
        h = ADRESH;                   //--- Higher 2 bit Data of ADC
        h = h << 8;                   //--- Shift 2 bit to higher 8 bit
        t = h | l;                    //--- Add 8 lower bit and 2 higher bit
        return(t);
    }

 /*ADC WRITE FUNCTION*/
    void adc_write(unsigned int x)
    {
        lcd_cmd(0xC0);                      //--- 2nd Line in LCD
        lcd_dwr(((x)/1000)%10 | (0x30));    //--- Convert HEX to Decimal
        lcd_dwr(((x)/100)%10 | (0x30));     //--- Convert HEX to Decimal
        lcd_dwr(((x)/10)%10 | (0x30));      //--- Convert HEX to Decimal
        lcd_dwr((x)%10 | (0x30));           //--- Convert HEX to Decimal
        lcd_msg(" H");                      //--- MSG
    }

/*END OF ADC FILE*/
#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */
