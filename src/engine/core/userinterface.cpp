/*
 * userinterface.cpp
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

#include "core/window.h"

#include "userinterface.h"

#ifdef LINUX
# include "core/x11/x11bridge.h"
# include "core/x11/x11window.h"
#endif

namespace Dee {
  
Dee::Window* UserInterface::getPlatformWindow() {
#ifdef LINUX
  return new X11Window();
#endif
}

void UserInterface::init() {
#ifdef LINUX
  X11Bridge::openDisplay();
#endif
}

void UserInterface::processEvents() {
#ifdef LINUX
  X11::processEvents();
#endif
}

void UserInterface::close() {
#ifdef LINUX
  X11::closeDisplay();
#endif
}

} /* namespace Dee */
