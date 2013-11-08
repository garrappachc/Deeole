/*
 * x11bridge.cpp
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

#include "core/application.h"
#include "core/glbridge.h"
#include "core/inputhandler.h"
#include "core/keyboard.h"
#include "core/x11/x11window.h"
#include "utils/logger.h"

#include "x11bridge.h"

namespace Dee {

Display*              X11Bridge::__display = nullptr;
X11Bridge::GlXVersion X11Bridge::__glxVersion = { 0, 0 };

void X11Bridge::openDisplay() {
  __display = XOpenDisplay(nullptr);
  if (!__display) {
    Logger::fatal("X11: could not open connection to the X server.");
  }
  
  Logger::debug("X11: connection established.");
  
  XSetErrorHandler(X11Bridge::__x11ErrorHandler);
  XInitThreads();
  glXQueryVersion(X11::display(), &__glxVersion.major, &__glxVersion.minor);
  
  Logger::info("GLX: reported version %i.%i", __glxVersion.major, __glxVersion.minor);
}

void X11Bridge::closeDisplay() {
  XCloseDisplay(__display);
  __display = 0;
  
  Logger::debug("X11: connection closed.");
}

void X11Bridge::processEvents() {
  static XEvent event;
  static X11Window* window = dynamic_cast<X11Window*>(Application::window());
  
  while (XPending(X11::display())) {
    XNextEvent(X11::display(), &event);
    
    switch (event.type) {
      case MapNotify:
        window->showEvent();
        break;
        
      case ClientMessage:
        if (static_cast<Atom>(event.xclient.data.l[0]) == X11::__wmCloseMessage())
          window->closeEvent();
        break;
        
      case KeyPress:
        deeApp->input()->keyPressEvent(event.xkey.keycode);
        break;
        
      case KeyRelease:
        deeApp->input()->keyReleaseEvent(event.xkey.keycode);
        break;
        
      case MotionNotify:
        deeApp->input()->mouseMotionEvent(event.xmotion.x, event.xmotion.y);
        break;
      
      case ConfigureNotify:
        int w = event.xconfigure.width;
        int h = event.xconfigure.height;
        
        if (w != window->width() || h != window->height())
          window->resizeEvent(w, h);
        break;
    }
  }
}

GLXFBConfig X11Bridge::getBestFbConfig() {
  static int fbAttribs[] = {
    GLX_RENDER_TYPE,    GLX_RGBA_BIT,
    GLX_X_RENDERABLE,   True,
    GLX_DRAWABLE_TYPE,  GLX_WINDOW_BIT,
    GLX_DOUBLEBUFFER,   True,
    GLX_X_VISUAL_TYPE,  GLX_TRUE_COLOR,
    GLX_RED_SIZE,       8,
    GLX_BLUE_SIZE,      8,
    GLX_GREEN_SIZE,     8,
    GLX_DEPTH_SIZE,     24,
    GLX_STENCIL_SIZE,   8,
    GLX_ALPHA_SIZE,     8,
    
    /* Closing */
    0
  };
  
  /* Get configuration list */
  int numConfigs;
  GLXFBConfig* fbConfigs = glXChooseFBConfig(X11::display(), DefaultScreen(X11::display()),
                                             fbAttribs, &numConfigs);
  DeeAssert(fbConfigs);
  
  Logger::debug("GLX: found %i configs.", numConfigs);
  
  /* Choose the best configuration */
  int bestFbc = -1, worstFbc = -1, bestNumSamp = -1, worstNumSamp = 999;
  
  for (int i = 0; i < numConfigs; ++i) {
    XVisualInfo* vi = glXGetVisualFromFBConfig(X11::display(), fbConfigs[i]);
    if (vi) {
      int sampBuf, samples;
      glXGetFBConfigAttrib(X11::display(), fbConfigs[i], GLX_SAMPLE_BUFFERS, &sampBuf);
      glXGetFBConfigAttrib(X11::display(), fbConfigs[i], GLX_SAMPLES, &samples);
      
      if ((bestFbc < 0 || sampBuf) && samples > bestNumSamp)
        bestFbc = i, bestNumSamp = samples;
      if (worstFbc < 0 || !sampBuf || samples < worstNumSamp)
        worstFbc = i, worstNumSamp = samples;
    }
    
    XFree(vi);
  }
  
  GLXFBConfig bestFbConfig = fbConfigs[bestFbc];
  XFree(fbConfigs);
  
  return bestFbConfig;
}

void X11Bridge::registerWindow(::Window handle) {
  XSetWMProtocols(X11::display(), handle, &X11::__wmCloseMessage(), 1);
}

GLXContext X11Bridge::glXCreateContextAttribsARB(Display* display, GLXFBConfig fbConfig,
                                                 GLXContext shareContext, int direct,
                                                 const int* attribs) {
  static auto proc =
    GlBridge::getProcAddr<decltype(&X11Bridge::glXCreateContextAttribsARB)>("glXCreateContextAttribsARB");
  
  if (proc) {
    return proc(display, fbConfig, shareContext, direct, attribs);
  } else {
    Logger::info("glXCreateContextAttribsARB() unavailable, using glXCreateNewContext() in use.");
    return glXCreateNewContext(display, fbConfig, GLX_RGBA_TYPE, 0, True);
  }
}

Atom& X11Bridge::__wmCloseMessage() {
  static Atom atom = XInternAtom(X11::display(), "WM_DELETE_WINDOW", False);
  return atom;
}

int X11Bridge::__x11ErrorHandler(Display* display, XErrorEvent* error) {
  static char buffer[256];
  
  memset(buffer, '\0', sizeof(buffer));
  XGetErrorText(display, error->error_code, buffer, sizeof(buffer));
  
  Logger::warning("X11 error: %s", buffer);
  return 0;
}

} /* namespace Dee */
