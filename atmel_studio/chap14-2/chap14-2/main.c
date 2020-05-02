#include <avr/io.h>
#include <avr/interrupt.h>

int state = 0;

// 256(분주비) * 32,767(OCR1A) / 16,000,000 = 0.524s 마다 실행
ISR(TIMER1_COMPA_vect)
{
	state = (state + 1)%2;	// LED 상태 반전
	PORTB = state;			// 포트로 상태 출력
	//TCNT1 = 0;			// CTC모드에서는 비교일치에서 TCNT1가 0이 됨
}

int main(void)
{
	DDRB = 0x01;			// PB0 핀을 출력으로 설정
	PORTB = 0x00;			// LED는 끈 상태에서 시작
	OCR1A = 0x7FFF;			// 비교일치 값 설정
	// CTC모드, 분주비를 256으로 설정
	TCCR1B |= (1 << WGM12) | (1 << CS12);
	TIMSK |= (1 << OCIE1A);	// 비교일치 A 인터럽트 허용
	sei();					// 전역적으로 인터럽트 허용
	
	while(1){ }
	return 0;
}
