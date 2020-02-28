#include <mega128.h>
#include <delay.h>

void STEP_M_CW();       // STEP Motor CW ���� �Լ�
void STEP_M_CCW();      // STEP Motor CCW ���� �Լ�
void STEP_M_STOP();     // STEP Motor STOP�Լ�

unsigned Step[4] = {0x01, 0x02, 0x04, 0x08};    // ���� ����
int i;

void main(void)
{
    unsigned char buff0;
    PORTC=0xff;            // Port C : ����ġ �Է�
    DDRC=0x00;
    PORTA=0xff;            // Port A : ���� ���ڽ�ȣ ��� 
    DDRA=0xff;
    
    while (1)
    {
        buff0 = PINC & 0x03;    // ����ġ ����
        switch(buff0)
        {
        case 0x02:			    // SW0�� ������
            STEP_M_CW();		// STEP Motor CW ����
            break;
        case 0x01:			    // SW1�� ������
            STEP_M_CCW();		// STEP Motor CCW ����
            break;
        default:			    // default���̸�
            STEP_M_STOP();		// ����ġ�� �������� ������ ����
            break;
        }
    }
}

void STEP_M_CW()		// ��ȸ�� �Լ� - 4���ܾ� �����Ѵ�.
{
    for(i=0; i<=3; i++)
    {
        PORTA = Step[i];
        delay_ms(5);
    }
}

void STEP_M_CCW()		// ��ȸ�� �Լ� - 4���ܾ� �����Ѵ�.
{
    for(i=3; i>=0; i--)
    {
        PORTA = Step[i];
        delay_ms(5);
    }
}

void STEP_M_STOP()
{
    PORTA = 0x00;		
}
