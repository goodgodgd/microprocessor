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
    DDRB = 0xff;    // DDR ���� �ؾ� ��� ����
    TCCR1A = 0x23;  // ������ PWM (��� 11), OC1B ������ ��� 
    TCCR1B = 0x13;    // 64����
    OCR1AH = 0x09;  OCR1AL = 0xC4;      // 20ms = 2500 count 
    OCR1BH = 0x00;  OCR1BL = MIDDLE;    // ����� �ʱ�ȭ
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
        case 0x02:      // SW0�� ������ ��
            OCR1BH = 0; OCR1BL = LEFT;
            break;
        case 0x01:      // SW1�� ������ ��
            OCR1BH = 0; OCR1BL = RIGHT;
            break;
        default:
            break;
        }
    }
}
