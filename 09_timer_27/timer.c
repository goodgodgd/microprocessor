#include <mega128.h>
#include <delay.h>

unsigned char count;            // 인터럽트 발생 횟수 저장용

interrupt [TIM0_COMP] void timer0_comp_isr(void) // 비교일치 인터럽트 서브루틴
{
    count++;
    if (count == 250)        // 인터럽트가 250회 발생했는가? (= 1초?)
    {
        PORTE ^= 0xff;         // XOR - 반전 출력 
        count = 0;        // count값 초기화
    } 
}

void initial(void) // ---------- 초기화 함수
{
    PORTE = 0xff;
    DDRE = 0xff;    // led
	TCCR0 = 0x0E;   // 0000 1110: CTC모드, OC0 출력없음, 256분주
	TCNT0 = 0x00;	// 0부터 카운트
	OCR0 = 249;	    // 16MHz/256분주/(249+1) = 250Hz 
			        //(1초에 250회 OC int.발생)
	TIMSK = 0x02;	// OC 인터럽트 활성화
}

void main(void) //------------- 메인함수 
{
	initial(); 		// 타이머0, 포트 초기화
	PORTA = 0xff; 	// LED off 
	SREG = 0x80; 	// Grobal 인터럽트 인에이블 
	while(1)
        delay_ms(1);
}
