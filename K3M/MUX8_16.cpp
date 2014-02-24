/*!
 *  @file		MUX8_16.cpp
 *  Project		Generic Multiplexer Controller Library
 *	@brief		Allows the control of Multiplexers for 8 or 16 analog inputs for the Arduino
 *	Version		0.99
 *  @author		Ken Martel 
 *	@date		24/05/13
 *  License		MIT
 */
#include "Arduino.h"
#include "MUX8_16.h"


MUX8_16::MUX8_16(int analogPort, int * comPorts, int comLen) {
  init(analogPort, comPorts, comLen);
}

MUX8_16::MUX8_16(int * comPorts, int comLen) {
  init(A0, comPorts, comLen);
}

// This is a common method for the constructors DRY
void MUX8_16::init(int analogPort, int * comPorts, int comLen) {
  _analogPort = analogPort;
  _comPorts = comPorts;
  _comLen = comLen;
  setup();
}

void MUX8_16::setup(void) {
  
  pinMode(_comPorts[0], OUTPUT);
  pinMode(_comPorts[1], OUTPUT);
  pinMode(_comPorts[2], OUTPUT);
  
  if (_comLen > 3) {
    pinMode(_comPorts[3], OUTPUT);
  }

}

byte MUX8_16::readInput(int pota) {
  selectInput(pota);
  current_value = ceil(analogRead(_analogPort)/8);
  return current_value;
}

void MUX8_16::selectInput(int pota) {
  
  digitalWrite(_comPorts[0], pota & 0x01);
  digitalWrite(_comPorts[1], ((pota>>1) & 0x01));
  digitalWrite(_comPorts[2], ((pota>>2) & 0x01)); 
  
  if (_comLen > 3) {
    digitalWrite(_comPorts[3], ((pota>>3) & 0x01)); 
  }
  
}

// Debug only ;)  
int MUX8_16::getSize() {
  return _comLen;
}
