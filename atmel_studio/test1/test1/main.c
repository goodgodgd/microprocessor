#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	uint8_t number[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x67,0x72
	,0x7D,0x39,0x3E,0x79,0x71};
	
	int count = 0;
	DDRB = 0xFF;
	
	while(1)
	{
		PORTB = number[count];
		count = (count + 1) % 16;
		
		_delay_ms(500);
	}
	
	return 0;
}