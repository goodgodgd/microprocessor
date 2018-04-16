#include <mega128.h>
#include <delay.h>
#include <stdio.h>
#include <string.h>

#asm
.equ __lcd_port=0x1b
#endasm
#include <lcd.h>

unsigned char fnd[10]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x98};

void main(void)
{
    int i, step = 0;
    unsigned char shift=0;
    int curkey = 0;
    int keyins[3] = {0,0,0};
    char lcd_buf[16];
    memset(lcd_buf, 0x00, 16);
     
    PORTA=0xff; DDRA=0xff;  // PORTA: LCD
    PORTB=0x00; DDRB=0xff;  // PORTB: FND
    PORTC=0xff; DDRC=0x00;  // PORTC: switch
    
    lcd_init(16);
    delay_ms(1);
    lcd_putsf("Press switches");        

    while(1)
    {   
        delay_ms(1);
        
        // read switch
        curkey = 0;
        for(i=0; i<8; i++)
            if(PINC == ~(0x01<<i))
                curkey = i;
        
        if(PINC == ~0x02)
            curkey=1;
        if(PINC == ~0x04)
            curkey=2;
        shift=3;
        if(PINC == ~(0x01<<3))
            curkey=3;

        
        PORTB = ~fnd[curkey];
        continue;
        if(curkey < 0 || curkey > 8)
            continue;
        
        while(PINC!=0xff)
            delay_ms(1);
        
        // show current key
        PORTB = ~fnd[curkey];
        
        // keep pressed numbers
        keyins[step] = curkey;
        step++;
        
        // print numbers and operation result
        if(step==3)
        {
            step = 0;
            lcd_gotoxy(0,1);
            
            switch(keyins[1])
            {
            case 0: sprintf(lcd_buf, "%2d + %2d = %2d", keyins[0], keyins[2], keyins[0]+keyins[2]); break;
            case 1: sprintf(lcd_buf, "%2d - %2d = %2d", keyins[0], keyins[2], keyins[0]-keyins[2]); break;
            case 2: sprintf(lcd_buf, "%2d * %2d = %2d", keyins[0], keyins[2], keyins[0]*keyins[2]); break;
            case 3: sprintf(lcd_buf, "%2d / %2d = %2d", keyins[0], keyins[2], keyins[0]/keyins[2]); break;
            default: sprintf(lcd_buf, "invalid operator"); break;
            }
            
            lcd_puts(lcd_buf);
        } 
    }
}