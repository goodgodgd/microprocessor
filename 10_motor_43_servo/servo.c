#include <mega128.h>
#include <delay.h>

#define RIGHT   125     // -90
#define MIDDLE  187     // 0
#define LEFT    250     // 90

void SetupPWM(void)
{
    PORTC = 0x00;
    DDRC = 0x00; 
    PORTB = 0x00;
    DDRB = 0xff;    // DDR 설정 해야 출력 나옴
    TCCR1A = 0x23;  // 위상교정 PWM (모드 11), OC1B 정상파 출력 
    TCCR1B = 0x13;    // 64분주
    OCR1AH = 0x09;  OCR1AL = 0xC4;      // 20ms = 2500 count 
    OCR1BH = 0x00;  OCR1BL = MIDDLE;    // 가운데로 초기화
}

void main(void)
{
    unsigned char buff = 0;
    SetupPWM();
    while(1)
    {
        buff = PINC & 0x03;
        switch(buff)
        {
        case 0x02:      // SW0을 눌렀을 때
            OCR1BH = 0; OCR1BL = LEFT;
            break;
        case 0x01:      // SW1을 눌렀을 때
            OCR1BH = 0; OCR1BL = RIGHT;
            break;
        default:
            break;
        }
    }
}
