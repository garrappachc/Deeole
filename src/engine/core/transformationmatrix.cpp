/*
 * transformationmatrix.cpp
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

#include "transformationmatrix.h"

namespace Dee {

TransformationMatrix& TransformationMatrix::operator=(const Matrix4d& other) {
  Matrix4d::operator =(other);
}

void TransformationMatrix::rotate(float angle, Axis axis) {
  switch (axis) {
    case X:
      rotate(angle, Vector3d(1.0f, 0.0f, 0.0f));
      break;
      
    case Y:
      rotate(angle, Vector3d(0.0f, 1.0f, 0.0f));
      break;
      
    case Z:
      rotate(angle, Vector3d(0.0f, 0.0f, 1.0f));
      break;
  }
}

void TransformationMatrix::rotate(float angle, const Vector3d& vector) {
  static Matrix4d rot;
  
  loadIdentity();
  
  float rad = deg2Rad(angle);
  
  float c = cos(rad);
  float s = sin(rad);
  
  float anti_c = 1 - c;
  
  rot.at(0,0) = vector.x() * vector.x() * (anti_c) + c;
  rot.at(0,1) = vector.x() * vector.y() * (anti_c) - (vector.z() * s);
  rot.at(0,2) = vector.x() * vector.z() * (anti_c) + (vector.y() * s);
  
  rot.at(1,0) = vector.x() * vector.y() * (anti_c) + (vector.z() * s);
  rot.at(1,1) = vector.y() * vector.y() * (anti_c) + c;
  rot.at(1,2) = vector.y() * vector.z() * (anti_c) - (vector.x() * s);
  
  rot.at(2,0) = vector.x() * vector.z() * (anti_c) - (vector.y() * s);
  rot.at(2,1) = vector.y() * vector.z() * (anti_c) + (vector.x() * s);
  rot.at(2,2) = vector.z() * vector.z() * (anti_c) + c;
  
  *this *= rot;
}

} /* namespace Dee */
