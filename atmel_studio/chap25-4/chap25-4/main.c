#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Text_LCD.h"

#define  PRESCALER 1024		// 분주비
uint8_t MODE = 4;			// LCD 4-bit mode

void Timer_init(void)
{
	// 16비트 타이머 1번 타이머/카운터 분주비를 1024로 설정
	TCCR1B |= (1 << CS12) | (1 << CS10);
}

int measure_distance(void)
{
	// 트리거 핀으로 펄스 출력
	PORTC &= ~(1 << PC1);		// LOW 값 출력
	_delay_us(1);
	PORTC |= (1 << PC1);		// HIGH 값 출력
	_delay_us(10);				// 10 마이크로초 대기
	PORTC &= ~(1 << PC1);		// LOW 값 출력
	
	// 에코 핀이 HIGH가 될 때까지 대기
	TCNT1 = 0;
	while(!(PINC & 0x01))
		if(TCNT1 > 65000)		// 장애물이 없는 경우
			return 0;

	// 에코 핀이 LOW가 될 때까지의 시간 측정
	TCNT1 = 0;					// 카운터를 0으로 초기화
	while(PINC & 0x01) {
		if(TCNT1 > 650000)		// 측정 불가능
			return 0;
	}
	// 에코 핀의 펄스 폭을 마이크로초 단위로 계산
	double pulse_width = 1000000.0 * TCNT1 * PRESCALER / F_CPU;
	return (int)(pulse_width / 58);		// 센티미터 단위 거리 반환
}

void print_LCD(int distance)
{
	static char data[10];
	LCD_clear();
	LCD_goto_XY(0, 0);
	sprintf(data, "distance: %d", distance);
	LCD_write_string(data);
}

int main(void)
{
	int distance;
	DDRC |= 0x02;			// PC1, 트리거 핀 출력으로 설정
	DDRC &= 0xFE;			// PC0, 에코 핀 입력으로 설정
	LCD_init();				// LCD 초기화
	Timer_init();			// 1번 타이머/카운터 활성화
	
	while(1)
	{
		distance = measure_distance();	// 거리 측정
		print_LCD(distance);			// LCD로 거리출력
		_delay_ms(500);
	}
	return 0;
}
