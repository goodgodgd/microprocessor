#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA |= 0x01;
	while(1)
	{
		
		PORTA |= 0x01;
		_delay_ms(500);
		PORTA &= ~0x01;
		_delay_ms(500);
	}
	return 0;
}
