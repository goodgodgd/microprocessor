#include <mega128.h>
#include <delay.h>

void init_port(void); 	

interrupt [EXT_INT0] void ext_int0_isr(void) 	      // INT0 ���ͷ�Ʈ ó���Լ� 
{
	PORTB = 0b11110000;	
	delay_ms(1000); 
	PORTB = 0b00001111;	
	delay_ms(1000); 
} 

interrupt [EXT_INT5] void ext_int5_isr(void) 	      // INT5 ���ͷ�Ʈ ó���Լ� 
{
	PORTB = 0b11000011;	
	delay_ms(1000); 
	PORTB = 0b00111100;	
	delay_ms(1000); 
}

void init_port(void)
{
    PORTB=0xff;   DDRB=0xff;        // LED
    PORTD=0xff;   DDRD=0x00;
    PORTE=0xff;   DDRD=0x00;
}
	
void main(void)
{
	init_port();
				// ���ͷ�Ʈ �ʱ�ȭ
	EICRA =0x02; 		// 00000010 : INT0 �ϰ����� ���� 
	EICRB =0x08; 		// 00001000 : INT5 �ϰ����� ���� 
	EIMSK = 0x21; 		// 00100001 : INT5,INT0 �ο��̺�
	#asm("sei"); 		// Global enable interrupts
	while(1)
	{
	 	PORTB = 0b00000000;	
		delay_ms(1000); 
		PORTB = 0b11111111;	
		delay_ms(1000); 
	}
}
