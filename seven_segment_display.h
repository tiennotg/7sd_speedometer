/*
 * seven_segment_display.h
 * 
 * Copyright 2020 Guilhem Tiennot <contact@tiennotblog.fr>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 * 
 */
 
#ifndef SEVEN_SEGMENT_DISPLAY_H
#define SEVEN_SEGMENT_DISPLAY_H

#include "Arduino.h"

const int maxCharCount = 5;

class SevenSegmentDisplay
{
  public:
  SevenSegmentDisplay(int charCount);
  ~SevenSegmentDisplay();

  void print(const char s[]);
  void print(const float f);
  void print(const int i);
  void refreshDisplay();
  
  private:
  byte *charArray;
  int charPointer;
  int charCount;

  /*
   * Pattern with digital pin numbers :
   * 
   *   111
   *  2   0
   *  2   0
   *   333
   *  7   5
   *  7   5
   *   666  4
   */

  const int firstCharSelectPin = 8;
  const byte matrix[15] = {0xE7,0x21,0xCB,0x6B,0x2D, // numbers (0..4)
                           0x6E,0xEE,0x23,0xEF,0x6F, // numbers (5..9)
                           0x08,0x10,0x48,0x00,0x4A};// - . = space and others
};

#endif
