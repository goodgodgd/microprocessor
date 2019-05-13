#include <mega128.h>    
#include <delay.h>

unsigned char *ptr;
char String[] = "Welcome to ATmega128\r\n";

void Initial(void) // ------ 초기화 함수 ------
{
    PORTE= 0xff;
    DDRE = 0xfe;    
    UCSR0A = 0x00;
    UCSR0B = 0xb8;        // UDR Empty 인터럽트 허가
    UCSR0C = 0x06;        // No parity, 1 stop bit, 8bit data
    UBRR0H = 0;
    UBRR0L = 103;         // 9600bps
}

interrupt [USART0_DRE] void usart0_transmit(void) // -- UDR Empty 인터럽트 --
{
    UDR0 = *ptr;    // 현재 포인터 위치의 문자 출력
    ptr++;          // 포인터 위치 한칸 이동
    if(*ptr==0)     // 문자열 끝에 도달하면 다시 처음으로 이동
        ptr = String;
}

void main(void)
{
    Initial();
    #asm("sei"); 		// Global enable interrupts
    ptr = String;		// 문자열의 선두 주소 값 저장
    while(1)
        delay_ms(1);
}
