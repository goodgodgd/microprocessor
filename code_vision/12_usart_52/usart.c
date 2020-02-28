#include <mega128.h>	
#include <delay.h>

void Initial(void) 		// ---------- �ʱ�ȭ �Լ� ------------------
{
	PORTE = 0xff;
	DDRE = 0xfe;	
    UCSR0A = 0x00;
    UCSR0B = 0x18;        // USART Enable
    UCSR0C = 0x06;        // No parity, 1 stop bit, 8bit data
    UBRR0H = 0;
    UBRR0L = 103;         // 9600bps
}

void TxChar(unsigned char chr)    // ------ �ѹ��� �����Լ� --------
{
    while((UCSR0A & 0x20) == 0) // UDRE0�� 1�� �ɶ����� ��ٸ�
        delay_us(10);
    UDR0 = chr;
}

void TxString(unsigned char *str) // ------ ���ڿ� �����Լ� --------
{
    int i =0;
    while(str[i] != 0) 		// ���ڿ� ���� NULL ���� ��0�� ���� �� ���� ����
    {	
        TxChar(str[i]); 
        i++;
    }
}

void main(void) 	// ========== >>> ���� �Լ� <<< ========
{
    char message[] = "Welcome to ATmega128\r\n";
    PORTB = 0xff; DDRB = 0xff;
    Initial();
    TxChar(0x0d);   // '\r' carriage return ASCII �ڵ�: ù ���� �̵�
    TxChar(0x0a); 	// '\n' line feed ASCII �ڵ�: �ٹٲ�
    while(1)
    {
        TxString(message);
        delay_ms(500);
        PORTB ^= 0xff;
    }
}
