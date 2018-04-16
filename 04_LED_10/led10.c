#include <mega128.h>
#include <delay.h>
void left_shift(void) ;        // SW0 �� ON �� �� ���� ����Ʈ ó�� �Լ� ��������
void right_shift(void);        // SW1 �� ON �� �� ������ ����Ʈ ó�� �Լ� �������� 

int LL=0x01;         // Left Shift LED �ʱ� ���� ������ 0b00000001 
int RR=0x80;         // Right Shift LED �ʱ� ���� ������ 0b10000000

void main(void)        // -------- ���� �Լ� ------------
{
    PORTE = 0x00; DDRE = 0xff;     
    PORTC = 0xff; DDRC = 0x00;
    while(1)
    {
        if(PINC.0 == 0)         // SW0 �� ON�̸� ���ʽ���Ʈ �Լ� ����
            left_shift();
        else if (PINC.1 == 0)   // SW1�� ON�̸� ������ �ý�Ʈ �Լ� ����
            right_shift();
    }
} 

void left_shift(void)    //----SW1 �� ON �� �� ���� ����Ʈ ó�� �Լ� ------
{
	do{
	    PORTE = LL; 		// ���� ����Ʈ LED �ʱⰪ ��� 
	    delay_ms(200);
	    if (LL == 0x80)     // ������ LED ON �Ǿ����� �ٽ� �ʱⰪ���� 
		    LL=0x01; 
	    else 			    // �ƴϸ� 1 bit �� ����Ʈ 
		    LL <<= 1;
	} while((PINC.0 != 0)&&(PINC.1 != 0)); 
    // SW �ϳ��� ON �� �ƴϸ� ��� ����
}

void right_shift(void)      //--SW 2 �� ON �� ���� ������ ����Ʈ ó�� �Լ� ----
{
	do{ 
	    PORTE = RR; 	    // ������ ����Ʈ LED �ʱⰪ ��� 
	    delay_ms(200);
	    if (RR == 0x01) 
		    RR=0x80; 		// ������ LED ON �Ǿ����� �ٽ� �ʱⰪ���� 
	    else 			    // �ƴϸ� 1 bit �� ����Ʈ 
	 	    RR >>= 1; 
	} while((PINC.0 != 0)&&(PINC.1 != 0));
} 
