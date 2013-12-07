/*
 * item.h
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

#ifndef ITEM_H
#define ITEM_H

#include <initializer_list>
#include <vector>

#include "core/deeglobal.h"

#include "core/mesh.h"
#include "core/renderable.h"
#include "core/transformationmatrix.h"

namespace Dee {

class __DeeExport__ Item : public Renderable {
  
public:
  Item(bool visible = true);
  Item(std::initializer_list<Mesh>&& meshes, bool visible = true);
  
  void translate(const Vector3d& vector);
  
  void rotate(float angle, Axis axis);
  
  void scale(const Vector3d& vector);
  
  void reset();
  
  void setColor(Color color);
  
  inline const std::vector<Mesh>& meshes() const {
    return __meshes;
  }
  
  inline std::vector<Mesh>& meshes() {
    return __meshes;
  }
  
  inline const TransformationMatrix& transform() const {
    return __transform;
  }
  
  inline TransformationMatrix& transform() {
    return __transform;
  }
  
protected:
  void render() override;
  
private:
  std::vector<Mesh> __meshes;
  TransformationMatrix __transform;
  
};

} /* namespace Dee */

#endif // ITEM_H
