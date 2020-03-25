#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

char circular_shift_right(char pattern)
{
	char LSB = pattern & 0x01;
	char MSB = LSB << 7;
	char new_pattern = pattern >> 1;
	new_pattern |= MSB;
	return new_pattern;
}

int main(void)
{
	char pattern = 0xA0;
	DDRE = 0xFF;
	while(1)
	{
		PORTE = pattern;
		pattern = circular_shift_right(pattern);
		_delay_ms(500);
	}
	return 0;
}
