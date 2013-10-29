/*
 * x11window.cpp
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

#include "GL/glx.h"

#include "x11window.h"

namespace Dee {

X11Window::X11Window(std::string name) :
    Window(name) {
  __setupWindow();
}

X11Window::~X11Window() {

}

void X11Window::swapBuffers() {
  
}

void X11Window::updateVisibility(bool visible) {
  
}

void X11Window::updateName(const std::string& name) {

}

void X11Window::updateSize(int width, int height) {

}

bool X11Window::updateFullscreen(bool fullscreen) {

}

void X11Window::resizeEvent(int width, int height) {

}

void X11Window::showEvent() {

}

void X11Window::closeEvent() {

}

void X11Window::__setupWindow() {

}

} /* namespace Dee */
