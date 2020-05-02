#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Text_LCD.h"

uint8_t MODE = 4;	// LCD 4-bit mode

void ADC_init(unsigned char channel)
{
	ADMUX |= (1 << REFS0); 		// AVCC를 기준 전압으로 선택
	ADMUX = ((ADMUX & 0xE0) | channel);	// 채널 선택
	
	ADCSRA |= 0x07;				// 분주비 설정
	ADCSRA |= (1 << ADEN);		// ADC 활성화
	ADCSRA |= (1 << ADFR);		// 프리 러닝 모드

	ADCSRA |= (1 << ADSC);		// 변환 시작
}

int read_ADC(void)
{
	while(!(ADCSRA & (1 << ADIF)))	// 변환 종료 대기
		;
	return ADC;					// 10비트 값을 반환
}

void print_LCD(int read)
{
	static char data[10];
	LCD_clear();
	LCD_goto_XY(0, 0);
	sprintf(data, "adc: %d", read);
	LCD_write_string(data);
}

int main(void)
{
	int read;	
	LCD_init();			// LCD 초기화
	ADC_init(0);		// AD 변환기 초기화
	
	while(1)
	{
		read = read_ADC();			// 가변저항 값 읽기
		print_LCD(read);
		_delay_ms(1000);			// 1초에 한 번 읽음
	}
	return 0;
}
