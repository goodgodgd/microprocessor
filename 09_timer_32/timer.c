#include <mega128.h>
#include <delay.h>

// FND Data    ��0'    '1'     ��2'     '3'     '4'      '5'     '6'     '7'     '8'      '9��
unsigned char fnd[10]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x98};
int fndnum, count=0, cycle=50;

interrupt [TIM2_OVF] void timer2_ovf_isr(void)
{
    count++;
    if(count == cycle) {    // 4ms*50 =200ms ���� ���� �ø�
        count=0;
        fndnum++;
    }
    switch(count%4) {       // 4���� ���ڸ� ���ư��鼭 ���
    case 0:
        PORTA = fnd[fndnum/1000];       // fndnum�� õ ���� �� ��� FND3 �� ���� 
        PORTB = 0b11111110;
        break;
    case 1:
        PORTA = fnd[fndnum%1000/100];   // fndnum�� �� ���� �� ��� FND2 �� ���� 
        PORTB = 0b11111101;
        break;
    case 2:
        PORTA = fnd[fndnum%100/10];     // fndnum�� �� ���� �� ��� FND1 �� ����
        PORTB = 0b11111011;
        break;
    case 3:
        PORTA = fnd[fndnum%10/1];       // fndnum �� �� ���� �� ��� FND0 �� ����
        PORTB = 0b11110111;
        break;
    }
}

void initial(void)
{
    TCCR2 = 0x04;   // Normal mode, OC�� ��� ����, Ŭ���� 256 ����
    TIMSK = 0x40;   // TIMER2 �����÷� ���ͷ�Ʈ �ο��̺�
    TCNT2 = 0x00;
    PORTA = 0xff; DDRA = 0xff;  // FND ���׸�Ʈ
    PORTB = 0x00; DDRB = 0xff;  // FND select 
    PORTD = 0xff; DDRD = 0xff;  // LED
}

void main(void) // ------- ����
{
    initial();      // Ÿ�̸�0, ��Ʈ �ʱ�ȭ
    SREG = 0x80;    // Global ���ͷ�Ʈ �ο��̺�
    while(1)        // LED ���� (FND ���۴� �����ϰ� ���۵��� �˼� �ִ�.)
    {            
        PORTD = 0xf0;         // 1111 0000
        delay_ms(500);
        PORTD = 0x0f;         // 0000 1111
        delay_ms(500); 
    }
}
