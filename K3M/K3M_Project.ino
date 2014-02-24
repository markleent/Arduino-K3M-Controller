/*!
 *  @file		K3M_PROJECT.ino
 *  Project		K3M SysEx based Arduino Controller
 *	@brief		Create sounds with a Kawai K3M Synth and a Arduino Microcontroller !!!
 *	Version		0.99
 *  @author		Ken Martel 
 *	@date		24/05/13
 *  License		MIT
 */
#include <StandardCplusplus.h>
#include <vector>

#include "MIDI.h"
#include <T6963.h>
#include "MUX_MANAGER.H"
#include "CONFIG.h"
#include "K3M_MAIN.h"

// Communication ports to work with multiplexers

int comPorts[] = {
  2, 3, 4};
int analogPorts[] = {
  0, 1, 2}; 
int portSize[] = {
  3, 3, 3};
int8_t nbInputsPerMux[] = {
  8, 8, 5};

// K3M sysEx Template
byte sysEx[] = {0x40, 0x00, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00};

// Multiplexer Manager
MUXMNG Manager(3, comPorts, analogPorts, portSize, nbInputsPerMux);

// LCD Instance
T6963 LCD(240, 64, 6, 32);

// Main Program
K3M_CLASS K3M(Manager, MIDI, LCD);

// Debug Utility
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

// Init Ardunino
void setup() {
    
  // Setup K3M
  K3M.setup(sysEx);
  
  // For debug only
  //Serial.begin(9600);
  //Serial.println("\n[memCheck]");
  //Serial.println(freeRam());
}

// Main
void loop() {
  
  // ...
  K3M.run();
 
  
  // Wait, can be put to Zero
  delay(50);
}
