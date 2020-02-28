#include <mega128.h>
#include <delay.h>

unsigned char count;            // ���ͷ�Ʈ �߻� Ƚ�� �����

interrupt [TIM0_COMP] void timer0_comp_isr(void) // ����ġ ���ͷ�Ʈ �����ƾ
{
    count++;
    if (count == 250)        // ���ͷ�Ʈ�� 250ȸ �߻��ߴ°�? (= 1��?)
    {
        PORTE ^= 0xff;         // XOR - ���� ��� 
        count = 0;        // count�� �ʱ�ȭ
    } 
}

void initial(void) // ---------- �ʱ�ȭ �Լ�
{
    PORTE = 0xff;
    DDRE = 0xff;    // led
	TCCR0 = 0x0E;   // 0000 1110: CTC���, OC0 ��¾���, 256����
	TCNT0 = 0x00;	// 0���� ī��Ʈ
	OCR0 = 249;	    // 16MHz/256����/(249+1) = 250Hz 
			        //(1�ʿ� 250ȸ OC int.�߻�)
	TIMSK = 0x02;	// OC ���ͷ�Ʈ Ȱ��ȭ
}

void main(void) //------------- �����Լ� 
{
	initial(); 		// Ÿ�̸�0, ��Ʈ �ʱ�ȭ
	PORTA = 0xff; 	// LED off 
	SREG = 0x80; 	// Grobal ���ͷ�Ʈ �ο��̺� 
	while(1)
        delay_ms(1);
}
