// HDSP2000 libray written by N.K  4th March 2025
// Version 0.1

#ifndef HDSP2000_H
#define HDSP2000_H

#include <Arduino.h>
#include <avr/pgmspace.h>

// Pin definitions
#define COL1_PIN   2
#define COL2_PIN   3
#define COL3_PIN   4
#define COL4_PIN   5
#define COL5_PIN   6

#define VB_PIN     A5
#define DATAIN_PIN 8
#define CLOCK_PIN  7

class HDSP2000 {
  public:
    HDSP2000();
    void begin();
    void setText(const uint8_t *txt);      // expects an array of 4 characters
    void refresh();                        // to be called from Timer1 ISR
  private:
    volatile uint8_t _currentColumn;
    volatile uint8_t _czas;
    uint8_t _text[4];
    void displayColumn();
    void selectColumn(uint8_t col);
    uint8_t reverse_bits(uint8_t b);
};

extern HDSP2000 display;

#endif
