#include <mega128.h>
#include <delay.h>

#asm
.equ __lcd_port=0x1b
#endasm
#include <lcd.h>

void main(void)
{
	int i;
	char buff = 'O'; 		// LCD 출력 Data 저장 변수 설정	
	 
	PORTA=0xff;	
	DDRA=0xff;
	
	lcd_init(16);		
	lcd_gotoxy(0,0);	
	delay_us(500); 	
	lcd_putchar(buff) ;		// LCD (0,0) 위치 문자 “O“ 출력

    while(1)
    {
        for(i = 1; i<=15 ; i++)             // 화면 오른쪽 시프트
        { 
            _lcd_ready();
            _lcd_write_data(0x1c);        // 제어레지스터에 명령 입력
            delay_ms(200);
        } 

        for(i = 1; i<=15 ; i++) 	         // 화면 왼쪽 시프트
        { 
            _lcd_ready();
            _lcd_write_data(0x18);        // 제어 레지스터에 명령 입력
            delay_ms(200);
        }
	}
}