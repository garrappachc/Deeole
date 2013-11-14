/*
 * modelviewmatrix.cpp
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

#include "modelviewmatrix.h"

namespace Dee {
  
void ModelViewMatrix::lookAt(const Point3d& eye, const Point3d& center, const Vector3d& up) {
  Vector3d f = center - eye;
  f.normalize();
  
  Vector3d side = f.cross(up);
  side.normalize();
  
  Vector3d u = side.cross(f);
  
  loadIdentity();
  
  at(0, 0) = side.x();
  at(0, 1) = side.y();
  at(0, 2) = side.z();
  
  at(1, 0) = u.x();
  at(1, 1) = u.y();
  at(1, 2) = u.z();
  
  at(2, 0) = -f.x();
  at(2, 1) = -f.y();
  at(2, 2) = -f.z();
  
  translate(-eye);
}

void ModelViewMatrix::translate(const Vector3d& vector) {
  at(0,3) += (at(0,0) * vector.x() + at(0,1) * vector.y() + at(0,2) * vector.z());
  at(1,3) += (at(1,0) * vector.x() + at(1,1) * vector.y() + at(1,2) * vector.z());
  at(2,3) += (at(2,0) * vector.x() + at(2,1) * vector.y() + at(2,2) * vector.z());
  at(3,3) += (at(3,0) * vector.x() + at(3,1) * vector.y() + at(3,2) * vector.z());
}

} /* namespace Dee */
