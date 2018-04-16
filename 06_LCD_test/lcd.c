#include <mega128.h>


#asm
.equ __lcd_port=0x15 
#endasm

// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here

void main(void)
{

    PORTA = 0xff;
    DDRA = 0xff;
    // Alphanumeric LCD initialization
    // Connections are specified in the
    // Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
    // RS - PORTA Bit 0
    // RD - PORTA Bit 1
    // EN - PORTA Bit 2
    // D4 - PORTA Bit 4
    // D5 - PORTA Bit 5
    // D6 - PORTA Bit 6
    // D7 - PORTA Bit 7
    // Characters/line: 8

// initialize the LCD for
// 2 lines & 16 columns
lcd_init(16);

// go on the second LCD line
lcd_gotoxy(0,1);

// display the message
lcd_putsf("Hello world");

// stop here
while (1);
}
