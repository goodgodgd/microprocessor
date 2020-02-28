#include <mega128.h>
#include <delay.h>

void main(void)
{
    // FND Data  '0'      '1'     ‘2'     '3'     '4'     '5'     '6'     '7'     '8'     '9' 
    unsigned char fnd[10]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x98};
    
    PORTB=0x00;
	DDRB=0xFF;
	PORTD=0x00;
	DDRD=0xFF;
	
    while(1)
	{
        PORTB = ~fnd[4];	 // FND3 에만 “4” 점등
        PORTD = ~0x01; 
        delay_ms(5);

        PORTB = ~fnd[7]; 	 // FND2 에만 “7” 점등
        PORTD = ~0x02; 		
        delay_ms(5); 
		 		
        PORTB = ~fnd[5]; 	 // FND1 에만 “5” 점등
        PORTD = ~0x04; 		
        delay_ms(5); 
		 		
        PORTB = ~fnd[3];	 // FND0 에만 “3” 점등
        PORTD = ~0x08;
        delay_ms(5); 		
	}
} 
