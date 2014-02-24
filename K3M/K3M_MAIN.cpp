/*!
 *  @file		K3M_MAIN.cpp
 *  Project		SysEx Pseudo Syntheziser Generator Library (Specific for Kawai K3M)
 *	@brief		Control and create sounds from an analog panel to a K3M Synt, with Lcd display of parameter change for the Arduino
 *	Version		0.99
 *  @author		Ken Martel 
 *	@date		24/05/13
 *  License		MIT
 */
#include "K3M_MAIN.h"
#include "MUX_MANAGER.h"
#include "UTILS.h"
#include "CONFIG.h"

// Permet l'optimisation. Pas de trucs en mémoire mais dans le binaire. 
static byte ctrlTemp[MAXMUX][MAXCTRLS] = {
  {0x01, 0x02, 0x27, 0x04, 0x07, 0x1C, 0x1E, 0x1A},
  {0x14, 0x15, 0x17, 0x18, 0x0E, 0x0F, 0x11, 0x12},
  {0x1D, 0x0C, 0x0B, 0x0A, 0x13, 0x00, 0x00, 0x00}
};

// Range des boutons/potentiometres
static int8_t rangeTemp[MAXMUX][MAXCTRLS] = {
   {33, 2, 7, -15, 33, 31, 31, 99},
   {31, 31, 31, 31, 31, 31, 31, 31},
   {31, 31, 31, 99, 31, 0, 0, 0}
};

static char* dictionary[MAXMUX][MAXCTRLS] = {
    {"Oscillator1: ", "Range      : ", "Chorus      : ", "Balance    : ", "Oscillator2: ", "LFO OSC    : ", "LFO VCA    : ", "LFO SPEED  : "},
    {"VCA ATTACK : ", "VCA DELAY  : ", "VCA SUSTAIN: ", "VCA RELEASE : ", "VCF ATTACK : ", "VCF DELAY  : ", "VCF SUSTAIN: ", "VCF RELEASE: "},
    {"LFO VCF    : ", "HighPassFil: ", "Resonance  : ", "CutOff      : ", "Level      : ", "Placeholder1:", "Placeholder2:", "PlaceHolder3:"}
};

// Inject pointers of  Multiplexer manager, Midi and LCD class into the main program
K3M_CLASS::K3M_CLASS(MUXMNG &Manager, MIDI_Class &Midi, T6963 &Lcd)
: _controls(MAXMUX, std::vector<byte>(MAXCTRLS)), _ranges(MAXMUX, std::vector<int8_t>(MAXCTRLS))
{
  _MNGR = &Manager;
  _Midi = &Midi;
  _Lcd = &Lcd;
}


//void K3M_CLASS::setup(std::vector< std::vector<byte> > & control, std::vector< std::vector<int8_t> > & ranges, byte * sysEx) {
void K3M_CLASS::setup(byte * sysEx) {  
  
  for (int i = 0; i < MAXMUX; i++) {
    _controls[i].assign(ctrlTemp[i], ctrlTemp[i] + MAXCTRLS);
    _ranges[i].assign(rangeTemp[i], rangeTemp[i] + MAXCTRLS);
  }
  
  _sysEx = sysEx;
  _Lcd->Initialize();
  _Lcd->TextGoTo(13,0);
  _Lcd->writeString("K3m Controler");
  _Midi->begin(MIDI_CHANNEL_OMNI);
}

void K3M_CLASS::run() {  
    for (int j = 0; j < MAXCTRLS; j++) {
     
      if (abs(_MNGR->getInput(0, j) - _MNGR->getBuffer(0, j)) > 1 && _MNGR->getNbInputs()[0] > j) { 
          
          _MNGR->setBuffer(0, j);
          this->sendSysEx(0, j);
          this->displayMsg(0, j);
      }
      
      if (abs(_MNGR->getInput(1, j) - _MNGR->getBuffer(1, j)) > 1 && _MNGR->getNbInputs()[1] > j) { 
          
          _MNGR->setBuffer(1, j);
          this->sendSysEx(1, j);
          this->displayMsg(1, j);
      }
      
      if (abs(_MNGR->getInput(2, j) - _MNGR->getBuffer(2, j)) > 1 && _MNGR->getNbInputs()[2] > j) { 
          
          _MNGR->setBuffer(2, j);
          this->sendSysEx(2, j);
          this->displayMsg(2, j);
      }
      
      _MNGR->setInput(0, j);
      _MNGR->setInput(1, j);
      _MNGR->setInput(2, j);
    }
}


void K3M_CLASS::displayMsg(int mux, int input) {
      _Lcd->TextGoTo(1, 4);
      _Lcd->writeString(dictionary[mux][input]);
      _Lcd->TextGoTo(22, 4);
      _Lcd->writeString(UTILS::intToCharArray(_MNGR->getInput(mux, input) , _ranges[mux][input]));
}


void K3M_CLASS::sendSysEx(int mux, int input) {
  // Get actual Value
  int8_t mapped = this->mappedValue(mux, input);
  // Populate sys Ex message
  _sysEx[5] = _controls[mux][input];
  _sysEx[6] = UTILS::getHighByte_8(mapped); 
  _sysEx[7] = UTILS::getLowByte_8(mapped); 
  // Send through MIDI
 _Midi->sendSysEx(8, _sysEx);
} 

int8_t K3M_CLASS::mappedValue(int mux, int input) {
  int8_t val = _MNGR->getInput(mux, input);
  int8_t range = _ranges[mux][input];
  return (int8_t) UTILS::mapTo(val, range);
}

