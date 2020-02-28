#include <mega128.h>
#include <stdio.h>
#include <delay.h>

#asm
.equ __lcd_port=0x1b
#endasm
#include <lcd.h>

#define ADC_VREF_TYPE 0x40
char sbuf[60];

unsigned int read_adc(unsigned char adc_input) // Read the AD conversion result
{
    ADMUX=adc_input|ADC_VREF_TYPE;
    ADCSRA|=0x40;              // Set ADSC to start the ADC
    while ((ADCSRA & 0x10)==0);           // Wait until ADIF becomes 1
    ADCSRA|=0x10;                              // Clear ADIF by writing 1 on it
    return ADCW;
}

void main(void)
{
    int adc_value;
    float distance;         // 거리값 저장 변수
    float voltage;        // 전압값 저장 변수
    PORTF = 0x00; DDRF = 0x00;
    ADMUX=ADC_VREF_TYPE; // ADC 초기화 : 125.000 kHz, AREF pin
    ADCSRA=0x87;
    lcd_init(16);
    while(1)
    {
        adc_value = read_adc(1);
        voltage = adc_value * 5.f / 1024.f; 	           // 전압 값 계산
        distance = 9.06 / (voltage*voltage) - 6.63*voltage + 27.3;   // 거리 계산
        lcd_clear();
        delay_ms(1);
        sprintf(sbuf, "Dist = %d", (int)(distance*100.f)); 	   // LCD : “Dist = 거리” 출력
        lcd_gotoxy(0,0);
        lcd_puts(sbuf); 		
        sprintf(sbuf, "ADC = %d", adc_value);            // LCD : “ADC = 전압 ” 출력
        lcd_gotoxy(0,1); 
        lcd_puts(sbuf); 
        delay_ms(100);
    }                                            
    
    
    
}
