#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

char circular_shift_left(char pattern)
{
	return ( (pattern << 1) | (pattern >> 7) );
}

int main(void)
{
	DDRE = 0xFF;			// PORTB 핀을 모두 출력으로 설정
	DDRC &= ~0x04;			// PORTF의 PF2 핀을 입력으로 설정
	
	char pattern = 0x01;	// 초기 출력값
	PORTE = pattern;
	
	// 이전 및 현재 버튼의 상태
	char state_previous = 1, state_current;
	
	while (1)
	{
		state_current = (PINC & 0x04) >> 2;	// 버튼 상태 읽기
		// 버튼이 눌러지지 않은 상태에서 눌러진 상태로 바뀌는 경우
		if(state_current == 0 && state_previous == 1){
			_delay_ms(30);			// 디바운스
			pattern = circular_shift_left(pattern);
			PORTE = pattern;
		}
		state_previous = state_current;	// 버튼 상태 업데이트
	}

	return 0;
}
