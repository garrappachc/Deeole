/*
 * mouse.cpp
 * Copyright (C) 2013  Michał Garapich <michal@garapich.pl>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "mouse.h"

namespace Dee {
  
Mouse::Mouse() :
    __x(0),
    __y(0),
    __dx(0),
    __dy(0) {}

void Mouse::motionEvent(int x, int y) {
  static bool initialized = false;
  
  if (!initialized) {
    __x = x;
    __y = y;
    initialized = true;
  }
  
  __dx = __x - x;
  __x = x;
  
  __dy = y - __y;
  __y = y;
}

void Mouse::clearDiff() {
  __dx = __dy = 0;
}

} /* namespace Dee */
