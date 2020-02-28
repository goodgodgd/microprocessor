#include <mega128.h>    
#include <delay.h>

int i;
char String[] = "Welcome to ATmega128\r\n";

void Initial(void) // ------ �ʱ�ȭ �Լ� ------
{
    PORTE= 0xff;
    DDRE = 0xfe;    
    UCSR0A = 0x00;
    UCSR0B = 0xb8;        // UDR Empty ���ͷ�Ʈ �㰡
    UCSR0C = 0x06;        // No parity, 1 stop bit, 8bit data
    UBRR0H = 0;
    UBRR0L = 103;         // 9600bps
}

interrupt [USART0_DRE] void usart0_transmit(void) // UDR Empty ���ͷ�Ʈ
{
    UDR0 = (uchar)String[i];    // ���� �ϳ��� �۽�
    i++;
    if(String[i]==0)     // ���ڿ� ���� �����ϸ� �ٽ� ó������ �̵�
        i = 0;
}

void main(void)
{
    i=0;
    Initial();
    #asm("sei"); 		// Global enable interrupts
    while(1)
        delay_ms(1);
}
