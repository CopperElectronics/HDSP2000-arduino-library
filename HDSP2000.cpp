// HDSP2000 libray written by N.K  4th March 2025
// Version 0.1

#include "HDSP2000.h"
#include "font5x7.h"
#include <avr/interrupt.h>
#include <util/delay.h>

HDSP2000 display;

HDSP2000::HDSP2000() : _currentColumn(1), _czas(0) {
  _text[0] = ' ';
  _text[1] = ' ';
  _text[2] = ' ';
  _text[3] = ' ';
}

void HDSP2000::begin() {
  pinMode(COL1_PIN, OUTPUT);
  pinMode(COL2_PIN, OUTPUT);
  pinMode(COL3_PIN, OUTPUT);
  pinMode(COL4_PIN, OUTPUT);
  pinMode(COL5_PIN, OUTPUT);
  pinMode(VB_PIN, OUTPUT);
  pinMode(DATAIN_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  
  digitalWrite(VB_PIN, LOW);
  digitalWrite(COL1_PIN, LOW);
  digitalWrite(COL2_PIN, LOW);
  digitalWrite(COL3_PIN, LOW);
  digitalWrite(COL4_PIN, LOW);
  digitalWrite(COL5_PIN, LOW);
  
  cli();
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS11);
  OCR1A = 499;  // 4 kHz
  TIMSK1 |= (1 << OCIE1A);
  sei();
  
  _currentColumn = 1;
  _czas = 0;
}

void HDSP2000::setText(const uint8_t *txt) {
  for (uint8_t i = 0; i < 4; i++) {
    _text[i] = txt[3 - i];
  }
}

void HDSP2000::refresh() {
  if (_czas == 0) {
    selectColumn(_currentColumn);
    displayColumn();
    digitalWrite(VB_PIN, HIGH);
  }
  _czas++;
  if (_czas == 5) {
    digitalWrite(VB_PIN, LOW);
    _currentColumn++;
    if (_currentColumn > 5) _currentColumn = 1;
    _czas = 0;
  }
}

void HDSP2000::displayColumn() {
  uint32_t data = 0;
  uint8_t colIndex = _currentColumn - 1;
  for (uint8_t d = 0; d < 4; d++) {
    uint8_t colData = font5x7[_text[d]][colIndex] & 0x7F;
    colData = reverse_bits(colData);
    data |= ((uint32_t)colData) << (d * 7);
  }
  for (uint8_t i = 0; i < 28; i++) {
    if (data & 0x01) PORTB |= _BV(PB0);
    else PORTB &= ~_BV(PB0);
    PORTD |= _BV(PD7);
    _delay_us(1);
    PORTD &= ~_BV(PD7);
    data >>= 1;
  }
}

void HDSP2000::selectColumn(uint8_t col) {
  PORTD &= ~(_BV(PD2) | _BV(PD3) | _BV(PD4) | _BV(PD5) | _BV(PD6));
  switch(col) {
    case 1: PORTD |= _BV(PD2); break;
    case 2: PORTD |= _BV(PD3); break;
    case 3: PORTD |= _BV(PD4); break;
    case 4: PORTD |= _BV(PD5); break;
    case 5: PORTD |= _BV(PD6); break;
    default: break;
  }
}

uint8_t HDSP2000::reverse_bits(uint8_t b) {
  b = (b >> 4) | (b << 4);
  b = ((b & 0xCC) >> 2) | ((b & 0x33) << 2);
  b = ((b & 0xAA) >> 1) | ((b & 0x55) << 1);
  b >>= 1;
  return b;
}

ISR(TIMER1_COMPA_vect) {
  display.refresh();
}
