/*
 * seven_segment_display.cpp
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

#include "seven_segment_display.h"

SevenSegmentDisplay::SevenSegmentDisplay(int charCount)
{
  if (charCount <= 0 || charCount > maxCharCount)
    this->charCount = 1;
  else
    this-> charCount = charCount;

  this->charArray = new byte[charCount];
  this->charPointer = -1;

  for (int i=0; i<8; i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }

  for (int i=this->firstCharSelectPin; i<this->firstCharSelectPin+charCount; i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
}

SevenSegmentDisplay::~SevenSegmentDisplay()
{
  delete this->charArray;
}

void SevenSegmentDisplay::print(const char s[])
{
  for (int i=0; i<this->charCount; i++)
  {
    if (s[i]>=0x30 && s[i]<=0x39) // numbers
      this->charArray[i] = this->matrix[s[i]-0x30];
    else if (s[i]=='-')
      this->charArray[i] = this->matrix[10];
    else if (s[i]=='.')
      this->charArray[i] = this->matrix[11];
    else if (s[i]=='=')
      this->charArray[i] = this->matrix[12];
    else if (s[i]==' ')
      this->charArray[i] = this->matrix[13];
    else
      this->charArray[i] = this->matrix[14];
  }
}

void SevenSegmentDisplay::print(const float f)
{
  this->print((int) round(f));
}

void SevenSegmentDisplay::print(const int i)
{
  if (i>=pow(10,this->charCount) || i<=-pow(10,this->charCount-1))
  {
    char* s = new char[this->charCount];
    for (int j=0; j<this->charCount; j++)
      s[j] = '-';
    this->print(s);
    delete s;
  }
  else
  {
    unsigned int k = abs(i);
    unsigned int l = (k/10)*10;
    for (int p = this->charCount-1; p>=0; p--)
    {
      this->charArray[p] = this->matrix[k-l];
      k=k/10;
      l=(k/10)*10;
    }

    if (i<0)
      this->charArray[0] = this->matrix[10];
  }
}

void SevenSegmentDisplay::refreshDisplay()
{
  if (this->charPointer >= 0)
    digitalWrite(this->charPointer+this->firstCharSelectPin,LOW);
  
  this->charPointer++;
  if (this->charPointer >= this->charCount)
    this->charPointer = 0;
  
  PORTD = this->charArray[this->charCount-this->charPointer-1];
  
  digitalWrite(this->charPointer+this->firstCharSelectPin,HIGH);
}
