/*
 * x11cursor.h
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

#ifndef X11CURSOR_H
#define X11CURSOR_H

#include "core/deeglobal.h"

#include "core/cursor.h"

namespace Dee {

class X11Cursor : public Cursor {
public:
  void setPosition(int x, int y) override;
  void setVisible(bool visible) override;
};

} /* namespace Dee */

#endif // X11CURSOR_H
