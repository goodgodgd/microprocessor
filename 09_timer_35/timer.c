#include <mega128.h>
#include <delay.h>

void initial(void)    // ---- TIMER, PORT 초기화 함수
{
    DDRC= 0x00;     // 포트C 입력
    PORTC = 0xFF;    
    DDRE= 0xFF;     // 포트 E 출력으로 설정
    PORTE = 0x00;
     
    TCCR3A = 0x10;    // 모드4, OC3B 토글출력, 8분주
    TCCR3B = 0x0A;    
    OCR3AH = 0xFF;	  // set default OCR 
    OCR3AL = 0x00;
}

void main(void)
{
    unsigned char buff; 	// 키 입력 버퍼
	initial();

    while(1)
	{ 
	    buff = PINC & 0b00000111 ; 	// 키 입력
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
