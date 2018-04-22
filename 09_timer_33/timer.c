#include <mega128.h>
#include <delay.h>

unsigned char led = 0x01; 
unsigned int time = 0x8000;   // ī��Ʈ ���� ��, �ֱ� = 0xffff - 0x8000 + 1 = 32786 Ŭ��

interrupt [TIM1_OVF] void timer_int1(void)    // Ÿ�̸�/ī����1 �����÷ο� ���� ��ƾ
{                  // (1/16)us * 32768 * 256���� = 524ms
    led <<= 1;     // LED ���� ����
    if(led == 0x00) led = 0x01;
    PORTE = led;
    TCNT1 = time; 
}

void initial(void)        // ---- TIMER1, PORT �ʱ�ȭ �Լ�
{
    DDRE = 0xFF;    // ��Ʈ C ������� ����
    PORTE = led;    // ��Ʈ C�� �ʱⰪ ���              
	// ���ͷ�Ʈ �ʱ�ȭ
	TIMSK = 0x04;	// TOIE1 = 1, TIMER1  �����÷ο� ���ͷ�Ʈ �ο��̺�
    TCCR1A = 0x00;	// ��� 0(�Ϲݸ��)
	TCCR1B = 0x04;	// ���������� = CK/256
	TCCR1C = 0x00;
	TCNT1 = time;	// Ÿ�̸�/ī����1 �������� �ʱⰪ: 16 ��Ʈ 
}

void main(void)
{                 
	initial();
	SREG = 0x80;	// ���� ���ͷ�Ʈ �ο��̺� ��Ʈ I ��.	
	while(1)		// ���� ����
        delay_ms(1);
}
