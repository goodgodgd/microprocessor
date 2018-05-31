#include <mega128.h> 
#include <delay.h>
#include <stdio.h>
#asm
.equ __lcd_port=0x1B;       // PORTA
#endasm
#include <lcd.h>

#define ADC_VREF_TYPE   0x40// AVCC를 기준 전압으로 사용
char sbuf[16];              // LCD 출력할 문자

void MPUinit(void)
{
    PORTA=0xff; DDRA=0xff;  // PORTA : LCD 
    PORTC=0xff; DDRC=0xff;  // PORTC : 적외선 LED 
    PORTF=0x00; DDRF=0x00;  // PORTF : (A/D 입력)
    // ADC initialization
    ADMUX=ADC_VREF_TYPE;
    ADCSRA=0x86;                 // 64분주 , 250kHz
}

int ReadAdc(unsigned char pin_num) //---- 라인 감지 A/D변환 처리 함수 ----------
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
        ADdata = ReadAdc(1);    // ADC1에서 A/D 변환
        
        sprintf(sbuf,"ADC result:%4d", ADdata);
        lcd_gotoxy(0,0);    
        lcd_puts(sbuf);
        delay_ms(500);
    };
}
