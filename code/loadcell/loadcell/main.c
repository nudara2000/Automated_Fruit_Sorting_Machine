                       
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "lcd.h"
#define calibrationFactor 0.00002773232
char calculation();
char numbers[5];
	char inputBits[24];
	char holder;
	char digitAmount;
	
int main(void)
{
    
	DDRD &= ~(1<<PD1);//make port input..DOUT
	DDRD |= (1<<PD0);//make port output...PD_SCK
	PORTD |= (1<<PD1);
	

	
	
	while(1)
	{
		for(int pulse=0;pulse<25;pulse++)
		{
			PORTD |= (1<<PD0);
			_delay_us(2);
			PORTD &= ~(1<<PD0);
			_delay_us(2);
			
			if(!(~PIND & (1<<PD1)) ) 
			{
				holder ='1';
			}
			else
			{
				holder = '0';
			}
			inputBits[pulse] = holder;
			_delay_us(1);
			
		}//end of FOR LOOP
		
		PORTD |= (1<<PD0);		//25th pulse
		_delay_us(2);				//DOUT pin back to high
		PORTD &= (~(1<<PD0));
		//_delay_ms(2);
		
		digitAmount=calculation();
		Display(digitAmount);
		_delay_ms(1000);
		
	}//end of WHILE LOOP
	
	
	
}//end of MAIN

char calculation()
{
	int sum = 0;
	
	for(int j=23;j>=0;j--){
		
		if(inputBits[j]=='0')
		{               
			sum=sum + pow(2,(23-j))*1;  
			
		}
		
	}
	
	double decimalOutput=sum+1.0;
	double finalValue=calibrationFactor*decimalOutput;
	int roundFinalValue=round(finalValue);
	
	return roundFinalValue ;
	
	char count=0;
	if(roundFinalValue==465){
		
		numbers[count]='0';
		_delay_ms(2);
		numbers[count+1]='0';
		
		}else{
		
		while(roundFinalValue>0){	//store values in "numbers" array.
			
			int remainder=roundFinalValue%10;
			numbers[count]=remainder+'0';
			roundFinalValue=roundFinalValue/10;
			count++;
			_delay_ms(10);
			
		}
	}
	return count;
}