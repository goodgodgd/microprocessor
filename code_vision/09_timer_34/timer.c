#include <mega128.h>
#include <delay.h>

void initial(void)    // ---- TIMER, PORT 초기화 함수
{
    DDRB = 0xFF;   PORTB = 0x00;    // 포트 B에 초기값 출력
    TCCR1A = 0xA3;            // 10bit 위상교정 PWM, (모드 3)
    TCCR1B = 0x03;            // 64분주
    OCR1AH = 0x00;  OCR1AL = 0x00;        // 초기 듀티비 = 0; 
    OCR1BH = 0x00;  OCR1BL = 0x00;
}
void main(void)
{ 
    initial();
    while(1)
    {
        OCR1AH = 0x00;   OCR1AL = 0xFF;    // 듀티비 = 25% 
        OCR1BH = 0x01;   OCR1BL = 0xFF;    // 듀티비 = 50% 
        delay_ms(2000);
        OCR1AH = 0x01;   OCR1AL = 0xFF;    // 50% 
        OCR1BH = 0x03;   OCR1BL = 0xFF;    // 100% 
        delay_ms(2000);
        OCR1AH = 0x03;   OCR1AL = 0xFF;    // 100% 
        OCR1BH = 0x00;   OCR1BL = 0xFF;    // 25% 
        delay_ms(2000);
	}
}

