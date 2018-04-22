#include <mega128.h>
#include <delay.h>

void initial(void) // TIMER2, PORT 초기화 함수
{
    TCCR2 = 0x6c;   // 01101100  고속PWM, 256분주
    TCNT2 = 0; 
    PORTB = 0x00;
    DDRB = 0xff; // OC2 = PB7
}

void main(void)
{
    initial();                 // 타이머0, 포트 초기화
    while(1)
    {
        OCR2 =0;    delay_ms(1000);     // duty 0% 
        OCR2 =63;   delay_ms(1000);     // duty 25%
        OCR2 =127;  delay_ms(1000);     // duty 50% 
        OCR2 =191;  delay_ms(1000);     // duty 75% 
        OCR2 =255; 	delay_ms(1000); 	// duty 100%
	}
}
