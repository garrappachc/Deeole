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

#include <cstring>
#include <GL/glx.h>

#include "core/x11/x11bridge.h"
#include "utils/logger.h"

#include "x11window.h"

namespace Dee {

X11Window::X11Window(std::string name) :
    Window(name) {
  __setupWindow();
}

X11Window::~X11Window() {
  __destroyWindow();
}

void X11Window::swapBuffers() {
  glXSwapBuffers(X11::display(), __handle);
}

void X11Window::updateVisibility(bool visible) {
  if (visible)
    XMapWindow(X11::display(), __handle);
  else
    XUnmapWindow(X11::display(), __handle);
}

void X11Window::updateName(const std::string& name) {
  XStoreName(X11::display(), __handle, name.c_str());
}

void X11Window::updateSize(int width, int height) {
  XWindowChanges changes;
  changes.width = width;
  changes.height = height;
  
  XConfigureWindow(X11::display(), __handle, CWWidth | CWHeight, &changes);
}

bool X11Window::updateFullscreen(bool fullscreen) {
  Atom atom = XInternAtom(X11::display(), "_NET_WM_STATE_FULLSCREEN", False);
  
  XEvent xev;
  memset(&xev, 0, sizeof(xev));
  xev.type = ClientMessage;
  xev.xclient.window = __handle;
  xev.xclient.message_type = XInternAtom(X11::display(), "_NET_WM_STATE", False);
  xev.xclient.format = 32;
  xev.xclient.data.l[0] = fullscreen ? 1 : 0;
  xev.xclient.data.l[1] = atom;
  
  XSendEvent(X11::display(), DefaultRootWindow(X11::display()), False,
             SubstructureRedirectMask | SubstructureNotifyMask, &xev);
  
  return true;
}

void X11Window::__setupWindow() {
  static int winmask = CWBorderPixel | CWBitGravity | CWEventMask | CWColormap;
  static GLXFBConfig fbConfig = X11::getBestFbConfig();
  
  /* Context attributes for OpenGL >= 3.0 */
  static int contextAttribs30[] = {
    GLX_CONTEXT_FLAGS_ARB,      GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
    None
  };
  
  /* If the above does not work, try legacy OpenGL */
  static int contextAttribsLegacy[] = {
    GLX_CONTEXT_MAJOR_VERSION_ARB,      2,
    GLX_CONTEXT_MINOR_VERSION_ARB,      1,
    None
  };
  
  XVisualInfo* visualInfo = glXGetVisualFromFBConfig(X11::display(), fbConfig);
  
  XSetWindowAttributes winAttrs;
  winAttrs.event_mask = ExposureMask
                      | VisibilityChangeMask
                      | KeyPressMask
                      | KeyReleaseMask
                      | StructureNotifyMask
                      | PointerMotionMask
                      ;
  
  winAttrs.border_pixel = 0,
  winAttrs.background_pixmap = None,
  winAttrs.bit_gravity = StaticGravity,
  winAttrs.colormap = XCreateColormap(
      X11::display(),
      RootWindow(X11::display(), visualInfo->screen),
      visualInfo->visual,
      AllocNone);
  
  /* Create window */
  __handle = XCreateWindow(X11::display(),
    RootWindow(X11::display(), visualInfo->screen),
    x(), y(),
    width(), height(),
    0, visualInfo->depth, InputOutput,
    visualInfo->visual, winmask,
    &winAttrs);
  
  if (!__handle)
    Logger::fatal("X11Window: could not create the window");
  
  X11::registerWindow(__handle);
  Logger::debug("X11Window: window %u created", __handle);
  
  XFree(visualInfo);
  
  __context = X11::glXCreateContextAttribsARB(X11::display(), fbConfig, 0, True, contextAttribs30);
  if (!__context)
    __context = X11::glXCreateContextAttribsARB(X11::display(), fbConfig, 0, True, contextAttribsLegacy);
  
  if (!__context)
    Logger::fatal("X11Window: OpenGL >= 2.1 is not supported on your system. Unable to continue.");
  
  XSync(X11::display(), false);
  glXMakeCurrent(X11::display(), __handle, __context);
  
  if (glXIsDirect(X11::display(), __context))
    Logger::info("X11Window: direct rendering");
  else
    Logger::info("X11Window: indirect rendering");
}

void X11Window::__destroyWindow() {
  glXDestroyContext(X11::display(), __context);
  XDestroyWindow(X11::display(), __handle);
}

} /* namespace Dee */
