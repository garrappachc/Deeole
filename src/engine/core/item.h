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

#include "core/color.h"
#include "core/renderable.h"
#include "core/transformationmatrix.h"
#include "core/vertex.h"

namespace Dee {

class __DeeExport__ Item : public Renderable {
  
public:
  Item(bool visible = true);
  Item(std::initializer_list<Vertex>&& vertices, bool visible = true);
  
  void setColor(Color color);
  
  inline void translate(const Vector3d& vector) {
    __transform.translate(vector);
  }
  
  inline void rotate(float angle, Axis axis) {
    __transform.rotate(angle, axis);
  }
  
  inline void scale(const Vector3d& vector) {
    __transform.scale(vector);
  }
  
  inline void reset() {
    __transform.loadIdentity();
  }
  
  inline const std::vector<Vertex>& vertices() const {
    return __vertices;
  }
  
  inline std::vector<Vertex>& vertices() {
      return __vertices;
    }
  
  inline const TransformationMatrix& transform() const {
    return __transform;
  }
  
  inline const Color& color() const {
    return __color;
  }
  
protected:
  void render() override;
  
private:
  std::vector<Vertex> __vertices;
  TransformationMatrix __transform;
  Color __color;
  
};

} /* namespace Dee */

#endif // ITEM_H
