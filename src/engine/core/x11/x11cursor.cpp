/*
 * x11cursor.cpp
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

#include <X11/X.h>

#include "core/application.h"
#include "core/window.h"
#include "core/x11/x11bridge.h"
#include "core/x11/x11window.h"

#include "x11cursor.h"

namespace Dee {

void X11Cursor::setPosition(int x, int y) {
  X11Window* window = dynamic_cast<X11Window*>(deeApp->window());
  DeeAssert(window);
  XWarpPointer(X11::display(), None, window->handle(), 0, 0, 0, 0, x, y);
  XFlush(X11::display());
}

} /* namespace Dee */
