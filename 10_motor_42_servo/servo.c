#include <mega128.h>
#include <delay.h>

#define RIGHT   125     // -90
#define MIDDLE  187     // 0
#define LEFT    250     // 90

void SetupPWM(void)
{
    PORTB = 0x00;
    DDRB = 0xff;    // DDR 설정 해야 출력 나옴
	TCCR1A = 0x23;  // 위상교정 PWM (모드 11), OC1B 정상파 출력 
	TCCR1B = 0x13;	// 64분주
	OCR1AH = 0x09;  OCR1AL = 0xC4;  // 20ms = 2500 count 
	OCR1BH = 0x00;  OCR1BL = RIGHT; // 오른쪽으로 초기화
}

void main(void)
{
    SetupPWM();
    while(1)
    {
        OCR1BH = 0;  OCR1BL = RIGHT;
        delay_ms(2000);
        OCR1BH = 0;  OCR1BL = MIDDLE;
        delay_ms(2000);
        OCR1BH = 0;  OCR1BL = LEFT;
        delay_ms(2000);
        OCR1BH = 0;  OCR1BL = MIDDLE;
        delay_ms(2000);
    }
}
