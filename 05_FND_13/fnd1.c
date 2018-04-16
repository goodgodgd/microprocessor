#include <mega128.h>
#include <delay.h>

//          FND Data  '0'    '1'   ��2'   '3'   '4'   '5'  '6'    '7'   '8'   '9'
unsigned char fnd[10]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x98};

void main(void)
{
    unsigned char i;
    PORTB=0xFF;
    DDRB=0xFF;
    
    while(1)
    {
        for(i=0 ; i <= 9 ; i++)     // FND ���� data Array Fetch
        {
            PORTB = ~fnd[i];     // FND data display '0' ~ '9'
            delay_ms(1000); 
	    }
	}
}
