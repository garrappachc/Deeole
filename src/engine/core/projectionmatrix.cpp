/*
 * projectionmatrix.cpp
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

#include "projectionmatrix.h"

namespace Dee {

void ProjectionMatrix::ortho(float left, float right, float bottom, float top, float near, float far) {
  loadIdentity();
  
  at(0, 0) = 2.0f / (right - left);
  at(1, 1) = 2.0f / (top - bottom);
  at(2, 2) = -2.0f / (far - near);  
  
  at(0, 3) = 0 - ((right + left) / (right - left));
  at(1, 3) = 0 - ((top + bottom) / (top - bottom));
  at(2, 3) = 0 - ((far + near) / (far - near));
  
  at(3, 3) = 1.0f;
}

void ProjectionMatrix::perspective(float fovy, float aspect, float zNear, float zFar) {
  DeeAssert(zNear);
  loadIdentity();
  
  float f = 1.0f / (tan(deg2Rad(fovy) / 2.0f));
  
  at(0, 0) = f / aspect;
  at(1, 1) = f;
  at(2, 2) = (zFar + zNear) / (zNear - zFar);
  at(2, 3) = (2 * zFar * zNear)  / (zNear - zFar);
  at(3, 2) = -1.0f;
}

} /* namespace Dee */
