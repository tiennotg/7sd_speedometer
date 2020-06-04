/*
 * schmitt_trigger.cpp
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

#include <Arduino.h>
#include "schmitt_trigger.h"

SchmittTrigger::SchmittTrigger(int analogPin, int lowThreshold, int highThreshold) : analogPin(analogPin), lowThreshold(lowThreshold), highThreshold(highThreshold), isHighThresholdActive(true)
{}

bool SchmittTrigger::run()
{
  int value = analogRead(this->analogPin);
  if (this->isHighThresholdActive)
  {
    if (value >= this->highThreshold)
    {
      this-> isHighThresholdActive = false;
      return true;
    }
    else
      return false;
  }
  else
  {
    if (value <= this->lowThreshold)
    {
      this-> isHighThresholdActive = true;
      return false;
    }
    else
      return true;
  }
}
