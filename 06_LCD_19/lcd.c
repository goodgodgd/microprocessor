#include <mega128.h>
#include <delay.h>

#asm
.equ __lcd_port=0x1b
#endasm
#include <lcd.h>

void main(void)
{
	int i;
	char buff = 'O'; 		// LCD ��� Data ���� ���� ����	
	 
	PORTA=0xff;	
	DDRA=0xff;
	
	lcd_init(16);		
	lcd_gotoxy(0,0);	
	delay_us(500); 	
	lcd_putchar(buff) ;		// LCD (0,0) ��ġ ���� ��O�� ���

    while(1)
    {
        for(i = 1; i<=15 ; i++)             // ȭ�� ������ ����Ʈ
        { 
            _lcd_ready();
            _lcd_write_data(0x1c);        // ��������Ϳ� ��� �Է�
            delay_ms(200);
        } 

        for(i = 1; i<=15 ; i++) 	         // ȭ�� ���� ����Ʈ
        { 
            _lcd_ready();
            _lcd_write_data(0x18);        // ���� �������Ϳ� ��� �Է�
            delay_ms(200);
        }
	}
}