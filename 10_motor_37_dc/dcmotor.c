#include <mega128.h>
#include <delay.h>
          //  "0",    "1",   "2",   "3",    "4",   "5",    "6",   "7",    "8",   "9"
unsigned char FND[10]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

void MPUinit(void)  // ============ 초기화 함수 =============
{
    PORTB=0x00;  DDRB=0xFF;    // Port B 모터 
    PORTC=0xFF;  DDRC=0x00;    // Port C 스위치 입력
    PORTE=0x00;  DDRE=0xFF;    // Port E FND

    TCCR1A = 0x21;      // 00101001 8비트 위상변경 PWM 
    TCCR1B = 0x03;      // 64분주 
    TCNT1 = 0x0000;
}

void main(void)     //============= 메인 함수 ============
{
    unsigned char buff0;    // 스위치 입력값 저장
    MPUinit();
    OCR1BL = 0; 		    // 모터 정지 : duty ratio = 0% 
    PORTB = 0xFD; 		    // 정회전 모드 : 1(1)11 1101
    
    while (1)
    {
        buff0 = PINC & 0x1F;    // 스위치 값 읽음 
        delay_ms(5);
    
        switch(buff0)
        {
        case 0x1E:		    // SW0이 눌리면(0001 1110)
            OCR1BL = 51;    // duty 비 =  20%
            PORTE = ~FND[1]; // FND “1“
            break;
        case 0x1D:			// SW1이 눌리면(0001 1101)
            OCR1BL = 127;   // duty 비 = 50%
            PORTE = ~FND[2]; // FND “2“ 
            break;
        case 0x1B:			// SW2이 눌리면(0001 1011)
            OCR1BL = 178;  // duty 비 = 70%
            PORTE = ~FND[3]; // FND “3“
            break;
        case 0x17:			// SW3이 눌리면 (0001 0111)
            OCR1BL = 255;   // duty 비 = 100%
            PORTE = ~FND[4]; // FND “4“
            break;
        case 0x0F:			// SW4이 눌리면 (0000 1111)
            OCR1BL = 0;     // 모터 정지 : duty비= 0%
            PORTE = ~FND[0];	// FND “0“  
            break;
        }
    };
}


