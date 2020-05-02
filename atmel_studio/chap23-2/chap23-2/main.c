#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define ROTATION_DELAY 	1000	// 1초 대기
#define PULSE_MIN		1300	// 최소 펄스 길이
#define PULSE_MID		3000
#define PULSE_MAX		4700	// 최대 펄스 길이

void InitializeTimer1(void)
{
	// 모드 15, 고속 PWM 모드
	TCCR1A |= (1 << WGM11) | (1 << WGM10);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	// OC1B 비반전 펄스 출력, TOP: OCR1A
	TCCR1A |= (1 << COM1B1);
	TCCR1B |= (1 << CS11);		// 분주율 8, 2MHz
	OCR1A = 39999;				// 20ms 주기
}

int main(void)
{
	// 모터 제어 핀 (OC1B)을 출력으로 설정
	DDRB |= (1 << PB6);
	InitializeTimer1();			// 1번 타이머/카운터 설정
	
	while(1)
	{
		OCR1B = PULSE_MIN;		// 0도
		_delay_ms(ROTATION_DELAY);
		
		OCR1B = PULSE_MID;		// 90도
		_delay_ms(ROTATION_DELAY);
		
		OCR1B = PULSE_MAX;		// 180도
		_delay_ms(ROTATION_DELAY);
	}
	return 0;
}