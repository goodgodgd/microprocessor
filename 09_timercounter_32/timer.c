#include <mega128.h>
#include <delay.h>

unsigned char fnd[10]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x98};
int fndnum, count=0, cycle=50;

interrupt [TIM2_OVF] void timer2_ovf_isr(void)
{
    count++;
    if(count == cycle) {        // 4ms*50 = 200ms ���� ���� �ø�
        count=0;
        fndnum++;
    }
    
    switch(count%4) {          // 4���� ���ڸ� ���ư��鼭 ���
    case 0:
        PORTB = ~fnd[fndnum/1000];       // fndnum�� õ ���� �� ��� FND3 �� ���� 
        PORTE = (PORTE&0xf0) + 0b00001110;  break;
    case 1:
        PORTB = ~fnd[fndnum%1000/100];   // fndnum�� �� ���� �� ��� FND2 �� ���� 
        PORTE = (PORTE&0xf0) + 0b00001101;  break;
    case 2:
        PORTB = ~fnd[fndnum%100/10];     // fndnum�� �� ���� �� ��� FND1 �� ����
        PORTE = (PORTE&0xf0) + 0b00001011;  break;
    case 3:
        PORTB = ~fnd[fndnum%10/1];       // fndnum �� �� ���� �� ��� FND0 �� ����
        PORTE = (PORTE&0xf0) + 0b00000111;  break;
    }
}

void initial(void)
{
    TCCR2 = 0x04; 		// normal mode, Ŭ�� 256 ����, 4ms ���� overflow
    TIMSK = 0x40; 		// TIMER2 �����÷� ���ͷ�Ʈ �ο��̺�
    TCNT2 = 0x00;
    PORTB = 0xff;   DDRB = 0xff;    // FND ���׸�Ʈ
    PORTE = 0x00;   DDRE = 0xff;    // 0~4: FND select, 7: LED  
    SREG = 0x80; 		// Global ���ͷ�Ʈ �ο��̺�
}

void main(void)
{
    initial(); 		// Ÿ�̸�0, ��Ʈ �ʱ�ȭ
    while(1)        // LED ����: FND ���۴� �����ϰ� ����
    {			
        PORTE |= 0x80;  // PORTE 7�� ��Ʈ ON
        delay_ms(500);
        PORTE &= 0x7f;  // PORTE 7�� ��Ʈ OFF
        delay_ms(500); 
    }
}
