#include <mega128.h>	// ATmega128 헤더파일
#include <delay.h>		// 시간지연 헤더파일

void main(void)
{	
	PORTE = 0xff;		// Port A 초기값 
	DDRE = 0xff;		// Port A 출력으로.
	PORTC = 0xff;		// Port C 초기값 
	DDRC = 0x00;		// Port C 입력으로.
	
	while(1) // 무한 반복
	{
	    if(PINC.0 == 0)		// SW0 ON ?
		    PORTE = 0x00;	// LED 모두 점등 
	    else if(PINC.1 == 0)// SW1 ON?
	       	PORTE = 0xff;	// LED 모두 끔		 
	}
}
