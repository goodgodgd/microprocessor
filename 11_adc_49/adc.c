#include <mega128.h> 
#include <delay.h>
#include <stdio.h>
#asm
.equ __lcd_port=0x15 ;         // PORTC
#endasm
#include <lcd.h>

#define ADC_VREF_TYPE   0x00
char sbuf[16];              // LCD 출력할 문자

void MPUinit(void)
{
    DDRA=0xff;  PORTA=0xff;     // 포트A : 적외선 LED 
    DDRC=0xff;  PORTC=0xff;     // 포트C : LCD 
    DDRF=0x00; PORTF = 0x00;    // 포트F : (A/D 입력)
    // ADC initialization
    ADMUX=ADC_VREF_TYPE;        // 0x00: AREF를 기준 전압으로 사용
	ADCSRA=0x86; 		        // 64분주 , 250kHz
	lcd_init(16); 		        // LCD module initialization
}

unsigned int read_adc(unsigned char adc_input) //----- A/D 변환 후 결과 출력 함수 ----
{
	ADMUX=adc_input|ADC_VREF_TYPE; 
	ADCSRA|=0x40;	                // Start the AD conversion				
	while ((ADCSRA & 0x10)==0); 	// Wait for the AD conversion to complete
	ADCSRA|=0x10; 
	return ADCW;    // (int)ADCL + ((int)ADCH << 8);
}

void ReadSensor(int* adcout) //---- 라인 감지 A/D변환 처리 함수 ----------
{
    unsigned char fire = 0x01;
    int i;
    for(i=0; i<4; i++)
    {
        PORTA = fire;
        fire <<= 1;
        delay_us(30);
        adcout[i] = read_adc(3);
        PORTA = 0x00;
        delay_us(1000);
    }
}

void main(void)
{
    int AData[4];   // A/D변환된 센서값이 저장될 변수
    MPUinit();
    while (1)
    {
        ReadSensor(AData); 		// 라인 감지 A/D변환 처리
        sprintf(sbuf,"%03d, %03d", AData[0], AData[1]); 	// 3번 센서 A/D변환값 표시
        lcd_gotoxy(0,0);	
        lcd_puts(sbuf);
        sprintf(sbuf,"%03d, %03d", AData[2], AData[3]); 	// 3번 센서 A/D변환값 표시
        lcd_gotoxy(1,0);	
        lcd_puts(sbuf);
    };
}

