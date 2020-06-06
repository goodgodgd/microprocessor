#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "Text_LCD.h"
uint8_t MODE = 4;
char msg[16];

void UART1_init(void)
{
	UBRR1H = 0x00;			// 9600 보율로 설정
	UBRR1L = 103;
	// 비동기, 8비트 데이터, 패리티 없음, 1비트 정지 비트 모드
	UCSR1C |= 0x06;
	UCSR1B |= _BV(RXEN1);	// 송수신 가능
	UCSR1B |= _BV(TXEN1);
	UCSR1B |= _BV(RXCIE1);	// 수신 인터럽트 활성화
	sei();
}

void UART1_transmit(char data)
{
	while( !(UCSR1A & (1 << UDRE1)) )	// 송신 가능 대기
		;
	UDR1 = data;						// 데이터 전송
}

void UART1_print_string(char *str)		// 문자열 송신
{
	for(int i = 0; str[i]; i++)			// ‘\0’ 문자를 만날 때까지 반복
		UART1_transmit(str[i]);			// 바이트 단위 출력
}

void print_string(char* msg)
{
	LCD_clear();
	LCD_goto_XY(0, 0);
	LCD_write_string(msg);
	UART1_print_string(msg);
}

ISR(USART1_RX_vect)
{
	char data;
	if(UCSR1A & (1<<RXC1))
	{
		data = (char)UDR1;
		sprintf(msg, "Rx:%c\n", data);
		print_string(msg);
	}
}

int main(void)
{
	int count = 0;
	UART1_init();		// UART 통신 초기화
	LCD_init();
	while (1)
	{
		count++;
		sprintf(msg, "count:%d\n", count);
		print_string(msg);
		_delay_ms(1000);
	}
	return 0;
}
