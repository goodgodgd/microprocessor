#include <mega128.h>
#include <delay.h>

void main(void)
{
    // (옛날) c언어에서 변수 선언은 전방선언 해야함
    // c99 이후로 나온 컴파일러는 전방선언 제약이 없으나 avr compiler가 오래된 관계로 옛날 문법을 따라야 함
    unsigned char last = 0x80;
    unsigned char buff = last;    // 1000 0000

    PORTE = 0x00;
    DDRE = 0xff;
        
    while (1)
    {
        if(buff == last)    // 7번 LED까지 켜졌으면
            buff = 0x01;    // buff 값 초기 점등데이터로
        else                // 아니면 다음 점등데이터 준비
        {
            buff = buff<<1;  // 1 bit shift left
            buff = buff&0xfe;// 0번 비트를 "1"로 만듬 (0번 LED끔) 
	    }
        
        PORTE = buff;       // LED ← buff : LED점등
        delay_ms(500);
	}
}
