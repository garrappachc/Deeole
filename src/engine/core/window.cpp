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
#include "events/fullscreenevent.h"
#include "events/namechangeevent.h"
#include "events/resizeevent.h"
#include "events/visibilitychangeevent.h"
#include "utils/logger.h"

#include "window.h"

namespace Dee {
  
Window::Window(std::string name) :
    __name(std::forward<std::string>(name)),
    __size(800, 600),
    __visible(false),
    __fullscreen(false) {
  deeApp->aboutToQuit.connect(this, &Window::close);
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
  
  if (__fullscreen)
    setFullscreen(true);
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

void Window::setSize(int width, int height) {
  ResizeEvent event(this->size(), Size(width, height));
  resizeEvent(&event);
  __size = event.newSize();
  
  emit resized(__size);
}

void Window::setSize(const Size& size) {
  ResizeEvent event(this->size(), size);
  resizeEvent(&event);
  __size = event.newSize();
  
  emit resized(__size);
}

void Window::setFullscreen(bool fullscreen) {
  if (visible()) {
    FullscreenEvent event(fullscreen);
    fullscreenEvent(&event);
  }
  
  __fullscreen = fullscreen;
}

void Window::visibilityChangeEvent(VisibilityChangeEvent* event) {
  __visible = event->visible();
  if (visible())
    emit shown();
  else
    emit closed();
}

void Window::nameChangeEvent(NameChangeEvent* event) {}

void Window::resizeEvent(ResizeEvent* event) {
  __size = event->newSize();
  emit resized(__size);
}

void Window::fullscreenEvent(FullscreenEvent* event) {}

} /* namespace Dee */
