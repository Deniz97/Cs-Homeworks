#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define lcd PORTD
#define rs PORTDbits.RD0
#define en PORTDbits.RD1
    
/*DELAY FUNCTION*/
    void delay(unsigned int ms)
    {
        unsigned int i,j;
        for(i=0;i<=ms;i++)          //--- User Defined Delay
            for(j=0;j<=120;j++);    //--- 1 sec delay loop
    }

/*LCD LATCH FUNCTION*/
    void lcd_lat()
    {
        en = 1;                     //--- High to Low Pulse to Latch data
        delay(1);                   //--- into LCD
        en = 0;
    }
/*LCD COMMAND FUNCTION*/
    void lcd_cmd(unsigned char x)
    {
        rs = 0;                     //--- Register Select as Command
        lcd &= 0x0F;                //--- Masking
        lcd |= (x & 0xF0);          //--- Masking Higher bit and send to LCD
        lcd_lat();                  //--- Latch data to LCD
        
        lcd &= 0x0F;                //--- Masking
        lcd |= ((x & 0x0F)<<4);     //--- Masking Higher bit and send to LCD
        lcd_lat();                  //--- Latch data to LCD
    }

/*LCD DATA FUNCTION*/
    void lcd_dwr(unsigned char x)
    {
        rs = 1;                     //--- Register Select as Data
        lcd &= 0x0F;                //--- Masking
        lcd |= (x & 0xF0);          //--- Masking Higher bit and send to LCD
        lcd_lat();                  //--- Latch data to LCD
        
        lcd &= 0x0F;                //--- Masking
        lcd |= ((x & 0x0F)<<4);     //--- Masking Higher bit and send to LCD
        lcd_lat();                  //--- Latch data to LCD
    }
    
/*LCD STRING FUNCTION*/
    void lcd_msg(unsigned char *c)
    {
        while(*c != 0)              //--- Pointer not equal to zero
            lcd_dwr(*c++);          //--- Send data to LCD
    }
    
/*LCD INITIALIZATION FUNCTION*/
    void lcd_init()
    {
        lcd_cmd(0x03);              //--- Sequence to enable 4 - bit LCD
        lcd_cmd(0x02);              //--- Sequence to enable 4 - bit LCD
        lcd_cmd(0x28);              //--- 16 x 2 line 4 - bit LCD
        lcd_cmd(0x0C);              //--- Cursor On Blinking Off
        lcd_msg("LCD TEST SUCCESS");//--- MSG
        lcd_cmd(0xC0);              //--- Next Line in LCD
        lcd_msg("CODE-N-LOGIC");    //--- MSG
        delay(2000);                //--- 2 sec delay
        lcd_cmd(0x01);              //--- Clear LCD
        lcd_cmd(0x80);              //--- 1st Line in LCD
    }

/*END OF LCD FUNCTION*/
#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

