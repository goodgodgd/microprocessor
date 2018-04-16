#include <mega128.h>	// ATmega128 헤더파일
#include <delay.h>		// 시간지연 헤더파일
void main(void)
{
	PORTE=0x00;		// Port A 초기값 
	DDRE=0xFF;		// Port A 설정, 출력으로 사용
	while(1) 			// 무한 반복 루틴
	{
	 	PORTE = 0xf0;	//PORTE에 1111 0000 을 출력
	 	delay_ms(500);	// 시간 지연 함수- 0.5초
	 	PORTE = 0x0f;	//PORTE에 0000 1111 을 출력
	 	delay_ms(500);	// 시간 지연 함수 - 0.5초
	}
}
