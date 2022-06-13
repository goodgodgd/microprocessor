#define F_CPU	16000000L
#include <avr/io.h>
#include <util/delay.h>
/*
8���� Ǯ�� ����ġ(PORT C) �Է��� �޾Ƽ�
�� ����ġ(PORT E)�� �ش��ϴ� LED�� �Ѵ� ������Ʈ
*/
typedef unsigned char uchar;

uchar read_switch_array(uchar sw_id)
{
	static uchar state_prev[] = {1, 1, 1, 1, 1, 1, 1, 1};
	// sw_id ��ư�� ���� ���� �б�
	uchar state_curr = (PINC >> sw_id) & 0x01;
	uchar result = 0;
	// 1: �ȴ���, 0: ����, ����ġ�� ������ �������� �� (�ϰ�����)
	if(state_curr == 0 && state_prev[sw_id] == 1)
	{
		_delay_ms(20);		// ��ٿ
		state_curr = (PINC >> sw_id) & 0x01;
		if(state_curr == 0)	// ����ġ ���� �ѹ� �� Ȯ��
			result = 1;
	}
	// ���� ���¸� ���� ���¿� ����
	state_prev[sw_id] = state_curr;
	return result;
}

uchar read_switch_bitwise(uchar sw_id)
{
	static uchar state_prev = 0xFF;
	uchar state_curr = PINC;
	// sw_id ��ư�� ���ſ� ���� ���� �б�
	uchar result = 0;
	// 1: �ȴ���, 0: ����, ����ġ�� ������ �������� �� (�ϰ�����)
	if((state_prev & (1 << sw_id)) != 0 && (state_curr & (1 << sw_id)) == 0)
	{
		_delay_ms(20);		// ��ٿ
		if((PINC & (1 << sw_id)) == 0)	// ����ġ ���� �ѹ� �� Ȯ��
			result = 1;
	}
	// ���� ���¸� ���� ���¿� ����
	state_prev = state_curr;
	return result;
}

uchar read_switch_all()
{
	static uchar state_prev = 0xFF;
	uchar state_curr = PINC;
	uchar result = 0;
	for(int i=0; i<8; i++)
	{
		// i��° ����ġ�� ������ �������� ��
		if(((state_prev & (1 << i)) != 0) && ((state_curr & (1 << i)) == 0))
		{
			_delay_ms(20);
			if((PINC & (1 << i)) == 0)
				result |= (1 << i);		// ����� i��° ��Ʈ�� ����
		}
	}
	// ���� ���¸� ���� ���¿� ����
	state_prev = state_curr;
	return result;
}


int main(void)
{
	// ��Ʈ ����� ���� �� ��� �� �ʱ�ȭ
	DDRC = 0x00;
	DDRE = 0xFF;
	PORTC = 0x00;
	PORTE = 0x00;
    while (1) 
    {
		// ����ġ 8���� ��� �˻��Ͽ� ���� �ֱٿ� ���� ����ġ�� �ش��ϴ� LED �ϳ��� �Ҵ�
		for(uchar i=0; i<8; i++)
		{
			// ��� 1: ���� ����ġ ���¸� �迭�� �����ϰ� ���� ���¸� ����ġ �ϳ��� Ȯ��
			//if(read_switch_array(i))
				//PORTE = (1 << i);
			// ��� 2: ���� ����ġ ���¸� ��Ʈ�� �����ϰ� ���� ���¸� ����ġ �ϳ��� Ȯ��
			if(read_switch_bitwise(i))
				PORTE = (1 << i);
		}
		continue;
		
		// ��� 3: ���� ����ġ ���¸� ��Ʈ�� �����ϰ� ���� ���¸� ��Ʈ�� ��� �Ѳ����� Ȯ��
		uchar result = read_switch_all();
		for(uchar i=0; i<8; i++)
		{
			if(result & (1 << i))
				PORTE = (1 << i);
		}
    }
}
