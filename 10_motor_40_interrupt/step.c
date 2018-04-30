#include <mega128.h>
#include <delay.h>

unsigned char steps[4] = {0x03, 0x06, 0x0c, 0x09};  // 2�� ���� ���� ����
unsigned char buff;
int index = 0;

interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
    buff = PINC & 0x03;
    if(buff==0x02)  // SW0 �� ������ ��
    {
        PORTA = steps[index];
        index++;
        if(index>3)
            index = 0;
    }
    else if(buff==0x01)  // SW1 �� ������ ��
    {
        PORTA = steps[index];
        index--;
        if(index<0)
            index = 3;
    }
    else
        PORTA = 0x00;
}

void Setup()
{
    PORTA = 0x00;   DDRA = 0xff;    // step ��ȣ ���
    PORTC = 0x00;   DDRC = 0x00;    // ����ġ �Է�
    TCCR1A = 0x00;  TCCR1B = 0x0C;  // CTC 4�� ��忡�� ���ֺ� 256
    OCR1AH = 0x01;  OCR1AL = 0x38;  // OCR1A = 312
    TIMSK = 0x10;   // compare match 1A enable
    TCNT2 = 0x00;
    SREG = 0x80;    // Global ���ͷ�Ʈ �ο��̺�
}

void main(void)
{
    Setup();
    while(1)
        delay_ms(1000);
}
