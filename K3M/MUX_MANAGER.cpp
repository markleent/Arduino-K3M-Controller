/*!
 *  @file		MUX_MANAGER.cpp
 *  Project		Multiplexer Manager Library
 *	@brief		Allows manipulation in vectors of n numbers of Multiplexer for the Arduino
 *	Version		0.99
 *  @author		Ken Martel 
 *	@date		24/05/13
 *  License		MIT
 */
#include "MUX_MANAGER.h"

MUXMNG::MUXMNG(int8_t nbMux, int * digitalPorts, int * analogPorts, int * portSize, int8_t * nbInputsMux) {
 
  // Set total number of multiplexers... 
 _nbMux = nbMux;
 // Stores number of Inputs per mux
 _nbInputs = nbInputsMux;
 
  // Instantiate all Mutiplexers together....
 for (int i = 0; i < nbMux; i++) {
  _Mux.push_back(MUX8_16(analogPorts[i], digitalPorts, portSize[i]));
 }
  
 // Initialize the number of Inputs (and buffers per Inputs) as we need to store Mux Values and there Buffers as much as possible...
 // We need to store data a 8bit for later manipulations...
 _Inputs = new int8_t*[nbMux];
 _InputsBuffers = new int8_t*[nbMux];
 
 // Allocation
 for(int8_t i = 0; i < nbMux; i++) {
   _Inputs[i] = new int8_t[nbInputsMux[i]];
   _InputsBuffers[i] = new int8_t[nbInputsMux[i]];
   
   for(int8_t j = 0; j < nbInputsMux[i]; j++) {
      _Inputs[i][j] = 0;
      _InputsBuffers[i][j] = 0;
    }
 }
  
}

MUX8_16 & MUXMNG::getMux(int mux) {
 return _Mux[mux]; 
}

/** Note 
*
* Setting a buffer/input or retreive it should be as safe as possible, so that we don't get an overflow and break the freaking app from running
* Because of this we can just have a master loop with higher boundaries with no risk of breaking it
*
* Ex:
* for (int i = 0; i < 8; i++) {
*  Manager.setInput(0, i);  // Even if the mux accepts only 3 inputs the remaining entries will just be discarded. this is to avoid having to many loops
*}
*
*/
void MUXMNG::setInput(int mux, int input) {
 if(input < _nbInputs[mux]) { // Only set Inputs if the input actually exists (as number of inputs can vary from one mux to another)
   _Inputs[mux][input] = (int8_t) this->getMux(mux).readInput(input); 
 }
}

void MUXMNG::setBuffer(int mux, int input) {
  if(input < _nbInputs[mux]) { // Only set buffers if the input actually exists (as number of inputs can vary from one mux to another)
    _InputsBuffers[mux][input] = _Inputs[mux][input];
  }
}


int8_t * MUXMNG::getNbInputs() {
  return _nbInputs;
}

int8_t MUXMNG::getInput(int mux, int input) {
  if(input < _nbInputs[mux]) {
   return _Inputs[mux][input]; 
  }
  
  return (int8_t) 0;
}

int8_t MUXMNG::getBuffer(int mux, int input) {
  if(input < _nbInputs[mux]) {
    return _InputsBuffers[mux][input];
  }
  
  return (int8_t) 0;
}
