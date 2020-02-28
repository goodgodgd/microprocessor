#include <mega128.h>
#include <delay.h>

unsigned char led = 0x01; 
unsigned int time = 0x8000;   // 카운트 시작 값, 주기 = 0xffff - 0x8000 + 1 = 32786 클럭

interrupt [TIM1_OVF] void timer_int1(void)    // 타이머/카운터1 오버플로우 서비스 루틴
{                  // (1/16)us * 32768 * 256분주 = 524ms
    led <<= 1;     // LED 순차 점멸
    if(led == 0x00) led = 0x01;
    PORTE = led;
    TCNT1 = time; 
}

void initial(void)        // ---- TIMER1, PORT 초기화 함수
{
    DDRE = 0xFF;    // 포트 C 출력으로 설정
    PORTE = led;    // 포트 C에 초기값 출력              
	// 인터럽트 초기화
	TIMSK = 0x04;	// TOIE1 = 1, TIMER1  오버플로우 인터럽트 인에이블
    TCCR1A = 0x00;	// 모드 0(일반모드)
	TCCR1B = 0x04;	// 프리스케일 = CK/256
	TCCR1C = 0x00;
	TCNT1 = time;	// 타이머/카운터1 레지스터 초기값: 16 비트 
}

void main(void)
{                 
	initial();
	SREG = 0x80;	// 전역 인터럽트 인에이블 비트 I 셋.	
	while(1)		// 무한 루프
        delay_ms(1);
}
