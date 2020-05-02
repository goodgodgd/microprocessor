#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Text_LCD.h"

uint8_t MODE = 4;	// LCD 4-bit mode

void ADC_init(unsigned char channel)
{
	ADMUX |= (1 << REFS0); 		// AVCC를 기준 전압으로 선택
	
	ADCSRA |= 0x07;				// 분주비 설정
	ADCSRA |= (1 << ADEN);		// ADC 활성화
	ADCSRA |= (1 << ADFR);		// free running 모드

	ADMUX = ((ADMUX & 0xE0) | channel);	// 채널 선택
	ADCSRA |= (1 << ADSC);		// 변환 시작
}

int read_ADC(void)
{
	while(!(ADCSRA & (1 << ADIF)));	// 변환 종료 대기
	
	return ADC;				// 10비트 값을 반환
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
	LCD_init();				// UART 통신 초기화
	ADC_init(1);			// AD 변환기 초기화, 입력채널 ADC1 (PF1)
	DDRE = 0xFF;			// 포트E를 출력으로 설정
	
	while(1)
	{
		read = read_ADC();		// 가변저항 값 읽기
		uint8_t pattern = 0;	// LED 제어값
		int LED_count = (read >> 7) + 1;	// 켜질 LED의 개수
		for(int i = 0; i < LED_count; i++) 	// LED 제어값 생성
			pattern |= (0x01 << i);

		PORTE = pattern;		// LED 켜기
		print_LCD(read);		// LCD 출력
		_delay_ms(500);
	}

	return 0;
}