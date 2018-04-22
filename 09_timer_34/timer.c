#include <mega128.h>
#include <delay.h>

void initial(void)    // ---- TIMER, PORT �ʱ�ȭ �Լ�
{
    DDRB = 0xFF;   PORTB = 0x00;    // ��Ʈ B�� �ʱⰪ ���
    TCCR1A = 0xA3;            // 10bit ������ PWM, (��� 3)
    TCCR1B = 0x03;            // 64����
    OCR1AH = 0x00;  OCR1AL = 0x00;        // �ʱ� ��Ƽ�� = 0; 
    OCR1BH = 0x00;  OCR1BL = 0x00;
}
void main(void)
{ 
    initial();
    while(1)
    {
        OCR1AH = 0x00;   OCR1AL = 0xFF;    // ��Ƽ�� = 25% 
        OCR1BH = 0x01;   OCR1BL = 0xFF;    // ��Ƽ�� = 50% 
        delay_ms(2000);
        OCR1AH = 0x01;   OCR1AL = 0xFF;    // 50% 
        OCR1BH = 0x03;   OCR1BL = 0xFF;    // 100% 
        delay_ms(2000);
        OCR1AH = 0x03;   OCR1AL = 0xFF;    // 100% 
        OCR1BH = 0x00;   OCR1BL = 0xFF;    // 25% 
        delay_ms(2000);
	}
}

