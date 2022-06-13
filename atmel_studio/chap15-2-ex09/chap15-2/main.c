#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int dim = 780; 				// 현재 LED 밝기
	DDRE |= (1 << PE4);
	// 11번 모드
	TCCR3A |= (1 << WGM31) | (1 << WGM30);
	TCCR3B |= (1 << WGM33);
	// 비반전 모드
	TCCR3A |= (1 << COM3B1);
	// 분주비를 1024로 설정
	TCCR3B |= (1 << CS32) | (1 << CS30);
	OCR3A = 7800;
	while(1)
	{
		OCR3B = dim;
		_delay_ms(1000);
		dim += 1560;			// 밝기 변화
		if(dim > 7800)
			dim = 0;
	}
	return 0;
}
