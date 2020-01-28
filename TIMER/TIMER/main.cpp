/*
 * TIMER.cpp
 *
 * Created: 1/28/2020 9:57:14 PM
 * Author : MCLEANS
 */ 
#define  F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "LCD.hpp"
#include <stdlib.h>
#include <avr/interrupt.h>

LCD lcd;

int second = 0;
int minute = 0;
int hour = 0;
char second_value[10];
char minute_value[10];
char hour_value[10];
char space[] = " ";
char colon[] = ":";


 ISR(TIMER1_COMPA_vect){
	 PORTD ^= (1<<PIND5);
	
	 
 }

int main(void)
{
    /* Replace with your application code */
	
	DDRD |= (1<<PIND5);
	lcd.initialize();
	char boot_string[] = "TIMER SYSTEM";
	lcd.send_string(boot_string);
	_delay_ms(1000);
	lcd.clear();
	
	//enable CTC MODE
	TCCR1B |= (1<<WGM12);
	//set prescaler of 256 (count for 1 sec = 62500)
	TCCR1B |= (1<<CS12);
	//OCR1A compare value
	OCR1A = 3907;
	//enable timer compare interrupt
	TIMSK |= (OCIE1A);
	//set global interrupts
	sei();
	
	
	
	
	
    while (1) 
    {
		
		if(TIFR & (1<<OCF1A)){
			PORTD ^= (1<<PIND5);
			TIFR |= (1<<OCF1A);
			second++;
			if(second > 59){
				second = 0;
				minute++;
				if(minute > 59){
					minute=0;
					hour++;
					if(hour>23){
						hour = 0;
					}
				}
			}
			
			
			itoa(minute,minute_value,10);
			itoa(second,second_value,10);
			itoa(hour,hour_value,10);
			
			lcd.clear();
			lcd.send_string(hour_value);
			lcd.send_string(space);
			lcd.send_string(colon);
			lcd.send_string(space);
			lcd.send_string(minute_value);
			lcd.send_string(space);
			lcd.send_string(colon);
			lcd.send_string(space);
			lcd.send_string(second_value);
			
		}
	}

}

