/*!
 *  @file		MUX_MANAGER.h
 *  Project		Multiplexer Manager Library
 *	@brief		Allows manipulation in vectors of n numbers of Multiplexer for the Arduino
 *	Version		0.99
 *  @author		Ken Martel 
 *	@date		24/05/13
 *  License		MIT
 */
#ifndef __MUX_MANAGER_H
#define __MUX_MANAGER_H

#include <StandardCplusplus.h>
#include <vector>
#include "MUX8_16.h"

class MUXMNG {
  public:  
    MUXMNG(int8_t nbMux, int * digitalPorts, int * analogPorts, int * portSize, int8_t * nbInputsMux);
    MUX8_16 & getMux(int mux);
    void setInput(int mux, int input);
    void setBuffer(int mux, int input);
    int8_t getInput(int mux, int input);
    int8_t getBuffer(int mux, int input);
    int8_t * getNbInputs();
  
  private:  
    std::vector<MUX8_16> _Mux;
    int8_t ** _Inputs;
    int8_t ** _InputsBuffers;
    int8_t _nbMux;
    int8_t * _nbInputs;
};

#endif
