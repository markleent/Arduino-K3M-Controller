/*!
 *  @file		UTILS.cpp
 *  Project		UTILS General Purpose Library
 *	@brief		UTILS General Purpose Library for the Arduino
 *	Version		0.99
 *  @author		Ken Martel 
 *	@date		24/05/13
 *  License		MIT
 */
#include "Arduino.h"
#include "UTILS.h"

char charBuffer[4];
const char* charDefault = "0";
const char* charPlusSign = "+";

char* UTILS::intToCharArray(int i, int maxValue) {
  
  if (maxValue > 0) {
   i = map(i, 0, 127, 0, maxValue); 
  }
  else if ( maxValue < 0 ) { // Si le max value est negatif, renvoye une balance a la place.
   return UTILS::intToBalance(i, -maxValue); 
  }
  
  String str = String(i);

  str.toCharArray(charBuffer, 4);
  
  if (str.length() == 2) {
    charBuffer[2] = charBuffer[1];
    charBuffer[1] = charBuffer[0];
    charBuffer[0] = charDefault[0];
  }
  else if (str.length() == 1) {
    charBuffer[2] = charBuffer[0];
    charBuffer[1] = charDefault[0];
    charBuffer[0] = charDefault[0];
  }
 
  return charBuffer;
}

char* UTILS::intToBalance(int i, int maxValue) {
  
  if (maxValue != 0) {
    i = map(i, 0, 127, -maxValue, maxValue);
  }
  else {
   i = map(i, 0, 127, -63, 63); 
  }
  
  String str = String(i);
  
  str.toCharArray(charBuffer, 4);
  
  if (str.length() == 2 && i > 0) {
  charBuffer[2] = charBuffer[1];
  charBuffer[1] = charBuffer[0];
  charBuffer[0] = charPlusSign[0];
  }
  else if (str.length() == 2 && i < 0) {
  charBuffer[2] = charBuffer[1];
  charBuffer[1] = charDefault[0];
  } 
  else if (str.length() == 1 && i == 0) {
  charBuffer[2] = charBuffer[0];
  charBuffer[1] = charDefault[0];
  charBuffer[0] = charDefault[0];  
  } 
  else if (str.length() == 1 && i > 0) {
  charBuffer[2] = charBuffer[0];
  charBuffer[1] = charDefault[0];
  charBuffer[0] = charPlusSign[0];
  }
  
  return charBuffer;
}

int8_t UTILS::mapTo(int8_t i, int8_t maxValue) {
  if ( maxValue < 0 ) { // Si la valeur max d'entree est negative renvoyer la valeur -maxValue a +maxValue
    return UTILS::mapToBalance(i, -maxValue);
  }
  return (int8_t) map(i, 0, 127, 0, maxValue);
}

int8_t UTILS::mapToBalance(int8_t i, int8_t maxValue) {
  return (int8_t) map(i, 0, 127, -maxValue, maxValue);
}

byte UTILS::getHighByte_8(int8_t i) {
  return (i >= 0) ? (byte) (i >> 4) : (byte) (abs(i) >> 4) + 0x08 ;        
}

byte UTILS::getLowByte_8(int8_t i) {
  return (byte) (abs(i)) & 0x0F;
}

