#include <mega128.h>	
#include <delay.h>

#define FND_DIGIT	PORTC
#define FND_SELEC	PORTA

// FND Data   '0'   '1'    ��2'    '3'    '4'    '5'    '6' ��    7'     '8'    '9' 
unsigned char fnd[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x98};

void Initial(void) // ------ �ʱ�ȭ �Լ� ---------------------------
{
	PORTC = 0xff;   DDRC = 0xff;	// FND ���
	PORTA = 0xff;   DDRA = 0xff;	// FND ����ġ TR
	PORTF = 0x00;   DDRF = 0x00;    // A/D0(PF.0) <-- ��������
	delay_ms(10);
    
	ADCSRA = 0x85;		// (1000 0101) ADC enable, 32����
	ADMUX = 0x40;		// �������� = AVCC(+5V), select ä�� ADC0 
	delay_us(150);
}	

void FndDisplay(unsigned int i) // ------ FND ǥ���Լ� --------
{
    FND_DIGIT = ~fnd[i/1000];        // i �� õ ���� ��� FND3 �� ����
    FND_SELEC = 0x0E;
    delay_ms(2);
    FND_DIGIT = ~fnd[i%1000/100]; 	// i �� �� ���� ��� FND2 �� ���� 
    FND_SELEC = 0x0D;
    delay_ms(2);
    FND_DIGIT = ~fnd[i%100/10]; 	    // i �� �� ���� ��� FND1 �� ����
    FND_SELEC = 0x0B;
    delay_ms(2);
    FND_DIGIT = ~fnd[i%10/1]; 	    // i �� �� ���� ��� FND0 �� ����
    FND_SELEC = 0x07; 
    delay_ms(2);
}

void main(void) // ========== >>> ���� �Լ� <<< ========
{
	int i;
	unsigned int ADresult ;
	Initial(); 	// ��Ʈ �� ADC�ʱ�ȭ
    
	while(1)
	{
        ADresult = 0;
        // ����� ���̱� ���� 8ȸ ������ ���
        for(i = 1; i <= 8; i++) {	// 8ȸ �ݺ��Ͽ� �о���� 
            ADCSRA = 0xC5;		    // A/D��ȯ���� �� clear ADIF
            while( (ADCSRA & 0x10) == 0 );          // ��ȯ �Ϸ���� ��� 
            ADresult += (int)ADCL +((int)ADCH << 8);// A/D ��� ������ ����
            delay_ms(1);
        }
        ADresult /= 8;	        // 8 �� ������ ��հ� ����.
        FndDisplay(ADresult);	// FND�� ��� 
	}
}
