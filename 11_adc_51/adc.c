#include <mega128.h>
#include <stdio.h>
#include <delay.h>
#asm
.equ __lcd_port=0x1B;       // PORTA
#endasm
#include <lcd.h>

#define USTrgger        PORTC.0 // 트리거 펄스 출력 핀
#define USEcho          PINC.1  // 에코 신호 입력 핀
#define SOUND_SPEED_mm  (340000.f)  // 340m/s
#define OVF_PERIOD_s    (0.000016f) // = 1*256/16MHz = 16us

int MeasureDistanceByUSS();
long ovf_count;
long rise_time, fall_time;

interrupt [TIM0_OVF] void timer0_ovf_isr(void) // interr_countr 0 overflow interrupt 
{
    ovf_count++;    // 매 16μs 마다 인터럽트 발생
} 

void main(void)
{
    char sbuf[16];
    int distance;
    PORTA = 0xff;   DDRA = 0xff;    // LCD
    PORTC = 0x02;   DDRC = 0x01;    // PC0: 트리거 출력, PC1: 에코 입력
    TCCR0 = 0x01;		// 노멀모드, 시스템 클록 8분주
    lcd_init(16);
    #asm("sei")
    	
    while (1)
    {
        distance = MeasureDistanceByUSS();	// 초음파 발생 거리 구함
        lcd_clear();
        delay_ms(1);
        lcd_gotoxy(0,0);
        sprintf(sbuf, "Dist:%d mm", distance);  // 거리 값 디스플레이
        lcd_puts(sbuf); 
        delay_ms(1);
        lcd_gotoxy(0,1);
        sprintf(sbuf, "Count:%d, %d", rise_time, fall_time);  // 거리 값 디스플레이
        lcd_puts(sbuf); 
        delay_ms(200);
    }
}

int MeasureDistanceByUSS(void)    // 초음파센서 작동하여 거리 구하기
{
    static float old_distance = 0.f;
    float distance;
    ovf_count = 0;
    TIMSK = 0x01; 	// timer start
    USTrgger = 1; 	// 트리거 펄스(10μs) 발생 
    delay_us(10);
    USTrgger = 0;
    
    // 약 12미터가 넘어가면, 루프 탈출 
    while( (USEcho == 0) && (ovf_count <= 2200) );
    rise_time = ovf_count;
    while( (USEcho == 1) && (ovf_count <= 2200) );
    fall_time = ovf_count;

    TIMSK=0x00; // timer stop
    distance = SOUND_SPEED_mm*OVF_PERIOD_s*(fall_time-rise_time)/2.f; // 거리 = 속도*시간

    if(distance <= 20)
        distance = old_distance; //거리값이 50mm이하이면 이전데이터 송츨
    else
        old_distance = distance; //지금의 데이터를 예전 데이터변수로 전달
    delay_ms(10);
    return (int)distance;
}
