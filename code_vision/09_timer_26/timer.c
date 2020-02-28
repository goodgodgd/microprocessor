#include <mega128.h>
#include <delay.h>

unsigned char buff = 0x01;  // LED �ʱ� ���
int tcnt =0;                // ���ͷ�Ʈ �߻� Ƚ���� ī��Ʈ

interrupt [TIM0_OVF] void timer0_ovf_isr(void) // �����÷� ���ͷ�Ʈ �߻� �����ƾ
{
    tcnt +=1;               // ���ͷ�Ʈ �߻� Ƚ�� ī��Ʈ ����
    if(tcnt == 610)         // 1000mSec? 
    { 
        PORTE = buff; 
        if(buff == 0x80)
            buff = 0x01;
        else
            buff <<= 1;
        tcnt = 0;
    } 
}

void initial(void) 	// -------- TIMER0, PORT �ʱ�ȭ �Լ�
{
	TCCR0 = 0x05; 	// Normal Mode, OC0 ��� ����, ���������Ϸ� 128
	TCNT0 = 0;
	TIMSK = 0x01; 	// TIMER0 �����÷� ���ͷ�Ʈ �ο��̺�

	PORTE = 0xff;
	DDRE = 0xff;
	SREG = 0x80; 	// Grobal ���ͷ�Ʈ �ο��̺�
}

void main(void)
{
	initial(); 		// Ÿ�̸�0, ��Ʈ �ʱ�ȭ
	while(1)
        delay_ms(1);
}
