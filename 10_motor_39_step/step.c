#include <mega128.h>
#include <delay.h> 

/*
// 1�� ����
void main(void)
{
    DDRA = 0xff; 
    PORTA = 0x00;
    while(1)
    {
        PORTA = 0x01;  delay_ms(5);     // ����1 : 0001
        PORTA = 0x02;  delay_ms(5);     // ����2 : 0010
        PORTA = 0x04;  delay_ms(5);     // ����3 : 0100
        PORTA = 0x08;  delay_ms(5);     // ����4 : 1000
    }
}
*/

/*
// 2�� ����
void main(void)
{
    unsigned char Step[4] = {0x03, 0x06, 0x0c, 0x09};
    int i;
    DDRA = 0xff; 
    PORTA = 0x00;
    while(1)
    {
        for(i=0; i<=3; i++)
        {
            PORTA = Step[i];
            delay_ms(5);
        }
    }
}
*/

// 1-2�� ����
void main(void)
{
    unsigned char Step[8] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08, 0x09};
    int i;
    DDRA = 0xff; 
    PORTA = 0x00;
    while(1)
    {
        for(i=0; i<=7; i++)
        {
            PORTA = Step[i];
            delay_ms(5);
        }
    }
}


