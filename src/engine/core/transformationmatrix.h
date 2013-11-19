/*
 * transformationmatrix.h
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

#ifndef TRANSFORMATIONMATRIX_H
#define TRANSFORMATIONMATRIX_H

#include "core/deeglobal.h"

#include "core/matrix.h"
#include "core/point.h"
#include "core/vector.h"

namespace Dee {

class __DeeExport__ TransformationMatrix : public Matrix4d {
  
public:
  TransformationMatrix& operator =(const Matrix4d& other);
  
  TransformationMatrix& translate(const Vector3d& vector);
  
  TransformationMatrix& rotate(float angle, Axis axis);
  TransformationMatrix& rotate(float angle, const Vector3d& vector);
  
};

} /* namespace Dee */

#endif // TRANSFORMATIONMATRIX_H
