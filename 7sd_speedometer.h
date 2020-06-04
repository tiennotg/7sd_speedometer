/*
 * 7sd_speedometer.h
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

#ifndef COMPTEUR_H
#define COMPTEUR_H

const int analogPin = 0;              // pin connected to the Hall effect sensor
const float wheelDistance = 0.002198; // equals to D*Pi (in km!!)
const int displayCharCount = 2;       // number of 7-segment displays

const unsigned long measurePeriod = 1;      // in ms (refresh rate for measurement and 7-segment displays)
const unsigned long displayPeriod = 250;    // in ms (refresh rate for speed display)
const unsigned long measureTimeout = 3000;  // in ms (beyond this time, considers that speed falls to 0)
const unsigned long measureMinimalGap = 72; // in ms (to remove outliers... 72ms means a speed of 110km/h!)

// Thresholds for analog detection
const int lowThreshold = 1;
const int highThreshold = 10;

#endif
