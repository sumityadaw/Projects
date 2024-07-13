#include <lpc214x.h>

#define bit(x) (1 << x)

void lcd_init(void);
void cmd(unsigned char a);
void dat(unsigned char b);
void delay(void);

int main() {
    VPBDIV = 0x01;

    IO0DIR |= 0xff000; // P0.12 to P0.15 set as output for data lines
    IO0DIR |= bit(16) | bit(17) | bit(18); // P0.16 to P0.18 set as output for control lines
    
    lcd_init();
    
    cmd(0x80);
    dat('H');
    dat('e');
    dat('l');
    dat('l');
    dat('o');
    dat(',');
    dat(' ');
    dat('W');
    dat('o');
    dat('r');
    dat('l');
    dat('d');
    
    while(1);
}

void lcd_init() {
    cmd(0x33); // Initialize LCD in 4-bit mode
    cmd(0x32); // 4-bit mode, 2 lines, 5x7 format
    cmd(0x28); // Display ON, Cursor OFF
    cmd(0x0e); // Increment cursor
    cmd(0x01); // Clear display
    delay();
}

void cmd(unsigned char a) {
    IO0PIN &= 0xff00ffff;
    IO0PIN |= (a & 0xf0) << 8;
    IO0CLR |= bit(18); // RS = 0
    IO0CLR |= bit(17); // RW = 0
    IO0SET |= bit(16); // E = 1
    delay();
    IO0CLR |= bit(16); // E = 0
    
    IO0PIN &= 0xff00ffff;
    IO0PIN |= ((a << 4) & 0xf0) << 8;
    IO0CLR |= bit(18); // RS = 0
    IO0CLR |= bit(17); // RW = 0
    IO0SET |= bit(16); // E = 1
    delay();
    IO0CLR |= bit(16); // E = 0
}

void dat(unsigned char b) {
    IO0PIN &= 0xff00ffff;
    IO0PIN |= (b & 0xf0) << 8;
    IO0SET |= bit(18); // RS = 1
    IO0CLR |= bit(17); // RW = 0
    IO0SET |= bit(16); // E = 1
    delay();
    IO0CLR |= bit(16); // E = 0
    
    IO0PIN &= 0xff00ffff;
    IO0PIN |= ((b << 4) & 0xf0) << 8;
    IO0SET |= bit(18); // RS = 1
    IO0CLR |= bit(17); // RW = 0
    IO0SET |= bit(16); // E = 1
    delay();
    IO0CLR |= bit(16); // E = 0
}

void delay() {
    unsigned int i;
    for(i = 0; i < 10000; i++);
}
