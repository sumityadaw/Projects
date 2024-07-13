//lcd.h
//primary lcd drivers prototypes
void WriteLCD(unsigned char);
void CmdLCD(unsigned char);
void CharLCD(unsigned char);
void InitLCD(void);
//secondary drivers prototypes
void StrLCD(char *s);
void U32LCD(unsigned int);
void S32LCD(int);
void F32LCD(float,unsigned int);
void BinLCD(unsigned int,unsigned int);
void HexLCD(unsigned int);
void BuildCGRAM(unsigned char *p,unsigned int);
