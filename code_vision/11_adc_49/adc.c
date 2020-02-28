#include <mega128.h> 
#include <delay.h>
#include <stdio.h>
#asm
.equ __lcd_port=0x1B;       // PORTA
#endasm
#include <lcd.h>

#define ADC_VREF_TYPE   0x40    // AVCC�� ���� �������� ���
char sbuf[16];              // LCD ����� ����

void MPUinit(void)
{
    PORTA=0xff; DDRA=0xff;  // PORTA : LCD 
    PORTC=0xff; DDRC=0xff;  // PORTC : ���ܼ� LED 
    PORTE=0x00; DDRE=0xff;  // PORTE : �Ϲ� LED���
    PORTF=0x00; DDRF=0x00;  // PORTF : (A/D �Է�)
    // ADC initialization
    ADMUX=ADC_VREF_TYPE;
	ADCSRA=0x86; 		        // 64���� , 250kHz
}

void ReadAdc(int* adc_out) //---- ���� ���� A/D��ȯ ó�� �Լ� ----------
{
    unsigned char fire = 0x01;
    int i=0;
    for(i=0; i<4; i++)
    {
        PORTC = 0xfe;
        delay_us(30);
        
        ADMUX = ADC_VREF_TYPE|i; 
        ADCSRA |= 0x40;	                // Start the AD conversion
        while((ADCSRA & 0x10)==0); 	// Wait for the AD conversion to complete
//        ADCSRA|=0x10;
        adc_out[i] = ADCW; //(int)ADCL + ((int)ADCH << 8);
        PORTC = 0xff;

        fire <<= 1;
        delay_ms(1);
    }
}

void main(void)
{
    int AData[4] = {0,0,0,0};   // A/D ��ȯ�� �������� ����� ����
    MPUinit();
    lcd_init(16);
    
    while (1)
    {
        ReadAdc(AData); 		// ���� ���� A/D��ȯ ó��
        
        sprintf(sbuf,"%4d, %4d", AData[0], AData[1]); 	// 0,1�� ���� A/D��ȯ�� ǥ��
        lcd_gotoxy(0,0);	
        lcd_puts(sbuf);
        delay_ms(1);
        
        sprintf(sbuf,"%4d, %4d", AData[2], AData[3]); 	// 2,3�� ���� A/D��ȯ�� ǥ��
        lcd_gotoxy(0,1);	
        lcd_puts(sbuf);
        delay_ms(20);
    };
}
