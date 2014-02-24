/*!
 *  @file		K3M_MAIN.h
 *  Project		SysEx Pseudo Syntheziser Generator Library (Specific for Kawai K3M)
 *	@brief		Control and create sounds from an analog panel to a K3M Synt, with Lcd display of parameter change for the Arduino
 *	Version		0.99
 *  @author		Ken Martel 
 *	@date		24/05/13
 *  License		MIT
 */
#ifndef _K3M_MAIN_H
#define _K3M_MAIN_H
#include <StandardCplusplus.h>
#include <vector>
#include "MUX_MANAGER.h"
#include <T6963.h>
#include "MIDI.h"
#include "CONFIG.h"

class K3M_CLASS {
  public:
    K3M_CLASS(MUXMNG &Manager, MIDI_Class &Midi, T6963 &Lcd);
    void setup(std::vector< std::vector<byte> > & control, std::vector< std::vector<int8_t> > & ranges, byte * sysEx);
    void setup(byte * sysEx);
    void run(void);
  
  private:
    int8_t mappedValue(int mux, int input);
    void sendSysEx(int mux, int input);
    void displayMsg(int mux, int input);
    byte * _sysEx;
    std::vector< std::vector<byte> > _controls;
    std::vector< std::vector<int8_t> > _ranges;
    MUXMNG *_MNGR;
    MIDI_Class *_Midi;
    T6963 *_Lcd;
};

#endif
