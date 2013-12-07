/*
 * pointitem.cpp
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

#include <GL/gl.h>

#include "pointitem.h"

namespace Dee {

PointItem::PointItem(bool visible) :
    Item({
      Mesh({{0.0f, 0.0f, 0.0f}})
    }, visible),
    __size(1.0f) {}

void PointItem::setSize(float size) {
  __size = size;
}

void PointItem::render() {
  
  glPushMatrix();
  glEnable(GL_POINT_SMOOTH);
  
  glMultMatrixf(transform());
  glColor3f(1.0f, 1.0f, 1.0f);
  
  glPointSize(__size);
  
  glVertexPointer(4, GL_FLOAT, 0, &(meshes()[0].vertices()[0]));
  glDrawArrays(GL_POINTS, 0, meshes()[0].vertices().size());
  
  glDisable( GL_POINT_SMOOTH );
  glPopMatrix();
}


} /* namespace Dee */
