#include <mega128.h>
#include <delay.h>

#define SW0 PINC.0       // 사용자 정의. “PINC” 표현을 “SW” 표현으로 대치한다.
#define SW1 PINC.1
#define SW2 PINC.2 

// FND Data  '0'      '1'     ‘2'     '3'     '4'     '5'     '6'     '7'     '8'     '9' 
unsigned char fnd[10]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x98};
int count = 0;

void UpCnt(void)    // --- 증가 카운트 함수 ------
{
    count++;        // 카운터값 +1 증가
    if(count > 9)        // 카운터가 9 까지 표시 되었으면 이상이면 다시 0 부터 
        count = 0;
}
void DownCnt(void)    // --- 감소 카운트 함수--------
{
    count--;        // 카운터값 -1 감소
    if(count < 0)        // 카운터가 0 까지 표시 되었으면 이면 다시 9 부터 
	    count = 9;
}

void main(void)
{
    PORTB=0xFF; DDRB=0xFF;
    PORTC=0xFF; DDRC=0x00; 
    PORTB = ~fnd[0];

    while(1)
    { 
        if(SW0 == 0)		// 스위치 SW0 ON?
        {
            delay_ms(1); 		// 채터링 방지를 위해 약간 시간지연.
            while(SW0 != 1) 		// OFF 될 때 까지 대기 
            { 
                delay_ms(1);
            }
            UpCnt();
            PORTB = ~fnd[count]; 	// 카운터값 FND 출력
        }
        if(SW1 == 0)		// 스위치 SW1 ON?
        { 
            delay_ms(1); 
            while(SW1 != 1) 		// OFF 될 때 까지 대기 
                delay_ms(1);
            DownCnt();
            PORTB = ~fnd[count]; 	// 카운터값 FND 출력
        }
        if(SW2 == 0) 		// 스위치 SW2 ON?
        {
            delay_ms(1); 
            while(SW2 != 1) 		// OFF 될 때 까지 대기 
                delay_ms(1);
            count = 0;		// 카운트값 초기화
            PORTB = ~fnd[count]; 
        }
    }  //  while 문 끝
}
