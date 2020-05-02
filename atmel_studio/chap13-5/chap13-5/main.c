#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	// 파형 출력 핀인 OC0(PB4) 핀을 출력으로 설정
	DDRB = 0x10;
	PORTB = 0x00;				// LED는 끈 상태에서 시작
	// 분주비를 1024로 설정
	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
	TCCR0 |= (1 << WGM01);		// CTC 모드
	// 비교일치 발생 시 OC0 핀의 출력을 반전
	TCCR0 |= (1 << COM00);
	OCR0 = 255;					// 비교일치 기준값
	
	while(1){ }
	return 0;
}