#include <mega128.h>
#include <delay.h>

void main(void)
{
    // (����) c���� ���� ������ ���漱�� �ؾ���
    // c99 ���ķ� ���� �����Ϸ��� ���漱�� ������ ������ avr compiler�� ������ ����� ���� ������ ����� ��
    unsigned char last = 0x80;
    unsigned char buff = last;    // 1000 0000

    PORTE = 0x00;
    DDRE = 0xff;
        
    while (1)
    {
        if(buff == last)    // 7�� LED���� ��������
            buff = 0x01;    // buff �� �ʱ� ������ͷ�
        else                // �ƴϸ� ���� ������� �غ�
        {
            buff = buff<<1;  // 1 bit shift left
            buff = buff&0xfe;// 0�� ��Ʈ�� "1"�� ���� (0�� LED��) 
	    }
        
        PORTE = buff;       // LED �� buff : LED����
        delay_ms(500);
	}
}
