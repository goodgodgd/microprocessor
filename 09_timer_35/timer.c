#include <mega128.h>
#include <delay.h>

void initial(void)    // ---- TIMER, PORT �ʱ�ȭ �Լ�
{
    DDRC= 0x00;     // ��ƮC �Է�
    PORTC = 0xFF;    
    DDRE= 0xFF;     // ��Ʈ E ������� ����
    PORTE = 0x00;
     
    TCCR3A = 0x10;    // ���4, OC3B ������, 8����
    TCCR3B = 0x0A;    
    OCR3AH = 0xFF;	  // set default OCR 
    OCR3AL = 0x00;
}

void main(void)
{
    unsigned char buff; 	// Ű �Է� ����
	initial();

    while(1)
	{ 
	    buff = PINC & 0b00000111 ; 	// Ű �Է�
	    switch(buff){
	 	case 0x06: 		// sw0 ON
	 	    OCR3AH = 0x00;	 // 10KHz 
		    OCR3AL = 0x63;
		    break;
	 	case 0x05: 		// sw1 ON
		    OCR3AH = 0x00;	// 5KHz 
		    OCR3AL = 0xC7; 
		    break;
	 	case 0x03: 		// sw2 ON
	 	    OCR3AH = 0x03;	// 1KHz 
		    OCR3AL = 0xE7;
	 	    break;
		}
	}
}
