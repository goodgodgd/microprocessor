#include <mega128.h>
#include <delay.h>

// '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'dot'
unsigned char fnd[17]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x98, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e, 0x7f}; 

int KeyMatrix(); 

void main(void)
{
    unsigned char num; 
    DDRA = 0x0F; PORTA = 0x00;     // PORTA 0,1,2,3출력, 4,5,6,7 입력으로
    DDRB = 0xFF; PORTB = 0x00;
    PORTB = ~fnd[0];         // 초기 "0" 표시

    while(1)
    {
        num = KeyMatrix();
        while((PINA&0xf0) != 0xf0)
            delay_ms(1);
        PORTB = ~fnd[num]; // 키 메트릭스 함수 호출
        delay_ms(1);
    }
}

int KeyMatrix()    // 키 값으로부터 FND 출력 코드 생성 함수
{
	static unsigned char key = 0;
	int keyout = 0x01; 		// 키 메트릭스 신호 
	int i;	 
	for( i = 0; i <= 3; i++ )
	{ 
        PORTA = ~keyout; 	// Port C에 1111 1110 출력, 0,4,8,C line Enable 
        delay_ms(1);
        switch(PINA & 0xf0) 	// PINC & 0xf0 = 응답 출력 비트
        {
	 	case 0x70: key = 0+i;  break;
	 	case 0xB0: key = 4+i;  break;
	 	case 0xD0: key = 8+i;  break;
	 	case 0xE0: key = 12+i;  break; 
        }
        keyout = keyout<<1;   //키보드 신호 출력 카운터
	}
	return key; 
} 

