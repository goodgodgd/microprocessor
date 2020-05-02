#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRB = 0x20;			// PB5(OC1A) 핀을 출력으로 설정
	PORTB = 0x00;			// LED는 끈 상태에서 시작
	OCR1A = 0x7FFF;			// 비교일치 값 설정
	// CTC모드, 분주비를 256으로 설정
	TCCR1B |= (1 << WGM12) | (1 << CS12);
	// 비교일치 발생 시 OC1A 핀의 출력을 반전
	TCCR1A |= (1 << COM1A0);
	
	while(1){ }
	return 0;
}

