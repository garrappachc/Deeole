/*
 * projectionmatrix.h
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

#ifndef PROJECTIONMATRIX_H
#define PROJECTIONMATRIX_H

#include "core/deeglobal.h"

#include "core/matrix.h"

namespace Dee {

class __DeeExport__ ProjectionMatrix : public Matrix4d {
  
public:
  
  void ortho(float left, float right, float bottom, float top, float near, float far);
  
  void perspective(float fovy, float aspect, float zNear, float zFar);
  
  
};

} /* namespace Dee */

#endif // PROJECTIONMATRIX_H
