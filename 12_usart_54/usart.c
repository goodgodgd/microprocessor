#include <mega128.h>
#include <delay.h>
#include <stdio.h>

#asm
.equ __lcd_port=0x1b;   // PORTA
#endasm
#include <lcd.h>

#define PARITY_ERROR        (1<<2)
#define DATA_OVERRUN        (1<<3)
#define FRAMING_ERROR       (1<<4)
#define DATA_REGISTER_EMPTY (1<<5)
#define RX_COMPLETE         (1<<7)
#define INVALID_DATA        0

char TryRxChar(void)  // USART0에 문자가 수신되면 데이터를 리턴하고 아니면 -1 리턴
{
    if((UCSR0A & (RX_COMPLETE | FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN)) == RX_COMPLETE)
        return (char)UDR0;
    else
        return INVALID_DATA;
}

void TxChar(char c) // USART0로 문자 송신
{
    while((UCSR0A & DATA_REGISTER_EMPTY)==0) //  UDR 이 비워질 때까지 대기
        delay_us(10);
    UDR0=c;
}

void init(void)		// 포트, USART0, LCD 초기화
{
    PORTA = 0x00; DDRA = 0x00;
    PORTE = 0xff; DDRE = 0xfe; // 0-bit는 Rx
    UCSR0A = 0x00;
    UCSR0B = 0x18;  // Rx/Tx enable	
    UCSR0C = 0x06;  // 8-bit communication
    UBRR0H = 0x00;
    UBRR0L = 0x67;	// baud rate: 9600 bps
    lcd_init(16);	// LCD module initialization
}

void main(void)	//-------------- 메인 함수 ----------
{
    char rx_data;
    char sbuf[16];
    init();
    lcd_putsf("Waiting for data"); 
    while (1)
    {
        rx_data = TryRxChar();    // 수신 데이터가 준비되면 읽어서 리턴
        delay_us(10);
        if(rx_data == INVALID_DATA)
              continue;
        TxChar(rx_data); 		    //받은 데이터 송출
        lcd_clear();
        sprintf(sbuf, "Rx data : %c", rx_data); // LCD 표시
        lcd_gotoxy(0,0);
        lcd_puts(sbuf);
    }
}
