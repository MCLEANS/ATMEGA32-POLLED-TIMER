#include "LCD.hpp"

LCD::LCD(){}

void LCD::send_character_to_pins(char character){
    if((character & 0b00000001))  D0PORT |= (1<<D0PIN);
    else if(!(character & 0b00000001))  D0PORT &= ~(1<<D0PIN);

    if((character & 0b00000010))  D1PORT |= (1<<D1PIN);
    else if(!(character & 0b00000010))  D1PORT &= ~(1<<D1PIN);

    if((character &  0b00000100))  D2PORT |= (1<<D2PIN);
    else if(!(character &  0b00000100))  D2PORT &= ~(1<<D2PIN);

    if((character &   0b00001000))  D3PORT |= (1<<D3PIN);
    else if(!(character &   0b00001000))  D3PORT &= ~(1<<D3PIN);

    if((character &   0b00010000))  D4PORT |= (1<<D4PIN);
    else if(!(character &   0b00010000))  D4PORT &= ~(1<<D4PIN); 

     if((character &   0b00100000))  D5PORT |= (1<<D5PIN);
    else if(!(character &   0b00100000))  D5PORT &= ~(1<<D5PIN);

     if((character &  0b01000000))  D6PORT |= (1<<D6PIN);
    else if(!(character &  0b01000000))  D6PORT &= ~(1<<D6PIN);

     if((character &  0b10000000))  D7PORT |= (1<<D7PIN);
    else if(!(character &  0b10000000))  D7PORT &= ~(1<<D7PIN);

     delay(DELAYBEFOREDISABLE);

     EnablePORT &= ~(1<<EnablePIN);

}

void LCD::delay(uint64_t duration){
    volatile uint64_t i ;
    for(i = 0 ; i<duration ; i++){}
}
void LCD::command_mode(){
    RSPORT &= ~(1<<RSPIN);
}

void LCD::character_mode(){
    RSPORT |= (1<<RSPIN);
}
void LCD::write_mode(){
     RWPORT &= ~(1<<RWPIN);
 }
void LCD::read_mode(){
    RWPORT |= (1<<RWPIN);
}

void LCD::Enable(){
    delay(DELAYBEFOREENABLE);
    EnablePORT |= (1<<EnablePIN);
}

void LCD::send_character(char character){
    write_mode();
    character_mode();
    Enable();
    send_character_to_pins(character);
}

void LCD::send_instruction(char instruction){
    command_mode();
    write_mode();
    Enable();
    send_character_to_pins(instruction);
}
void LCD::initialize(){
    DDIRECTION1 |= (1<<D0PIN); 
    DDIRECTION1 |= (1<<D1PIN);
    DDIRECTION |= (1<<D2PIN);
    DDIRECTION |= (1<<D3PIN);
    DDIRECTION |= (1<<D4PIN);
    DDIRECTION |= (1<<D5PIN);
    DDIRECTION |= (1<<D6PIN);
    DDIRECTION |= (1<<D7PIN);
    SIGNALDIRECTION |= (1<<EnablePIN);
    SIGNALDIRECTION |= (1<<RSPIN);
    SIGNALDIRECTION |= (1<<RWPIN);

    D0PORT &= ~(1<<D0PIN);
    D1PORT &= ~(1<<D1PIN);
    D2PORT &= ~(1<<D2PIN);
    D3PORT &= ~(1<<D3PIN);
    D4PORT &= ~(1<<D4PIN);
    D5PORT &= ~(1<<D5PIN);
    D6PORT &= ~(1<<D6PIN);
    D7PORT &= ~(1<<D7PIN);
    EnablePORT &= ~(1<<EnablePIN);
    RSPORT &= ~(1<<RSPIN);
    RWPORT &= ~(1<<RWPIN);

    
    send_instruction(0b00111000); //set to 8 bit mode
    send_instruction(0b00001110); //display on cursor blinking
    send_instruction(0b00000110);  //increment cursor
    send_instruction(0b10000000); //Force cursor to beginning ( 1st line)
    send_instruction(0b00000001); //clear lcd
    send_instruction(0b00001100); //turn off cursor
    

}
void LCD::clear(){
	send_instruction(0b00000001);
}

void LCD::new_line(){
	send_instruction(0b11000000);
}
void LCD::send_string(char *byte){
    for( ; *byte ; byte++) send_character(*byte);
}