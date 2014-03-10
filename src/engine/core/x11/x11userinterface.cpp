/*
 * x11userinterface.cpp
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

#include "x11userinterface.h"

#include "core/application.h"

#include "core/x11/x11bridge.h"
#include "core/x11/x11cursor.h"
#include "core/x11/x11window.h"

#include "utils/logger.h"

namespace Dee {
  
X11UserInterface::X11UserInterface() {
  X11Bridge::openDisplay();
  
  deeApp->afterRender.connect(this, &X11UserInterface::afterFirstFrame);
}

X11UserInterface::~X11UserInterface() {
  X11Bridge::closeDisplay();
}
  
Window* X11UserInterface::getWindow() {
  return new X11Window();
}

Cursor* X11UserInterface::getCursor() {
  return new X11Cursor();
}

void X11UserInterface::processEvents() {
  X11::processEvents();
}

DeeSlot X11UserInterface::afterFirstFrame() {
  X11::captureMouseMotion(true);
  deeApp->afterRender.disconnect(this, &X11UserInterface::afterFirstFrame);
}


} /* namespace Dee */
