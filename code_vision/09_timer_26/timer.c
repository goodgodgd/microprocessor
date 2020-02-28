#include <mega128.h>
#include <delay.h>

unsigned char buff = 0x01;  // LED 초기 점등값
int tcnt =0;                // 인터럽트 발생 횟수를 카운트

interrupt [TIM0_OVF] void timer0_ovf_isr(void) // 오버플로 인터럽트 발생 서브루틴
{
    tcnt +=1;               // 인터럽트 발생 횟수 카운트 증가
    if(tcnt == 610)         // 1000mSec? 
    { 
        PORTE = buff; 
        if(buff == 0x80)
            buff = 0x01;
        else
            buff <<= 1;
        tcnt = 0;
    } 
}

void initial(void) 	// -------- TIMER0, PORT 초기화 함수
{
	TCCR0 = 0x05; 	// Normal Mode, OC0 출력 없음, 프리스케일러 128
	TCNT0 = 0;
	TIMSK = 0x01; 	// TIMER0 오버플로 인터럽트 인에이블

	PORTE = 0xff;
	DDRE = 0xff;
	SREG = 0x80; 	// Grobal 인터럽트 인에이블
}

void main(void)
{
	initial(); 		// 타이머0, 포트 초기화
	while(1)
        delay_ms(1);
}
