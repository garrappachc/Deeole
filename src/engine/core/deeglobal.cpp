/*
 * deeglobal.cpp
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

#include <iostream>
#include <exception>
#include <cmath>

#include "deeglobal.h"

void dee_assert(const char* cond, const char* file, int line) {
  std::cout << "DeeAssert FAILED:" << std::endl <<
    "  Condition: " << cond << std::endl <<
    "  File: " << file << std::endl <<
    "  Line: " << line << std::endl;
  std::terminate();
}

namespace Dee {

float sin(float angle) {
  return static_cast<float>(::sin(static_cast<double>(angle)));
}

float cos(float angle) {
  return static_cast<float>(::cos(static_cast<double>(angle)));
}

}
