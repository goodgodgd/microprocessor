// include headers
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define NO_SWITCH	100

// 7-segment 숫자 패턴 배열 선언
uint8_t numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};

// 포트 입출력 설정 및 포트 출력 초기화
void init_ports()
{
	// PORTC: 스위치, PORTB: 7-segment
	DDRC = 0x00;
	DDRB = 0xff;
	PORTC = 0x00;
	PORTB = 0x00;
}

// 스위치 읽는 함수
uint8_t read_switch()
{
	static uint8_t prv = 0xff;
	uint8_t cur = PINC;
	if(prv != 0xff || cur == 0xff)
		return NO_SWITCH;
	
	for(uint8_t i=0; i<8; i++)
	{
		if((cur & (1<<i)) == 0)
		{
			_delay_ms(20);
			if((cur & (1<<i)) == 0)
				return i;
		}
	}
	return NO_SWITCH;
}

int main(void)
{
	init_ports();
	uint8_t sw;
	// 입력 스위치에 해당하는 7-segment 숫자 출력
	while(1)
	{
		_delay_ms(10);
		sw = read_switch();
		if(sw == NO_SWITCH)
			continue;
		
		PORTB = numbers[sw];
	}
}

