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

void TransformationMatrix::rotate(float angle, Axis axis) {
  float radangle = deg2Rad(angle); // convert to radians
  
  float c = cos(radangle);
  float s = sin(radangle);
  
  float anti_c = 1 - c;
  
  Vector3d rot;
  switch (axis) {
    case X:
      rot = Vector3d(1.0f, 0.0f, 0.0f);
      break;
    case Y:
      rot = Vector3d(0.0f, 1.0f, 0.0f);
      break;
    case Z:
      rot = Vector3d(0.0f, 0.0f, 1.0f);
      break;
  }
  
  at(0,0) = rot.x() * rot.x() * (anti_c) + c;
  at(1,0) = rot.x() * rot.y() * (anti_c) + (rot.z() * s);
  at(2,0) = rot.x() * rot.z() * (anti_c) - (rot.y() * s);
  
  at(0,1) = rot.x() * rot.y() * (anti_c) - (rot.z() * s);
  at(1,1) = rot.y() * rot.y() * (anti_c) + c;
  at(2,1) = rot.y() * rot.z() * (anti_c) + (rot.x() * s);
  
  at(0,2) = rot.x() * rot.z() * (anti_c) + (rot.y() * s);
  at(1,2) = rot.y() * rot.z() * (anti_c) - (rot.x() * s);
  at(2,2) = rot.z() * rot.z() * (anti_c) + c;
}

} /* namespace Dee */
