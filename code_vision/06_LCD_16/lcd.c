#include <mega128.h>
#include <delay.h>

#asm
.equ __lcd_port=0x1b 
#endasm
#include <lcd.h>

void main(void)
{ 
    char buff[17]="AVR ATmega128 "; // LCD 출력 Data 저장 변수 설정    
    PORTA=0xff;    
    DDRA=0xff;
    
    lcd_init(16);        // Character LCD 16 * 2 사용 선언 
    lcd_gotoxy(0,0);    	// LCD 1 line 선택 함수, x=0, y=0 
	delay_us(500); 		// 시간 지연 함수
	lcd_puts(buff);		// buff변수 Data를 LCD로 출력 
	lcd_gotoxy(0,1);		// LCD 2 line 선택 함수, x=0, y=1
	lcd_putsf("ROBOT SYSTEM"); 	// Data를 LCD로 출력
	while(1){ }		
}
