#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

void UART_init(void);
void UART_transmit(char data);
unsigned char UART_receive(void);
void UART_print_string(char *str);

int main(void)
{
	UART_init();				// UART 초기화
	char test_str[] = "Test using UART Library: ";
	char number_str[4] = "0";
	uint8_t num = 0;
	while (1)
	{
		UART_print_string(test_str);			// 문자열 출력
		sprintf(number_str, "%d\n\r", num);
		UART_print_string(number_str);
		num++;
		_delay_ms(500);
	}
	return 0;
}

void UART_init(void)
{
	UBRR1H = 0x00;		// 9600 보율로 설정 (1배속)
	UBRR1L = 103;
	UCSR1A = 0x00;	// 1배속
	UCSR1C = 0x06;	// 비동기, 8비트 데이터, 패리티 없음, 1비트 정지 비트 모드
	UCSR1B = 0x18;	// 송수신 가능
}

void UART_transmit(char data)
{
	while( !(UCSR1A & (1 << UDRE1)) )	// 송신 가능 대기
		;
	UDR1 = data;				// 데이터 전송
}

unsigned char UART_receive(void)
{
	while( !(UCSR1A & (1<<RXC1)) )	// 데이터 수신 대기
		;
	return UDR1;
}

void UART_print_string(char *str)	// 문자열 송신
{
	for(int i = 0; str[i]; i++)			// ‘\0’ 문자를 만날 때까지 반복
		UART_transmit(str[i]);			// 바이트 단위 출력
}
