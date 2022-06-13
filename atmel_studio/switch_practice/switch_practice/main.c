#define F_CPU	16000000L
#include <avr/io.h>
#include <util/delay.h>
/*
8개의 풀업 스위치(PORT C) 입력을 받아서
각 스위치(PORT E)에 해당하는 LED를 켜는 프로젝트
*/
typedef unsigned char uchar;

uchar read_switch_array(uchar sw_id)
{
	static uchar state_prev[] = {1, 1, 1, 1, 1, 1, 1, 1};
	// sw_id 버튼의 현재 상태 읽기
	uchar state_curr = (PINC >> sw_id) & 0x01;
	uchar result = 0;
	// 1: 안눌림, 0: 눌림, 스위치가 눌리기 시작했을 때 (하강에지)
	if(state_curr == 0 && state_prev[sw_id] == 1)
	{
		_delay_ms(20);		// 디바운스
		state_curr = (PINC >> sw_id) & 0x01;
		if(state_curr == 0)	// 스위치 눌림 한번 더 확인
			result = 1;
	}
	// 현재 상태를 과거 상태에 저장
	state_prev[sw_id] = state_curr;
	return result;
}

uchar read_switch_bitwise(uchar sw_id)
{
	static uchar state_prev = 0xFF;
	uchar state_curr = PINC;
	// sw_id 버튼의 과거와 현재 상태 읽기
	uchar result = 0;
	// 1: 안눌림, 0: 눌림, 스위치가 눌리기 시작했을 때 (하강에지)
	if((state_prev & (1 << sw_id)) != 0 && (state_curr & (1 << sw_id)) == 0)
	{
		_delay_ms(20);		// 디바운스
		if((PINC & (1 << sw_id)) == 0)	// 스위치 눌림 한번 더 확인
			result = 1;
	}
	// 현재 상태를 과거 상태에 저장
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
		// i번째 스위치가 눌리기 시작했을 때
		if(((state_prev & (1 << i)) != 0) && ((state_curr & (1 << i)) == 0))
		{
			_delay_ms(20);
			if((PINC & (1 << i)) == 0)
				result |= (1 << i);		// 결과를 i번째 비트에 저장
		}
	}
	// 현재 상태를 과거 상태에 저장
	state_prev = state_curr;
	return result;
}


int main(void)
{
	// 포트 입출력 설정 및 출력 값 초기화
	DDRC = 0x00;
	DDRE = 0xFF;
	PORTC = 0x00;
	PORTE = 0x00;
    while (1) 
    {
		// 스위치 8개를 모두 검사하여 가장 최근에 눌린 스위치에 해당하는 LED 하나만 켠다
		for(uchar i=0; i<8; i++)
		{
			// 방법 1: 이전 스위치 상태를 배열에 저장하고 현재 상태를 스위치 하나씩 확인
			//if(read_switch_array(i))
				//PORTE = (1 << i);
			// 방법 2: 이전 스위치 상태를 비트에 저장하고 현재 상태를 스위치 하나씩 확인
			if(read_switch_bitwise(i))
				PORTE = (1 << i);
		}
		continue;
		
		// 방법 3: 이전 스위치 상태를 비트에 저장하고 현재 상태를 비트에 담아 한꺼번에 확인
		uchar result = read_switch_all();
		for(uchar i=0; i<8; i++)
		{
			if(result & (1 << i))
				PORTE = (1 << i);
		}
    }
}
