#include <mega128.h>
#include <delay.h>

unsigned char buff = 0x01;  // LED 초기 점등값

interrupt [TIM0_OVF] void timer0_ovf_isr(void) // 오버플로 인터럽트 발생 서브루틴
{
    PORTE = buff; 
    if(buff == 0x80)
        buff = 0x01;
    else
        buff <<= 1;
}

void initial(void)     // -------- TIMER0, PORT 초기화 함수
{
    TCCR0 = 0x07;     // Normal Mode, OC0 출력 없음, 프리스케일러 1024
    TCNT0 = 0;
    TIMSK = 0x01;     // TIMER0 오버플로 인터럽트 인에이블

    PORTE = 0xff;
    DDRE = 0xff;
    SREG = 0x80;     // Grobal 인터럽트 인에이블
}

void main(void)
{
    initial();         // 타이머0, 포트 초기화
    while(1)
        delay_ms(1);
}
