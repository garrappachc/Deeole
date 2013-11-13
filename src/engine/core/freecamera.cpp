/*
 * freecamera.cpp
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

#include <GL/glu.h>

#include "core/application.h"
#include "core/window.h"

#include "freecamera.h"

namespace Dee {
  
FreeCamera::FreeCamera() :
    Camera(),
    __angle({0.0f, 0.0f, 0.0f}),
    __fovy(45.0f) {}

void FreeCamera::move(const Vector3d& vector) {
  eye() += Vector3d(
    (lookAt().x() * vector.z()) - (lookAt().z() * vector.x()),
    vector.y(),
    (lookAt().z() * vector.z()) + (lookAt().x() * vector.x())
  );
}

void FreeCamera::rotate(const Vector3d& vector) {
  __angle -= (vector / 100);
  __angle[1] = Dee::bound(deg2Rad(-90), __angle.y(), deg2Rad(90));
  
  setLookAt({
    cos(__angle.x() - 90),
    sin(__angle.y()),
    sin(__angle.x() - 90)
  });
  
  lookAt().normalize();
}

void FreeCamera::setProjection() {
//   glMatrixMode(GL_PROJECTION);
//   
//   GLdouble aspect = static_cast<GLdouble>(deeApp->window()->width()) /
//                     static_cast<GLdouble>(deeApp->window()->height());
//   gluPerspective(__fovy, aspect, zNear(), zFar());
  
  float aspect = static_cast<float>(deeApp->window()->width()) /
                 static_cast<float>(deeApp->window()->height());
                 
  projectionMatrix().perspective(__fovy, aspect, zNear(), zFar());
  
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(projectionMatrix());
}

void FreeCamera::setView() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  gluLookAt(eye().x(), eye().y(), eye().z(),
            eye().x() + lookAt().x(), eye().y() + lookAt().y(), eye().z() + lookAt().z(),
            up().x(), up().y(), up().z());
}

} /* namespace Dee */
