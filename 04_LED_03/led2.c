#include <mega128.h>	// ATmega128 �������
#include <delay.h>		// �ð����� �������

void main(void)
{	
	PORTE = 0xff;		// Port A �ʱⰪ 
	DDRE = 0xff;		// Port A �������.
	PORTC = 0xff;		// Port C �ʱⰪ 
	DDRC = 0x00;		// Port C �Է�����.
	
	while(1) // ���� �ݺ�
	{
	    if(PINC.0 == 0)		// SW0 ON ?
		    PORTE = 0x00;	// LED ��� ���� 
	    else if(PINC.1 == 0)// SW1 ON?
	       	PORTE = 0xff;	// LED ��� ��		 
	}
}
