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
  
void FreeCamera::setProjection() const {
  glMatrixMode(GL_PROJECTION);
  
  GLdouble aspect = static_cast<GLdouble>(deeApp->window()->width()) /
                    static_cast<GLdouble>(deeApp->window()->height());
  gluPerspective(fovy(), aspect, zNear(), zFar());
}

} /* namespace Dee */
