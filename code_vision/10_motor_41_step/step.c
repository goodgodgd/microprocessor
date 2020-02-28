#include <mega128.h>
#include <delay.h>

void main(void)
{
    unsigned char Step[4] = {0x01, 0x02, 0x04, 0x08};
    int i, j; 
    int Time; 
    DDRA = 0xff;  PORTC = 0x00;
    while(1)
    {
        Time = 20; // delay = 200ms ���� ����
        // ---------------- ����------------
        for(j=0; j<90; j++) {
             for(i=0; i<=3; i++) {
                 PORTA = Step[i];
                 delay_ms(Time);
             }
             if(j%10==0)
                Time -= 2;
         }
         
        // ---------------- ���------------
        for(j=0; j<300; j++) {
            for(i=0; i<=3; i++) {
                PORTA = Step[i];
                delay_ms(Time);
            }
        }

        // ---------------- ����------------
        for(j=0; j<90; j++) {
            for(i=0; i<=3; i++) {
                PORTA = Step[i];
                delay_ms(Time);
            }
             if(j%10==0)
                Time += 2;
         }

        //-----------------����------------
        PORTA = 0x00; 		
        delay_ms(500);
    };
}
