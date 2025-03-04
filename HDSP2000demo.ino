#include "HDSP2000.h"

uint8_t txt[4] = {'H','D','S','P'};
uint8_t textscroll[11] = {'T','E','X','T',' ','S','C','R','O','L','L'};

void setup() {
  display.begin();
  display.setText(txt);
  delay(2000);
}

void loop() {
  // Libray runs on interrupts, so delay() is working, but i prefer using delays based on millis()
  
  txt[0] = '2';
  txt[1] = '0';
  txt[2] = '0';
  txt[3] = '0';
  display.setText(txt);
  delay(2000);
  txt[0] = 'D';
  txt[1] = 'E';
  txt[2] = 'M';
  txt[3] = 'O';
  display.setText(txt);
  delay(2000);
  
  // If you want to display digit add 48 to the value in table

  for (uint8_t x = 0; x < 10; x++){
    txt[0] = 48 + x;               
    txt[1] = 48 + x;
    txt[2] = 48 + x;
    txt[3] = 48 + x;
    display.setText(txt);
    delay(500);    
  }

  //Clean display

  txt[0] = 0;               
  txt[1] = 0;
  txt[2] = 0;
  txt[3] = 0;

  //Example of text scroll

  for (uint8_t x = 0; x < 13; x++){
    display.setText(txt);
    txt[0] = txt[1];               
    txt[1] = txt[2];
    txt[2] = txt[3];
    txt[3] = textscroll[x];
    delay(400);    
  }

  //Variable counting
  
  for (uint8_t x = 0; x < 200; x++){
    display.setText(txt);
    txt[0] = 'E';               
    txt[1] = (x / 100) + 48;
    uint8_t y = x;
    if(x >= 100){
      y = y - 100;
    }
    txt[2] = (y / 10) + 48;
    txt[3] = (x % 10) + 48;
    delay(50);    
  }

  //Clean display

  txt[0] = 0;               
  txt[1] = 0;
  txt[2] = 0;
  txt[3] = 0;

  //All pixel test

  for (uint8_t x = 0; x < 5; x++){
    display.setText(txt);
    txt[0] = txt[1];               
    txt[1] = txt[2];
    txt[2] = txt[3];
    txt[3] = 219;
    delay(400);    
  }

  delay(3000);

  for (uint8_t x = 0; x < 5; x++){
    display.setText(txt);
    txt[0] = txt[1];               
    txt[1] = txt[2];
    txt[2] = txt[3];
    txt[3] = 0;
    delay(400);    
  }

  //ASCII font 5x7 demo

  for (uint8_t x = 0; x < 255; x++){
    display.setText(txt);
    txt[0] = txt[1];               
    txt[1] = txt[2];
    txt[2] = txt[3];
    txt[3] = x;
    delay(300);    
  }   
}
