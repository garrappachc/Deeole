/*
 * color.h
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

#ifndef COLOR_H
#define COLOR_H

#include <string>

#include "core/deeglobal.h"

namespace Dee {

/**
 * \ingroup Core
 * @{
 * 
 * The Color class provides various colors support.
 * 
 * As OpenGL uses rgba values, this is the default format.
 */
class __DeeExport__ Color {
  
public:
  
  /**
   * Constructs just black, opaque color.
   */
  Color();
  
  /**
   * Constructs the color based on the given RGBA values.
   * \param r The red value.
   * \param g The green value.
   * \param b The blue value.
   * \param a The alpha value.
   */
  Color(int r, int g, int b, int a = 255);
  
  Color(float r, float g, float b, float a = 1.0f);
  
  /**
   * Constructs color from the given name.
   * 
   * The available names are:
   * - black
   * - white
   * - red
   * - green
   * - blue
   * - yellow
   */
  Color(const std::string& name);
  
  void dumpTo(float* array) const;
  
  inline const float r() const {
    return __r;
  }
  
  inline const float g() const {
    return __g;
  }
  
  inline const float b() const {
    return __b;
  }
  
  inline const float a() const {
    return __a;
  }
  
  Color(const Color& other) = default;
  Color(Color&& other) = default;
  Color& operator =(const Color& other) = default;
  
private:
  float __r;
  float __g;
  float __b;
  float __a;
  
}; /** @} */

} /* namespace Dee */

#endif // COLOR_H
