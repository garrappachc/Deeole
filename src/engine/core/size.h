/*
 * size.h
 * Copyright (C) 2014  Michał Garapich <michal@garapich.pl>
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

#ifndef SIZE_H
#define SIZE_H

#include <ostream>

#include "core/deeglobal.h"

namespace Dee {

/**
 * \ingroup Core
 * @{
 * 
 * The Size class is used to describe a 2-dimensional object's size.
 * 
 * The size is described by _width_ and _height_ parameters. They can
 * be set in the constructor or by setWidth() and setHeight() methods.
 * To check if either width or height is zero (the size is null), you can
 * user isNull() method.
 */
class __DeeExport__ Size {
  
public:
  
  /**
   * Construct a null size.
   * 
   * \sa isNull().
   */
  Size();
  
  /**
   * Constructs a size with the given _width_ and _height_.
   * 
   * \param width The _width_ param value.
   * \param height The _height_ param value.
   */
  Size(int width, int height);
  
  /**
   * Sets _width_ to the given value.
   * 
   * \param width The new _width_ value.
   * \sa setHeight().
   */
  void setWidth(int width);
  
  /**
   * Sets _height_ to the given value.
   * 
   * \param height The new _height_ value.
   * \sa setWidth().
   */
  void setHeight(int height);
  
  /**
   * Returns true if either _width_ or _height_ is 0; otherwise returns false.
   * 
   * \return True if either _width_ or _height_ is equal to 0.
   */
  bool isNull() const;
  
  inline int height() const {
    return __height;
  }
  
  inline int width() const {
    return __width;
  }
  
private:
  int __width;
  int __height;
  
  
}; /** @} */

} /* namespace Dee */

#endif // SIZE_H
