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

#include "core/application.h"
#include "events/namechangeevent.h"
#include "events/visibilitychangeevent.h"
#include "utils/logger.h"

#include "window.h"

namespace Dee {
  
Window::Window(std::string name) :
    __name(std::forward<std::string>(name)),
    __width(800),
    __height(600),
    __visible(false),
    __fullscreen(false) {
  Application::singleton().aboutToQuit.connect(this, &Window::close);
}

Window::~Window() {
  if (visible())
    close();
}

DeeSlot Window::show() {
  VisibilityChangeEvent event(true);
  visibilityChangeEvent(&event);
  __visible = event.visible();
  
  emit shown();
  
  if (__fullscreen) {
    __fullscreen = false;
    setFullscreen(true);
  }
}

DeeSlot Window::close() {
  VisibilityChangeEvent event(false);
  visibilityChangeEvent(&event);
  __visible = event.visible();
  
  emit closed();
}

void Window::setName(std::string name) {
  NameChangeEvent event(__name, name);
  nameChangeEvent(&event);
  __name = event.newName();
}

void Window::setWidth(int width) {
  updateSize(width, this->height());
  __width = width;
  
  emit resized(__width, __height);
}

void Window::setHeight(int height) {
  updateSize(this->width(), height);
  __height = height;
  
  emit resized(__width, __height);
}

void Window::setSize(int width, int height) {
  updateSize(width, height);
  __width = width;
  __height = height;
  
  emit resized(__width, __height);
}

void Window::setFullscreen(bool fullscreen) {
  if (visible()) {
    if (updateFullscreen(fullscreen))
      __fullscreen = fullscreen;
  } else {
    __fullscreen = fullscreen;
  }
}

void Window::resizeEvent(int width, int height) {
  __width = width;
  __height = height;
  
  emit resized(width, height);
}

void Window::showEvent() {
  __visible = true;
  emit shown();
}

void Window::closeEvent() {
  __visible = false;
  emit closed();
}

} /* namespace Dee */
