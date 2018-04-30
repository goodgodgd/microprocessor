#include <mega128.h>
#include <delay.h>

// FND Data    ‘0'    '1'     ‘2'     '3'     '4'      '5'     '6'     '7'     '8'      '9’
unsigned char fnd[10]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x98};
int fndnum, count=0, cycle=50;

interrupt [TIM2_OVF] void timer2_ovf_isr(void)
{
    count++;
    if(count == cycle) {    // 4ms*50 =200ms 마다 숫자 올림
        count=0;
        fndnum++;
    }
    switch(count%4) {       // 4개의 숫자를 돌아가면서 출력
    case 0:
        PORTA = fnd[fndnum/1000];       // fndnum값 천 단위 수 계산 FND3 만 점등 
        PORTB = 0b11111110;
        break;
    case 1:
        PORTA = fnd[fndnum%1000/100];   // fndnum값 백 단위 수 계산 FND2 만 점등 
        PORTB = 0b11111101;
        break;
    case 2:
        PORTA = fnd[fndnum%100/10];     // fndnum값 십 단위 수 계산 FND1 만 점등
        PORTB = 0b11111011;
        break;
    case 3:
        PORTA = fnd[fndnum%10/1];       // fndnum 값 일 단위 수 계산 FND0 만 점등
        PORTB = 0b11110111;
        break;
    }
}

void initial(void)
{
    TCCR2 = 0x04;   // Normal mode, OC핀 출력 없음, 클록을 256 분주
    TIMSK = 0x40;   // TIMER2 오버플로 인터럽트 인에이블
    TCNT2 = 0x00;
    PORTA = 0xff; DDRA = 0xff;  // FND 세그멘트
    PORTB = 0x00; DDRB = 0xff;  // FND select 
    PORTD = 0xff; DDRD = 0xff;  // LED
}

void main(void) // ------- 메인
{
    initial();      // 타이머0, 포트 초기화
    SREG = 0x80;    // Global 인터럽트 인에이블
    while(1)        // LED 점멸 (FND 동작는 무관하게 동작됨을 알수 있다.)
    {            
        PORTD = 0xf0;         // 1111 0000
        delay_ms(500);
        PORTD = 0x0f;         // 0000 1111
        delay_ms(500); 
    }
}
