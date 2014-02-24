/*!
 *  @file		MUX8_16.h
 *  Project		Generic Multiplexer Controller Library
 *	@brief		Allows the control of Multiplexers for 8 or 16 analog inputs for the Arduino
 *	Version		0.99
 *  @author		Ken Martel 
 *	@date		24/05/13
 *  License		MIT
 */
#ifndef MUX816_H
#define MUX816_H

#include "Arduino.h"

/*
 * MUX8_16 class compatible with 4051 multiplexer/demultiplexer and equivalent 16 input/outputs mux
 *
 *
 *
 * @author : MK 
 *
 */
 
class MUX8_16 {
  public:
  MUX8_16(int analogPort, int * comPorts, int comLen); // Default Constructor/initializer that takes an analog port and an int array as com port
  MUX8_16(int * comPorts, int comLen); // Overloaded Method, if the analogPort is A0
  void setup(void);
  byte readInput(int pota);
  int getSize();
  
  private:
  int _analogPort;
  int * _comPorts;
  int _comLen;
  void selectInput(int pota);
  void init(int analogPort, int * comPorts, int comLen);
  int current_value;
  
};

#endif
