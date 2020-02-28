#include <mega128.h>
#include <delay.h>

unsigned char fnd[10]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x98};
int fndnum, count=0, cycle=50;

interrupt [TIM2_OVF] void timer2_ovf_isr(void)
{
    count++;
    if(count == cycle) {        // 4ms*50 = 200ms 마다 숫자 올림
        count=0;
        fndnum++;
    }
    
    switch(count%4) {          // 4개의 숫자를 돌아가면서 출력
    case 0:
        PORTB = ~fnd[fndnum/1000];       // fndnum값 천 단위 수 계산 FND3 만 점등 
        PORTE = (PORTE&0xf0) + 0b00001110;  break;
    case 1:
        PORTB = ~fnd[fndnum%1000/100];   // fndnum값 백 단위 수 계산 FND2 만 점등 
        PORTE = (PORTE&0xf0) + 0b00001101;  break;
    case 2:
        PORTB = ~fnd[fndnum%100/10];     // fndnum값 십 단위 수 계산 FND1 만 점등
        PORTE = (PORTE&0xf0) + 0b00001011;  break;
    case 3:
        PORTB = ~fnd[fndnum%10/1];       // fndnum 값 일 단위 수 계산 FND0 만 점등
        PORTE = (PORTE&0xf0) + 0b00000111;  break;
    }
}

void initial(void)
{
    TCCR2 = 0x04; 		// normal mode, 클록 256 분주, 4ms 마다 overflow
    TIMSK = 0x40; 		// TIMER2 오버플로 인터럽트 인에이블
    TCNT2 = 0x00;
    PORTB = 0xff;   DDRB = 0xff;    // FND 세그멘트
    PORTE = 0x00;   DDRE = 0xff;    // 0~4: FND select, 7: LED  
    SREG = 0x80; 		// Global 인터럽트 인에이블
}

void main(void)
{
    initial(); 		// 타이머0, 포트 초기화
    while(1)        // LED 점멸: FND 동작는 무관하게 동작
    {			
        PORTE |= 0x80;  // PORTE 7번 비트 ON
        delay_ms(500);
        PORTE &= 0x7f;  // PORTE 7번 비트 OFF
        delay_ms(500); 
    }
}
