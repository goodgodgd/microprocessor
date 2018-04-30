#include <mega128.h> 
#include <delay.h>
#include <stdio.h>
#asm
.equ __lcd_port=0x15 ;         // PORTC
#endasm
#include <lcd.h>

#define ADC_VREF_TYPE   0x00
char sbuf[16];              // LCD ����� ����

void MPUinit(void)
{
    DDRA=0xff;  PORTA=0xff;     // ��ƮA : ���ܼ� LED 
    DDRC=0xff;  PORTC=0xff;     // ��ƮC : LCD 
    DDRF=0x00; PORTF = 0x00;    // ��ƮF : (A/D �Է�)
    // ADC initialization
    ADMUX=ADC_VREF_TYPE;        // 0x00: AREF�� ���� �������� ���
	ADCSRA=0x86; 		        // 64���� , 250kHz
	lcd_init(16); 		        // LCD module initialization
}

unsigned int read_adc(unsigned char adc_input) //----- A/D ��ȯ �� ��� ��� �Լ� ----
{
	ADMUX=adc_input|ADC_VREF_TYPE; 
	ADCSRA|=0x40;	                // Start the AD conversion				
	while ((ADCSRA & 0x10)==0); 	// Wait for the AD conversion to complete
	ADCSRA|=0x10; 
	return ADCW;    // (int)ADCL + ((int)ADCH << 8);
}

void ReadSensor(int* adcout) //---- ���� ���� A/D��ȯ ó�� �Լ� ----------
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
    int AData[4];   // A/D��ȯ�� �������� ����� ����
    MPUinit();
    while (1)
    {
        ReadSensor(AData); 		// ���� ���� A/D��ȯ ó��
        sprintf(sbuf,"%03d, %03d", AData[0], AData[1]); 	// 3�� ���� A/D��ȯ�� ǥ��
        lcd_gotoxy(0,0);	
        lcd_puts(sbuf);
        sprintf(sbuf,"%03d, %03d", AData[2], AData[3]); 	// 3�� ���� A/D��ȯ�� ǥ��
        lcd_gotoxy(1,0);	
        lcd_puts(sbuf);
    };
}

