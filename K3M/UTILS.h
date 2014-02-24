/*!
 *  @file		UTILS.h
 *  Project		UTILS General Purpose Library
 *	@brief		UTILS General Purpose Library for the Arduino
 *	Version		0.99
 *  @author		Ken Martel 
 *	@date		24/05/13
 *  License		MIT
 */
#ifndef UTILS_H
#define UTILS_H

class UTILS {
  public:
  static char* intToCharArray(int i, int maxValue = 0);
  static char* intToBalance(int i, int maxValue = 0);
  static int8_t mapTo(int8_t i, int8_t maxValue);
  static int8_t mapToBalance(int8_t i, int8_t maxValue);
  static byte getHighByte_8(int8_t i);
  static byte getLowByte_8(int8_t i);
};

#endif
