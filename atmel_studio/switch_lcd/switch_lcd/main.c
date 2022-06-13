#define F_CPU	16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Text_LCD.h"

/*
8개의 풀업 스위치(PORT C) 입력을 받아서
각 스위치(PORT E)에 해당하는 LED를 켜고
스위치 번호를 LCD에 출력하는 프로젝트
*/
typedef unsigned char uchar;
uint8_t MODE = 4;

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

int main(void)
{
	// 포트 입출력 설정 및 출력 값 초기화
	DDRC = 0x00;	// switch
	DDRE = 0xFF;	// LED
	DDRA = 0xFF;	// LCD
	PORTC = 0x00;
	PORTE = 0x00;
	
	LCD_init();
	char string[17];	// LCD 한 줄 16칸 + NULL
	
	while (1)
	{
		// 스위치 8개를 모두 검사하여 가장 최근에 눌린 스위치에 해당하는 LED 하나만 켠다
		for(uchar i=0; i<8; i++)
		{
			if(read_switch_array(i))
			{
				PORTE = (1 << i);
				// sprintf: 숫자를 문자로 변환
				sprintf(string, "switch: %d", i);
				LCD_clear();
				LCD_write_string(string);
			}
		}
	}
}
