/*
 * window.cpp
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

#include "window.h"

namespace Dee {
  
Window::Window(std::string name) :
    __name(std::forward<std::string>(name)),
    __width(800),
    __height(600),
    __visible(false),
    __fullscreen(false) {}

Window::~Window() {
  if (visible())
    hide();
}

DeeSlot Window::show() {
  updateVisibility(true);
  __visible = true;
}

DeeSlot Window::hide() {
  updateVisibility(false);
  __visible = false;
}

void Window::setName(std::string name) {
  updateName(name);
  __name = name;
}

void Window::setWidth(int width) {
  updateSize(width, this->height());
  __width = width;
}

void Window::setHeight(int height) {
  updateSize(this->width(), height);
  __height = height;
}

void Window::setSize(int width, int height) {
  updateSize(width, height);
  __width = width;
  __height = height;
}

void Window::setFullscreen(bool fullscreen) {
  
}



} /* namespace Dee */
