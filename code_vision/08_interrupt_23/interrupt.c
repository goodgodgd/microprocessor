#include <mega128.h>
#include <delay.h>

unsigned char Int0_test=0;

interrupt [EXT_INT0] void ext_int0_isr(void) // INT0 ���ͷ�Ʈ ���� ��ƾ
{
    EIMSK = 0x00;          // Interrupt Disable
    Int0_test++;    
    delay_ms(500); 
    EIMSK = 0x01;         // Interrupt Enable
}

void init_port(void)
{
    PORTE = 0xff;         // LED PORT 
    DDRE = 0xff; 
    
    PORTD = 0xff;         // PD.0 : INT0
    DDRD = 0x00;
}

void main(void)
{
	init_port();
			        // ���ͷ�Ʈ �ʱ�ȭ
	EICRA = 0x02; 	// 00000010 : INT1,INT0 �ϰ����� ���� 
	EIMSK = 0x01; 	// INT0 �ο��̺�
	SREG = 0x80 ; 	// = #asm("sei")  :  Global enable interrupts

    while(1)
    {
        PORTE = Int0_test; // LED OUT
        delay_ms(1);
    }
}
