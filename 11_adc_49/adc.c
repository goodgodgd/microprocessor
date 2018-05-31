#include <mega128.h> 
#include <delay.h>
#include <stdio.h>
#asm
.equ __lcd_port=0x1B;       // PORTA
#endasm
#include <lcd.h>

#define ADC_VREF_TYPE   0x40    // AVCC를 기준 전압으로 사용
char sbuf[16];              // LCD 출력할 문자

void MPUinit(void)
{
    PORTA=0xff; DDRA=0xff;  // PORTA : LCD 
    PORTC=0xff; DDRC=0xff;  // PORTC : 적외선 LED 
    PORTE=0x00; DDRE=0xff;  // PORTE : 일반 LED출력
    PORTF=0x00; DDRF=0x00;  // PORTF : (A/D 입력)
    // ADC initialization
    ADMUX=ADC_VREF_TYPE;
	ADCSRA=0x86; 		        // 64분주 , 250kHz
}

void ReadAdc(int* adc_out) //---- 라인 감지 A/D변환 처리 함수 ----------
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
    int AData[4] = {0,0,0,0};   // A/D 변환된 센서값이 저장될 변수
    MPUinit();
    lcd_init(16);
    
    while (1)
    {
        ReadAdc(AData); 		// 라인 감지 A/D변환 처리
        
        sprintf(sbuf,"%4d, %4d", AData[0], AData[1]); 	// 0,1번 센서 A/D변환값 표시
        lcd_gotoxy(0,0);	
        lcd_puts(sbuf);
        delay_ms(1);
        
        sprintf(sbuf,"%4d, %4d", AData[2], AData[3]); 	// 2,3번 센서 A/D변환값 표시
        lcd_gotoxy(0,1);	
        lcd_puts(sbuf);
        delay_ms(20);
    };
}
