#include <mega128.h>
#include <delay.h>
          //  "0",    "1",   "2",   "3",    "4",   "5",    "6",   "7",    "8",   "9"
unsigned char FND[10]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

void MPUinit(void)  // ============ �ʱ�ȭ �Լ� =============
{
    PORTB=0x00;  DDRB=0xFF;    // Port B ���� 
    PORTC=0xFF;  DDRC=0x00;    // Port C ����ġ �Է�
    PORTE=0x00;  DDRE=0xFF;    // Port E FND

    TCCR1A = 0x21;      // 00101001 8��Ʈ ���󺯰� PWM 
    TCCR1B = 0x03;      // 64���� 
    TCNT1 = 0x0000;
}

void main(void)     //============= ���� �Լ� ============
{
    unsigned char buff0;    // ����ġ �Է°� ����
    MPUinit();
    OCR1BL = 0; 		    // ���� ���� : duty ratio = 0% 
    PORTB = 0xFD; 		    // ��ȸ�� ��� : 1(1)11 1101
    
    while (1)
    {
        buff0 = PINC & 0x1F;    // ����ġ �� ���� 
        delay_ms(5);
    
        switch(buff0)
        {
        case 0x1E:		    // SW0�� ������(0001 1110)
            OCR1BL = 51;    // duty �� =  20%
            PORTE = ~FND[1]; // FND ��1��
            break;
        case 0x1D:			// SW1�� ������(0001 1101)
            OCR1BL = 127;   // duty �� = 50%
            PORTE = ~FND[2]; // FND ��2�� 
            break;
        case 0x1B:			// SW2�� ������(0001 1011)
            OCR1BL = 178;  // duty �� = 70%
            PORTE = ~FND[3]; // FND ��3��
            break;
        case 0x17:			// SW3�� ������ (0001 0111)
            OCR1BL = 255;   // duty �� = 100%
            PORTE = ~FND[4]; // FND ��4��
            break;
        case 0x0F:			// SW4�� ������ (0000 1111)
            OCR1BL = 0;     // ���� ���� : duty��= 0%
            PORTE = ~FND[0];	// FND ��0��  
            break;
        }
    };
}


