/*
 * modelviewmatrix.h
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

#ifndef MODELVIEWMATRIX_H
#define MODELVIEWMATRIX_H

#include "core/deeglobal.h"

#include "core/matrix.h"
#include "core/point.h"
#include "core/vector.h"

namespace Dee {

class __DeeExport__ ModelViewMatrix : public Matrix4d {
  
public:
  void lookAt(const Point3d& eye, const Point3d& center,
              const Vector3d& up = Vector3d(0.0f, 1.0f, 0.0f));
  
  void translate(const Vector3d& vector);
};

} /* namespace Dee */

#endif // MODELVIEWMATRIX_H
