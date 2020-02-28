#include <mega128.h>
#include <delay.h>

#asm
.equ __lcd_port=0x1b 
#endasm
#include <lcd.h>

void main(void)
{ 
    char buff[17]="AVR ATmega128 "; // LCD ��� Data ���� ���� ����    
    PORTA=0xff;    
    DDRA=0xff;
    
    lcd_init(16);        // Character LCD 16 * 2 ��� ���� 
    lcd_gotoxy(0,0);    	// LCD 1 line ���� �Լ�, x=0, y=0 
	delay_us(500); 		// �ð� ���� �Լ�
	lcd_puts(buff);		// buff���� Data�� LCD�� ��� 
	lcd_gotoxy(0,1);		// LCD 2 line ���� �Լ�, x=0, y=1
	lcd_putsf("ROBOT SYSTEM"); 	// Data�� LCD�� ���
	while(1){ }		
}
