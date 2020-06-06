#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define C4		262 // 261.63 Hz
#define D4		294 // 293.66 Hz
#define E4		330 // 329.63 Hz
#define F4		349 // 349.23 Hz
#define G4		392 // 392.00 Hz
#define A4		440 // 440.00 Hz
#define B4		494 // 493.88 Hz
#define C5		523 // 523.25 Hz
#define PRESCALER 	8

const int notes[] = {C4, D4, E4, F4, G4, A4, B4, C5};

void init_music()
{
	DDRB |= (1 << PB6); 			// PBB 핀(OC1B 핀)을 출력으로 설정
	DDRC = 0;
	PORTC = 0xff;
	
	// COM1Bn = 01 : 비교일치 발생 시 출력 반전
	TCCR1A |= _BV(COM1B0);
	// WGM1n = 0100 : 4번 CTC 모드
	// CS1n = 010 : 분주비 8
	TCCR1B |= _BV(WGM12) | _BV(CS11);
}

int main()
{
	init_music();				// 포트 및 타이머 설정
	int ocr_val = 0;
	while(1)
	{
		ocr_val = 0;
		for(int i=0; i<8; i++)
		{
			if((PINC & (1<<i)) == 0)
				ocr_val = F_CPU / 2 / PRESCALER / notes[i];
		}
		OCR1A = ocr_val;
		_delay_ms(10);
	}
	return 0;
}
