#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define OCR_MAX		255
unsigned char read_switch(unsigned char sw_id);
void control_motor(float vel_ratio, int dir);

int main(void)
{
	DDRC = 0x00;	// PC0, PC1 입력
	DDRE = 0xFF;	// PE0, PE1, PE4 출력
	PORTE = 0x00;
	// OC3B로 비반전파 출력, 8비트 Fast PWM 모드: WGM3X(3~0): 0101
	TCCR3A |= (1 << COM3B1) | (1 << WGM30);
	// 분주비 64: CS3X(2~0): 011
	TCCR3B |= (1 << WGM32) | (1 << CS31) | (1 << CS30);
	OCR3B = 0;
    while (1) {
		if(read_switch(0))
			control_motor(0.7f, 1);
		if(read_switch(1))
			control_motor(0.3f, -1);
		if(read_switch(2))
			control_motor(0.f, 0);
		_delay_ms(50);
    }
}

unsigned char read_switch(unsigned char sw_id)
{
	static unsigned char pin_bef = 0xff;
	unsigned char sw_bef = pin_bef & (1 << sw_id);
	unsigned char sw_cur = PINC & (1 << sw_id);
	// 이전 스위치 값을 비트 단위로 저장
	pin_bef = (pin_bef & ~(1 << sw_id)) | sw_cur;
	
	if(sw_bef > 0 && sw_cur == 0)
	{
		_delay_ms(10);
		sw_cur = PINC & (1 << sw_id);
		if(sw_cur == 0)
		return 1;
	}
	return 0;
}

void control_motor(float vel_ratio, int dir)
{
	OCR3B = (int)(OCR_MAX * vel_ratio);
	if(dir > 0)
	{
		PORTE |= 0x01;		// IN1 = 1
		PORTE &= ~0x02;		// IN2 = 0
	}
	else if(dir < 0)
	{
		PORTE &= ~0x01;		// IN1 = 0
		PORTE |= 0x02;		// IN2 = 1
	}
	else
	{
		PORTE &= ~0x01;		// IN1 = 0
		PORTE &= ~0x02;		// IN2 = 0
	}
}


