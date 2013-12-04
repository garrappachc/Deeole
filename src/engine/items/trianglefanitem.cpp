/*
 * trianglefanitem.cpp
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

#include "trianglefanitem.h"

namespace Dee {

TriangleFanItem::TriangleFanItem(int triangles, bool visible) :
    Item({
      
      /* Front side */
      {  0.0f,  0.0f, -0.5f },
      { -0.5f,  1.0f, -0.5f },
      {  0.5f,  1.0f, -0.5f }
      
    }, visible) {
  
  float x = 1.0f;
  
  for (int i = 1; i < triangles; ++i) {
    vertices().push_back({x, 1.0f, -0.5f});
    x += 0.5f;
  }
}

void TriangleFanItem::render() {
  
  glPushMatrix();
  
  glMultMatrixf(transform());
  glColor3f(1.0f, 1.0f, 1.0f);
  
  glVertexPointer(4, GL_FLOAT, 0, &vertices()[0]);
  glDrawArrays(GL_TRIANGLE_FAN, 0, vertices().size());
  
  glPopMatrix();
}


} /* namespace Dee */
