/*
 * color.cpp
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

#include <map>
#include <utility>

#include "utils/logger.h"

#include "color.h"

namespace Dee {
  
static const std::map<std::string, Color> ColorMap({
  std::make_pair("black", Color(0, 0, 0)),
  std::make_pair("white", Color(255, 255, 255)),
  std::make_pair("red",   Color(255, 0, 0)),
  std::make_pair("green", Color(0, 255, 0)),
  std::make_pair("blue",  Color(0, 0, 255))
});
  
Color::Color() :
    __r(0),
    __g(0),
    __b(0),
    __a(255) {}

Color::Color(int r, int g, int b, int a) :
    __r(r),
    __g(g),
    __b(b),
    __a(a) {}

Color::Color(const std::string& name) {
  if (ColorMap.count(name) > 0) {
    *this = ColorMap.find(name)->second;
  } else {
    Logger::warning("Color: invalid color name: %s", name);
  }
}



} /* namespace Dee */
