#include <mega128.h>
#include <stdio.h>
#include <delay.h>
#asm
.equ __lcd_port=0x1B;       // PORTA
#endasm
#include <lcd.h>

#define USTrgger        PORTC.0 // Ʈ���� �޽� ��� ��
#define USEcho          PINC.1  // ���� ��ȣ �Է� ��
#define SOUND_SPEED_mm  (340000.f)  // 340m/s
#define OVF_PERIOD_s    (0.000016f) // = 1*256/16MHz = 16us

int MeasureDistanceByUSS();
long ovf_count;
long rise_time, fall_time;

interrupt [TIM0_OVF] void timer0_ovf_isr(void) // interr_countr 0 overflow interrupt 
{
    ovf_count++;    // �� 16��s ���� ���ͷ�Ʈ �߻�
} 

void main(void)
{
    char sbuf[16];
    int distance;
    PORTA = 0xff;   DDRA = 0xff;    // LCD
    PORTC = 0x02;   DDRC = 0x01;    // PC0: Ʈ���� ���, PC1: ���� �Է�
    TCCR0 = 0x01;		// ��ָ��, �ý��� Ŭ�� 8����
    lcd_init(16);
    #asm("sei")
    	
    while (1)
    {
        distance = MeasureDistanceByUSS();	// ������ �߻� �Ÿ� ����
        lcd_clear();
        delay_ms(1);
        lcd_gotoxy(0,0);
        sprintf(sbuf, "Dist:%d mm", distance);  // �Ÿ� �� ���÷���
        lcd_puts(sbuf); 
        delay_ms(1);
        lcd_gotoxy(0,1);
        sprintf(sbuf, "Count:%d, %d", rise_time, fall_time);  // �Ÿ� �� ���÷���
        lcd_puts(sbuf); 
        delay_ms(200);
    }
}

int MeasureDistanceByUSS(void)    // �����ļ��� �۵��Ͽ� �Ÿ� ���ϱ�
{
    static float old_distance = 0.f;
    float distance;
    ovf_count = 0;
    TIMSK = 0x01; 	// timer start
    USTrgger = 1; 	// Ʈ���� �޽�(10��s) �߻� 
    delay_us(10);
    USTrgger = 0;
    
    // �� 12���Ͱ� �Ѿ��, ���� Ż�� 
    while( (USEcho == 0) && (ovf_count <= 2200) );
    rise_time = ovf_count;
    while( (USEcho == 1) && (ovf_count <= 2200) );
    fall_time = ovf_count;

    TIMSK=0x00; // timer stop
    distance = SOUND_SPEED_mm*OVF_PERIOD_s*(fall_time-rise_time)/2.f; // �Ÿ� = �ӵ�*�ð�

    if(distance <= 20)
        distance = old_distance; //�Ÿ����� 50mm�����̸� ���������� ����
    else
        old_distance = distance; //������ �����͸� ���� �����ͺ����� ����
    delay_ms(10);
    return (int)distance;
}
