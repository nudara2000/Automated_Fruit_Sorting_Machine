


#ifndef LCD_H_
#define LCD_H_


#define RS PA1
#define RW PA2
#define EN PA3
#define Port_Dir DDRA
#define Command_Data PORTA


void Display(unsigned char weight);
void LCD_Initialization(void);
void LCD_Command(unsigned char command);
void LCD_Display(unsigned char weight);


void Display(unsigned char weight)
{
	LCD_Initialization();
	
	unsigned char exitkey = '#';
	unsigned char receivekey;
	unsigned char clearkey = '*';
	unsigned int column = 0;

	LCD_Display(weight);
	_delay_ms(1000);
	//LCD_Command(0xC0);
	

	
	
}

void LCD_Initialization(void)
{
	Port_Dir = 0xFF;
	_delay_ms(20);		// LCD Power ON delay always >15ms
	
	LCD_Command(0x33);
	LCD_Command(0x32);	// Send for 4 bit initialization of LCD
	LCD_Command(0x28);	// 2 line, 5*7 matrix in 4-bit mode
	LCD_Command(0x0E);	// Display on cursor off
	LCD_Command(0x06);	//Increment cursor (shift cursor to right)
	LCD_Command(0x01);	// Clear display screen
	
}

void LCD_Command(unsigned char command)
{
	Command_Data = ((Command_Data & 0x0F) | (command & 0xF0));//take upper nibble to command register
	Command_Data &= ~(1<<RS); // select command register
	Command_Data &= ~(1<<RW); // select write mode
	Command_Data |= (1<<EN);
	_delay_us(1);
	Command_Data &= ~(1<<EN);
	_delay_us(200);
	
	Command_Data = ((Command_Data & 0x0F) | (command << 4));// lower nibble
	Command_Data |= (1<<EN);
	_delay_us(1);
	Command_Data &= ~(1<<EN);
	_delay_ms(2);
	
	// by using command << 4 mean last 4 bits come forward by 4 places,mean it comes to upper nibble from lower nibble
	
}




void LCD_Display(unsigned char weight)
{
	Command_Data = ((Command_Data & 0x0F) | (weight & 0xF0));
	Command_Data |= (1<<RS);
	Command_Data &= ~(1<<RW);
	Command_Data |= (1<<EN);
	
	_delay_us(1);
	Command_Data &= ~(1<<EN);
	_delay_us(200);
	
	Command_Data = ((Command_Data & 0x0F) | (weight << 4));
	Command_Data |= (1<<EN);
	
	_delay_us(1);
	Command_Data &= ~(1<<EN);
	_delay_ms(2);
	
	
}








#endif /* LCD_H_ */