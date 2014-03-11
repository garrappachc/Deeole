/*
 * cubeitem.h
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

#ifndef CUBEITEM_H
#define CUBEITEM_H

#include "core/deeglobal.h"

#include "core/item.h"

namespace Dee {

class __DeeExport__ CubeItem : public Item {
  
public:
  
  CubeItem(bool visible = true);
  
  inline const Mesh& front() const {
    return meshes()[0];
  }
  
  inline Mesh& front() {
    return meshes()[0];
  }
  
  inline const Mesh& left() const {
    return meshes()[1];
  }
  
  inline Mesh& left() {
    return meshes()[1];
  }
  
  inline const Mesh& right() const {
    return meshes()[2];
  }
  
  inline Mesh& right() {
    return meshes()[2];
  }
  
  inline const Mesh& top() const {
    return meshes()[3];
  }
  
  inline Mesh& top() {
    return meshes()[3];
  }
  
  inline const Mesh& bottom() const {
    return meshes()[4];
  }
  
  inline Mesh& bottom() {
    return meshes()[4];
  }
  
  inline const Mesh& back() const {
    return meshes()[5];
  }
  
  inline Mesh& back() {
    return meshes()[5];
  }
  
};

} /* namespace Dee */

#endif // CUBEITEM_H
