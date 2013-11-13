/*
 * camera.cpp
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

#include <utility>
#include <GL/gl.h>
#include <GL/glu.h>

#include "camera.h"

namespace Dee {

Camera::Camera(Point3d eye, Vector3d lookAt, Vector3d up):
    __eye(std::move(eye)),
    __lookAt(std::move(lookAt)),
    __up(std::move(up)),
    __zNear(0.1f),
    __zFar(100.0f) {}

Camera::~Camera() {}

void
Camera::setEye(Point3d eye) {
  __eye = eye;
}

void
Camera::move(const Vector3d& vector) {
  __eye += vector;
  __lookAt += vector;
}

void
Camera::setLookAt(Vector3d lookAt) {
  __lookAt = lookAt;
}

void
Camera::rotate(const Vector3d& vector) {
  __lookAt += vector;
}

void
Camera::setUp(Vector3d up) {
  __up = up;
}

void
Camera::setProjection() {
//   glMatrixMode(GL_PROJECTION);
//   glOrtho(-1.0, 1.0,
//           -1.0, 1.0,
//           __zNear, __zFar);
  projectionMatrix().ortho(-1.0f, 1.0f, -1.0f, 1.0f, __zNear, __zFar);
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(projectionMatrix());
}

void
Camera::setView() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  gluLookAt(__eye.x(), __eye.y(), __eye.z(),
            __lookAt.x(), __lookAt.y(), __lookAt.z(),
            __up.x(), __up.y(), __up.z());
}

} /* namespace Dee */
