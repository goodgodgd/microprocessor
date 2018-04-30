#include <mega128.h>	
#include <delay.h>

#define FND_DIGIT	PORTC
#define FND_SELEC	PORTA

// FND Data   '0'   '1'    ‘2'    '3'    '4'    '5'    '6' ‘    7'     '8'    '9' 
unsigned char fnd[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x98};

void Initial(void) // ------ 초기화 함수 ---------------------------
{
	PORTC = 0xff;   DDRC = 0xff;	// FND 출력
	PORTA = 0xff;   DDRA = 0xff;	// FND 스위치 TR
	PORTF = 0x00;   DDRF = 0x00;    // A/D0(PF.0) <-- 가변저항
	delay_ms(10);
    
	ADCSRA = 0x85;		// (1000 0101) ADC enable, 32분주
	ADMUX = 0x40;		// 기준전압 = AVCC(+5V), select 채널 ADC0 
	delay_us(150);
}	

void FndDisplay(unsigned int i) // ------ FND 표시함수 --------
{
    FND_DIGIT = ~fnd[i/1000];        // i 값 천 단위 계산 FND3 만 점등
    FND_SELEC = 0x0E;
    delay_ms(2);
    FND_DIGIT = ~fnd[i%1000/100]; 	// i 값 백 단위 계산 FND2 만 점등 
    FND_SELEC = 0x0D;
    delay_ms(2);
    FND_DIGIT = ~fnd[i%100/10]; 	    // i 값 십 단위 계산 FND1 만 점등
    FND_SELEC = 0x0B;
    delay_ms(2);
    FND_DIGIT = ~fnd[i%10/1]; 	    // i 값 일 단위 계산 FND0 만 점등
    FND_SELEC = 0x07; 
    delay_ms(2);
}

void main(void) // ========== >>> 메인 함수 <<< ========
{
	int i;
	unsigned int ADresult ;
	Initial(); 	// 포트 및 ADC초기화
    
	while(1)
	{
        ADresult = 0;
        // 노이즈를 줄이기 위해 8회 측정후 평균
        for(i = 1; i <= 8; i++) {	// 8회 반복하여 읽어들임 
            ADCSRA = 0xC5;		    // A/D변환시작 및 clear ADIF
            while( (ADCSRA & 0x10) == 0 );          // 변환 완료까지 대기 
            ADresult += (int)ADCL +((int)ADCH << 8);// A/D 결과 누적합 구함
            delay_ms(1);
        }
        ADresult /= 8;	        // 8 로 나누어 평균값 구함.
        FndDisplay(ADresult);	// FND에 출력 
	}
}
