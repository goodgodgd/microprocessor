#include <mega128.h>	// ATmega128 �������
#include <delay.h>		// �ð����� �������
void main(void)
{
	PORTE=0x00;		// Port A �ʱⰪ 
	DDRE=0xFF;		// Port A ����, ������� ���
	while(1) 			// ���� �ݺ� ��ƾ
	{
	 	PORTE = 0xf0;	//PORTE�� 1111 0000 �� ���
	 	delay_ms(500);	// �ð� ���� �Լ�- 0.5��
	 	PORTE = 0x0f;	//PORTE�� 0000 1111 �� ���
	 	delay_ms(500);	// �ð� ���� �Լ� - 0.5��
	}
}
