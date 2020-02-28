#include <mega128.h>
#include <delay.h>

void initial(void) // ---- TIMER0, PORT �ʱ�ȭ �Լ�
{
    TCCR0 = 0x1f;   // 00011111 CTC���, ������, 1024 ����
    TCNT0 = 0; 
    OCR0 = 255;
    PORTB = 0xff;  DDRB = 0xff;
}

void main(void) //------------- �����Լ� 
{
    initial();      // Ÿ�̸�0, ��Ʈ �ʱ�ȭ
    SREG = 0x80;    // Global ���ͷ�Ʈ �ο��̺�
	while(1)
        delay_ms(1);
}
