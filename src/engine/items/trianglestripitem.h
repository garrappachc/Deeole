/*
 * trianglestripitem.h
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

#ifndef TRIANGLESTRIPITEM_H
#define TRIANGLESTRIPITEM_H

#include "core/deeglobal.h"

#include "core/item.h"

namespace Dee {

class TriangleStripItem : public Item {
  
public:
  
  TriangleStripItem(int triangles = 1, bool visible = true);
  
protected:
  void render() override;
  
  
};

} /* namespace Dee */

#endif // TRIANGLESTRIPITEM_H
