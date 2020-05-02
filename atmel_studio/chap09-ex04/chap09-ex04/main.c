#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define STRING_LEN	3

void UART1_init(void)
{
	UBRR1H = 0x00;			// 9600 보율로 설정
	UBRR1L = 103;
	// 비동기, 8비트 데이터, 패리티 없음, 1비트 정지 비트 모드
	UCSR1C |= 0x06;
	UCSR1B |= _BV(RXEN1);	// 송수신 가능
	UCSR1B |= _BV(TXEN1);
}

void UART1_transmit(char data)
{
	while( !(UCSR1A & (1 << UDRE1)) )	// 송신 가능 대기
		;
	UDR1 = data;						// 데이터 전송
}

unsigned char is_UART1_received(void)
{
	return (UCSR1A & (1<<RXC1));		// 데이터 수신 확인
}

void UART1_print_string(char *str)		// 문자열 송신
{
	for(int i = 0; str[i]; i++)			// ‘\0’ 문자를 만날 때까지 반복
		UART1_transmit(str[i]);			// 바이트 단위 출력
}

int main(void)
{
	UART1_init();				// UART1 초기화
	char buffer[STRING_LEN+1];	// 3글자 + '\0'
	int count = 0;
	while(1)
	{
		if(is_UART1_received())
		{
			if(count < STRING_LEN)
				buffer[count] = UDR1;
			count++;
			if(count == STRING_LEN)
			{
				buffer[count] = '\0';
				UART1_print_string(buffer);
				count = 0;
			}
		}
	}
	return 0;
}
