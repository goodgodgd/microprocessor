#include <mega128.h>
#include <delay.h>
void left_shift(void) ;        // SW0 이 ON 일 때 왼쪽 시프트 처리 함수 원형선언
void right_shift(void);        // SW1 이 ON 일 때 오른쪽 시프트 처리 함수 원형선언 

int LL=0x01;         // Left Shift LED 초기 점등 데이터 0b00000001 
int RR=0x80;         // Right Shift LED 초기 점등 데이터 0b10000000

void main(void)        // -------- 메인 함수 ------------
{
    PORTE = 0x00; DDRE = 0xff;     
    PORTC = 0xff; DDRC = 0x00;
    while(1)
    {
        if(PINC.0 == 0)         // SW0 이 ON이면 왼쪽시프트 함수 실행
            left_shift();
        else if (PINC.1 == 0)   // SW1이 ON이면 오른쪽 시스트 함수 실행
            right_shift();
    }
} 

void left_shift(void)    //----SW1 이 ON 일 때 왼쪽 시프트 처리 함수 ------
{
	do{
	    PORTE = LL; 		// 왼쪽 시프트 LED 초기값 출력 
	    delay_ms(200);
	    if (LL == 0x80)     // 마지막 LED ON 되었으면 다시 초기값으로 
		    LL=0x01; 
	    else 			    // 아니면 1 bit 좌 시프트 
		    LL <<= 1;
	} while((PINC.0 != 0)&&(PINC.1 != 0)); 
    // SW 하나라도 ON 이 아니면 계속 진행
}

void right_shift(void)      //--SW 2 가 ON 일 때의 오른쪽 시프트 처리 함수 ----
{
	do{ 
	    PORTE = RR; 	    // 오른쪽 시프트 LED 초기값 출력 
	    delay_ms(200);
	    if (RR == 0x01) 
		    RR=0x80; 		// 마지막 LED ON 되었으면 다시 초기값으로 
	    else 			    // 아니면 1 bit 우 시프트 
	 	    RR >>= 1; 
	} while((PINC.0 != 0)&&(PINC.1 != 0));
} 
