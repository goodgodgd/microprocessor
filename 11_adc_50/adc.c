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
    float distance;         // �Ÿ��� ���� ����
    float voltage;        // ���а� ���� ����
    PORTF = 0x00; DDRF = 0x00;
    ADMUX=ADC_VREF_TYPE; // ADC �ʱ�ȭ : 125.000 kHz, AREF pin
    ADCSRA=0x87;
    lcd_init(16);
    while(1)
    {
        adc_value = read_adc(1);
        voltage = adc_value * 5.f / 1024.f; 	           // ���� �� ���
        distance = 9.06 / (voltage*voltage) - 6.63*voltage + 27.3;   // �Ÿ� ���
        lcd_clear();
        delay_ms(1);
        sprintf(sbuf, "Dist = %d", (int)(distance*100.f)); 	   // LCD : ��Dist = �Ÿ��� ���
        lcd_gotoxy(0,0);
        lcd_puts(sbuf); 		
        sprintf(sbuf, "ADC = %d", adc_value);            // LCD : ��ADC = ���� �� ���
        lcd_gotoxy(0,1); 
        lcd_puts(sbuf); 
        delay_ms(100);
    }                                            
    
    
    
}
