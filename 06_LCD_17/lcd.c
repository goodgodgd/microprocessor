#include <mega128.h>
#include <delay.h>
#include <stdio.h>         // sprintf() 함수를 사용

// PORTA를 LCD 출력으로 설정
#asm
.equ __lcd_port=0x1b 
#endasm
#include <lcd.h>

void main(void)
{
    int i=0; 
    char sbuf[16] ;         
    PORTA = 0xff;
    DDRA = 0xff;
    lcd_init(16);             // LCD module initialization
    
    while (1)
    {
        lcd_gotoxy(0,0) ;         // LCD X,Y Select
        lcd_putsf("Current Value");         // LCD Display

        for( i = 0 ; i <= 1000 ; i++ ) 		
        {
            sprintf(sbuf, "DATA = %4d", i); 
            lcd_gotoxy(0,1) ; 	
            lcd_puts(sbuf); 	
            delay_ms(100) ; 		
        }
	};
}
