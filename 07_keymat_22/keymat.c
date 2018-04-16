#include <mega128.h>
#include <delay.h>

#define INVALID_NUM 0x10

// '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'dot'
unsigned char fnd[17] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x98, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e, 0x7f}; 
unsigned char digits[4] = {0,0,0,0};

unsigned char KeyMatrix();
void ResetNumbers(); 
void ShiftNumbers(unsigned char num);
void PrintNumbers();

void main(void)
{
    unsigned char num_cur = INVALID_NUM;
    unsinged char num_buf = INVALID_NUM;
    
    DDRA = 0xFF; PORTA = 0x00;      // PORTA: 4 FND A~G
    DDRF = 0xFF; PORTF = 0xFF;      // PORTF: 4 FND D1~D4
    DDRC = 0x0F; PORTC = 0x00;      // PORTC: key matrix 0,1,2,3���, 4,5,6,7 �Է�����
    DDRB = 0xFF; PORTB = ~fnd[0];   // PORTB: single FND

    while(1)
    {
        // read pin and read number
        num_cur = KeyMatrix();
        
        // ��ư�� ������ FND�� ���� ��ư�� �ٽ� �ö�ö����� ��ٸ���.
        if(num_cur != INVALID_NUM)
        {
            PORTB = ~fnd[ num_cur ];
            PORTF = 0xff;
            num_buf = num_cur;
            delay_ms(1);
            continue;
        }
                
        if(num_buf == 0x0f)
            ResetNumbers();
        else if(num_buf <= 0x09)
            ShiftNumbers(num_buf);

        PrintNumbers();
        
        // ShiftNumbers()�� �ѹ��� ����ǵ��� ���� ���� �ٲ۴�.
        num_buf = INVALID_NUM; 
    }
}

unsigned char KeyMatrix()    // Ű �����κ��� FND ��� �ڵ� ���� �Լ�
{
    unsigned char key = INVALID_NUM;   // Ű�� ������ �ʾ��� �� �⺻��
    int keyout = 0x01;          // Ű ��Ʈ���� ��ȣ(���) 
    int i;
         
    for( i = 0; i <= 3; i++ )
    { 
        PORTC = ~keyout;     // Port C�� 1111 1110 ���, 0,4,8,C line Enable 
        delay_ms(1);
        switch(PINC & 0xf0)     // PINC & 0xf0 = ���� ��� ��Ʈ
        {
         case 0x70: key = 0+i;  break;
         case 0xB0: key = 4+i;  break;
         case 0xD0: key = 8+i;  break;
         case 0xE0: key = 12+i;  break; 
        }
        keyout = keyout<<1;   //Ű���� ��ȣ ��� ī����
    }
    return key; 
}

void ResetNumbers()
{
    int i;
    for(i=0; i<4; i++)
        digits[i] = 0x00;
} 

void ShiftNumbers(unsigned char num)
{
    // ���� ��ġ [d1]      [d2]      [d3]      [d4] -> d4�� 1�� �ڸ�
    // �迭     digits[0] digits[1] digits[2] digits[3]
    // ��Ʈ     PA0       PA1       PA2       PA3
    int i;
    // shift to left
    for(i=0; i<3; i++)
        digits[i] = digits[i+1];
    digits[3] = num;    // ���ڸ��� �߰�
}

void PrintNumbers()
{
    PORTF = ~0x01;
    PORTA = ~fnd[ digits[0] ];
    delay_ms(5);

    PORTF = ~0x02;
    PORTA = ~fnd[ digits[1] ];
    delay_ms(5);

    PORTF = ~0x04;
    PORTA = ~fnd[ digits[2] ];
    delay_ms(5);

    PORTF = ~0x08;
    PORTA = ~fnd[ digits[3] ];
    delay_ms(5);
}
