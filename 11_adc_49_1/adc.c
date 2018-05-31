#include <mega128.h> 
#include <delay.h>
#include <stdio.h>
#asm
.equ __lcd_port=0x1B;       // PORTA
#endasm
#include <lcd.h>

#define ADC_VREF_TYPE   0x40// AVCC�� ���� �������� ���
char sbuf[16];              // LCD ����� ����

void MPUinit(void)
{
    PORTA=0xff; DDRA=0xff;  // PORTA : LCD 
    PORTC=0xff; DDRC=0xff;  // PORTC : ���ܼ� LED 
    PORTF=0x00; DDRF=0x00;  // PORTF : (A/D �Է�)
    // ADC initialization
    ADMUX=ADC_VREF_TYPE;
    ADCSRA=0x86;                 // 64���� , 250kHz
}

int ReadAdc(unsigned char pin_num) //---- ���� ���� A/D��ȯ ó�� �Լ� ----------
{
    ADMUX = ADC_VREF_TYPE|pin_num; 
    ADCSRA |= 0x40;             // Start the AD conversion
    while((ADCSRA & 0x10)==0);  // Wait for the AD conversion to complete
    return ADCW;                //(int)ADCL + ((int)ADCH << 8);
}

void main(void)
{
    int ADdata;
    MPUinit();
    lcd_init(16);
    
    while(1)
    {
        if(PORTC==0xff)
            PORTC=0x00;
        else
            PORTC=0xff;
        delay_ms(1);
        ADdata = ReadAdc(1);    // ADC1���� A/D ��ȯ
        
        sprintf(sbuf,"ADC result:%4d", ADdata);
        lcd_gotoxy(0,0);    
        lcd_puts(sbuf);
        delay_ms(500);
    };
}
