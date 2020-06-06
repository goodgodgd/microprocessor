#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

unsigned char read_switch(unsigned char sw_id)
{
	static unsigned char sw_bef = 1;
	unsigned char sw_cur = PINC & (1 << sw_id);
	if(sw_bef > 0 && sw_cur == 0)
	{
		_delay_ms(10);
		sw_cur = PINC & (1 << sw_id);
		sw_bef = sw_cur;
		if(sw_cur == 0)
			return 1;
	}
	sw_bef = sw_cur;
	return 0;
}

int main(void)
{
	DDRE = 0xff;
	DDRC = 0x00;
	int a = 0;
    while (1) 
    {
		if(read_switch(0))
		{
			if (a==1)	a=0;
			else a=1;
			PORTE = a;
		}
		_delay_ms(10);
    }
}

