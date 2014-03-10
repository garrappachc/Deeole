/*
 * sphereitem.cpp
 * Copyright (C) 2014  Michał Garapich <michal@garapich.pl>
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

#include "core/mesh.h"
#include "core/vertex.h"

#include "sphereitem.h"

namespace Dee {

SphereItem::SphereItem(int space, bool visible) : Item({{}}, visible) {
  __createSphere(space);
}

void SphereItem::render() {
  Mesh& mesh = meshes()[0];
  
  glPushMatrix();
  glMultMatrixf(transform());
  
  glVertexPointer(4, GL_FLOAT, sizeof(Vertex), mesh.vertices()[0].coords());
  glColorPointer(4, GL_FLOAT, sizeof(Vertex), mesh.vertices()[0].colors());
  glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh.vertices().size());
  
  glPopMatrix();
}

void SphereItem::__createSphere(int space) {
  const int R = 70;
  
  Mesh& mesh = meshes()[0];
  std::vector<Vertex>& vertices = mesh.vertices();
  
  for (double theta = 0.0; theta <= 90.0 - space; theta += static_cast<double>(space)) {
    for (double phi = 0.0; phi <= 360.0 - space; phi += static_cast<double>(space)) {
      Vertex v;
      v.coords()[0] = R * sin(deg2Rad(phi)) * sin(deg2Rad(theta));
      v.coords()[1] = R * cos(deg2Rad(phi)) * sin(deg2Rad(theta));
      v.coords()[2] = R * cos(deg2Rad(theta));
      vertices.push_back(v);
      
      v.coords()[0] = R * sin(deg2Rad(phi)) * sin(deg2Rad(theta + space));
      v.coords()[1] = R * cos(deg2Rad(phi)) * sin(deg2Rad(theta + space));
      v.coords()[2] = R * cos(deg2Rad(theta + space));
      vertices.push_back(v);
      
      v.coords()[0] = R * sin(deg2Rad(phi + space)) * sin(deg2Rad(theta));
      v.coords()[1] = R * cos(deg2Rad(phi + space)) * sin(deg2Rad(theta));
      v.coords()[2] = R * cos(deg2Rad(theta));
      vertices.push_back(v);
      
      v.coords()[0] = R * sin(deg2Rad(phi + space)) * sin(deg2Rad(theta + space));
      v.coords()[1] = R * cos(deg2Rad(phi + space)) * sin(deg2Rad(theta + space));
      v.coords()[2] = R * cos(deg2Rad(theta + space));
      vertices.push_back(v);
    }
  }
}

} /* namespace Dee */
