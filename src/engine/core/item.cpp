/*
 * item.cpp
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

#include "item.h"

namespace Dee {

Item::Item(bool visible) :
    Renderable(visible) {}

Item::Item(std::initializer_list<Mesh>&& meshes, bool visible) :
    Renderable(visible),
    __meshes(std::forward<std::initializer_list<Mesh>>(meshes)) {}

void Item::translate(const Vector3d& vector) {
  __transform.translate(vector);
}

void Item::rotate(float angle, Axis axis) {
  __transform.rotate(angle, axis);
}

void Item::scale(const Vector3d& vector) {
  __transform.scale(vector);
}

void Item::reset() {
  __transform.loadIdentity();
}

void Item::setColor(Color color) {
  for (Mesh& m: __meshes)
    m.setColor(std::forward<Color>(color));
}

void Item::render() {
  
  glPushMatrix();
  
  glMultMatrixf(__transform);
  
  for (Mesh& m: __meshes) {
    glColor4f(m.color().r(), m.color().g(), m.color().b(), m.color().a());
    
    glVertexPointer(4, GL_FLOAT, 0, &m.vertices()[0]);
    glDrawArrays(GL_TRIANGLES, 0, m.vertices().size());
  }
  
  glPopMatrix();
}

} /* namespace Dee */
