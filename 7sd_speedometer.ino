/*
 * 7sd_speedometer.ino
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

#include <Chrono.h>
#include "7sd_speedometer.h"
#include "schmitt_trigger.h"
#include "seven_segment_display.h"

Chrono displayChrono;
Chrono measureChrono;
Chrono measureTimeoutChrono;
SchmittTrigger schmittTrigger(analogPin, lowThreshold, highThreshold);

SevenSegmentDisplay ssd(displayCharCount);

float speed = 0;
bool prevValue = true;

void speedCalculation()
{
  float diff = float(measureTimeoutChrono.elapsed()) / 3600000.0;
  speed = wheelDistance / diff;
}

void setup()
{
  ssd.print("  "); // init 7-segment displays
}

void loop()
{
  if (measureTimeoutChrono.hasPassed(measureTimeout)) // if we're waiting for a wheel turn for too long,
                                                      // the speed is zero.
  {
    speed = 0; // Don't need to restart the chrono here, because it's done when a wheel turn is done.
  }
  
  if (measureChrono.hasPassed(measurePeriod)) // when a period is elapsed, do a new measure
  {
    measureChrono.restart();
    
    bool value = schmittTrigger.run();
    if ((value != prevValue) && prevValue) // triggers on falling front, if the wheel did a turn
    {
      if (measureTimeoutChrono.elapsed() > measureMinimalGap) // prevent outliers
      {
        speedCalculation();
        measureTimeoutChrono.restart();
      }
    }
    prevValue = value;
    ssd.refreshDisplay();
  }

  if (displayChrono.hasPassed(displayPeriod)) // when a period is elapsed, refresh the speed display
  {
    displayChrono.restart();
    ssd.print(speed);
  }
}
