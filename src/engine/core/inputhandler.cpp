/*
 * inputhandler.cpp
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

#include "core/keyboard.h"

#include "inputhandler.h"

namespace Dee {
  
InputHandler::InputHandler() :
    __keyboard(new Keyboard()) {}

InputHandler::~InputHandler() {
  delete __keyboard;
}

void InputHandler::clearState() {
  __keyboard->clearState();
}

void InputHandler::keyPressEvent(unsigned int key) {
  __keyboard->keyPressEvent(key);
}

void InputHandler::keyReleaseEvent(unsigned int key) {
  __keyboard->keyReleaseEvent(key);
}

} /* namespace Dee */
