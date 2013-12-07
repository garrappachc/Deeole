/*
 * mesh.h
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

#ifndef MESH_H
#define MESH_H

#include <vector>
#include <initializer_list>

#include "core/deeglobal.h"

#include "core/color.h"
#include "core/vertex.h"

namespace Dee {

class __DeeExport__ Mesh {
  
public:
  Mesh(std::initializer_list<Vertex>&& vertices);
  
  void setColor(Color color);
  
  inline const std::vector<Vertex>& vertices() const {
    return __vertices;
  }
  
  inline std::vector<Vertex>& vertices() {
    return __vertices;
  }
  
  inline const Color& color() const {
    return __color;
  }
  
  inline Color& color() {
    return __color;
  }
  
private:
  std::vector<Vertex> __vertices;
  Color __color;
  
  
  
};

} /* namespace Dee */

#endif // MESH_H
