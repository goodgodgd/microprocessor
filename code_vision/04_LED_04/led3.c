#include <mega128.h>

void main(void)
{
    PORTE = 0x00;        // Port A �ʱⰪ 
    DDRE = 0xff;        // Port A �������.
    PORTC = 0xff;        // Port C �ʱⰪ 
    DDRC = 0x00;        // Port C �Է�����.
    
    while (1) //--------------- ���� �ݺ� -------------------
    {
        if(PINC.0 == 0)             // SW0 ON ?
            PORTE = 0b00000011;     // 0x3f        
        else if(PINC.1 == 0)        // SW1 ON?
            PORTE = 0b00001100;     // 0xcf        
        else if(PINC.2 == 0)        // SW2 ON?
            PORTE = 0b00110000;     // 0xf3        
        else if(PINC.3 == 0)        // SW3 ON?
            PORTE = 0b11000000;     // 0xfc        
         
    } // ----------------------------------------------------
}
