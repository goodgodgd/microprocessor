#include <mega128.h>
#include <delay.h>

void STEP_M_CW();       // STEP Motor CW 구동 함수
void STEP_M_CCW();      // STEP Motor CCW 구동 함수
void STEP_M_STOP();     // STEP Motor STOP함수

unsigned Step[4] = {0x01, 0x02, 0x04, 0x08};    // 모터 스텝
int i;

void main(void)
{
    unsigned char buff0;
    PORTC=0xff;            // Port C : 스위치 입력
    DDRC=0x00;
    PORTA=0xff;            // Port A : 모터 여자신호 출력 
    DDRA=0xff;
    
    while (1)
    {
        buff0 = PINC & 0x03;    // 스위치 읽음
        switch(buff0)
        {
        case 0x02:			    // SW0이 눌리면
            STEP_M_CW();		// STEP Motor CW 구동
            break;
        case 0x01:			    // SW1이 눌리면
            STEP_M_CCW();		// STEP Motor CCW 구동
            break;
        default:			    // default값이면
            STEP_M_STOP();		// 스위치가 눌려지지 않으면 정지
            break;
        }
    }
}

void STEP_M_CW()		// 정회전 함수 - 4스텝씩 구동한다.
{
    for(i=0; i<=3; i++)
    {
        PORTA = Step[i];
        delay_ms(5);
    }
}

void STEP_M_CCW()		// 역회전 함수 - 4스텝씩 구동한다.
{
    for(i=3; i>=0; i--)
    {
        PORTA = Step[i];
        delay_ms(5);
    }
}

void STEP_M_STOP()
{
    PORTA = 0x00;		
}
