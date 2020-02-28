#include <mega128.h>
#include <delay.h>

void initial(void) // ---- TIMER0, PORT 초기화 함수
{
    TCCR0 = 0x1f;   // 00011111 CTC모드, 출력토글, 1024 분주
    TCNT0 = 0; 
    OCR0 = 255;
    PORTB = 0xff;  DDRB = 0xff;
}

void main(void) //------------- 메인함수 
{
    initial();      // 타이머0, 포트 초기화
    SREG = 0x80;    // Global 인터럽트 인에이블
	while(1)
        delay_ms(1);
}
