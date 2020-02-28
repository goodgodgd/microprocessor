#include <mega128.h>
#include <delay.h>

#define SW0 PINC.0       // ����� ����. ��PINC�� ǥ���� ��SW�� ǥ������ ��ġ�Ѵ�.
#define SW1 PINC.1
#define SW2 PINC.2 

// FND Data  '0'      '1'     ��2'     '3'     '4'     '5'     '6'     '7'     '8'     '9' 
unsigned char fnd[10]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x98};
int count = 0;

void UpCnt(void)    // --- ���� ī��Ʈ �Լ� ------
{
    count++;        // ī���Ͱ� +1 ����
    if(count > 9)        // ī���Ͱ� 9 ���� ǥ�� �Ǿ����� �̻��̸� �ٽ� 0 ���� 
        count = 0;
}
void DownCnt(void)    // --- ���� ī��Ʈ �Լ�--------
{
    count--;        // ī���Ͱ� -1 ����
    if(count < 0)        // ī���Ͱ� 0 ���� ǥ�� �Ǿ����� �̸� �ٽ� 9 ���� 
	    count = 9;
}

void main(void)
{
    PORTB=0xFF; DDRB=0xFF;
    PORTC=0xFF; DDRC=0x00; 
    PORTB = ~fnd[0];

    while(1)
    { 
        if(SW0 == 0)		// ����ġ SW0 ON?
        {
            delay_ms(1); 		// ä�͸� ������ ���� �ణ �ð�����.
            while(SW0 != 1) 		// OFF �� �� ���� ��� 
            { 
                delay_ms(1);
            }
            UpCnt();
            PORTB = ~fnd[count]; 	// ī���Ͱ� FND ���
        }
        if(SW1 == 0)		// ����ġ SW1 ON?
        { 
            delay_ms(1); 
            while(SW1 != 1) 		// OFF �� �� ���� ��� 
                delay_ms(1);
            DownCnt();
            PORTB = ~fnd[count]; 	// ī���Ͱ� FND ���
        }
        if(SW2 == 0) 		// ����ġ SW2 ON?
        {
            delay_ms(1); 
            while(SW2 != 1) 		// OFF �� �� ���� ��� 
                delay_ms(1);
            count = 0;		// ī��Ʈ�� �ʱ�ȭ
            PORTB = ~fnd[count]; 
        }
    }  //  while �� ��
}
