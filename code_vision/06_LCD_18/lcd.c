#include <mega128.h>
#include <delay.h>
#include <stdio.h>         // sprintf() �Լ��� ���

// PORTA�� LCD ������� ����
#asm
.equ __lcd_port=0x1b 
#endasm
#include <lcd.h>

void main(void)
{
    unsigned char curpin, buff=0x00;
    PORTA=0xff;   DDRA=0xff;
    PORTC=0xff;   DDRC=0x00;
    
    lcd_init(16);        // Character LCD 16 * 2 ��� ���� 
    lcd_gotoxy(0,0);	 	// LCD 1 line ���� �Լ�, x=0, y=0 
	lcd_putsf("No Switch"); 	// Data�� LCD�� ���

	while (1)
	{
        curpin = PINC;
        curpin &= 0b00001111; 
        delay_ms(100);
        if(curpin==buff)
            continue;
        
        buff = curpin;
        switch(buff) {
        case 0b00001110:             // SW0 ON �� �� 
              lcd_clear();  delay_ms(10); 
		      lcd_putsf("Switch 0 ON");   break;

		case 0b00001101: 			// SW1 ON �� �� 
		      lcd_clear();  delay_ms(10); 
		      lcd_putsf("Switch 1 ON");  break;

		case 0b00001011: 			// SW2 ON �� �� 
		      lcd_clear();  delay_ms(10); 
		      lcd_putsf("Switch 2 ON");  break; 

		case 0b00000111: 			// SW3 ON �� �� 
		      lcd_clear();  delay_ms(10); 
		      lcd_putsf("Switch 3 ON"); break; 

		default : 
		      lcd_clear();  delay_ms(10); 
		      lcd_putsf("No Switch");  break; 
	        }
	};  // while ��
}
