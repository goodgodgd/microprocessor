#include <mega128.h>	
#include <delay.h>

void Initial(void) 		// ---------- 초기화 함수 ------------------
{
	PORTE = 0xff;
	DDRE = 0xfe;	
    UCSR0A = 0x00;
    UCSR0B = 0x18;        // USART Enable
    UCSR0C = 0x06;        // No parity, 1 stop bit, 8bit data
    UBRR0H = 0;
    UBRR0L = 103;         // 9600bps
}

void TxChar(unsigned char chr)    // ------ 한문자 전송함수 --------
{
    while((UCSR0A & 0x20) == 0) // UDRE0가 1이 될때까지 기다림
        delay_us(10);
    UDR0 = chr;
}

void TxString(unsigned char *str) // ------ 문자열 전송함수 --------
{
    int i =0;
    while(str[i] != 0) 		// 문자열 끝에 NULL 문자 “0” 검출 때 까지 전송
    {	
        TxChar(str[i]); 
        i++;
    }
}

void main(void) 	// ========== >>> 메인 함수 <<< ========
{
    char message[] = "Welcome to ATmega128\r\n";
    PORTB = 0xff; DDRB = 0xff;
    Initial();
    TxChar(0x0d);   // '\r' carriage return ASCII 코드: 첫 열로 이동
    TxChar(0x0a); 	// '\n' line feed ASCII 코드: 줄바꿈
    while(1)
    {
        TxString(message);
        delay_ms(500);
        PORTB ^= 0xff;
    }
}
