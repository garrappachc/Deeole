/*
 * x11bridge.h
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

#ifndef X11BRIDGE_H
#define X11BRIDGE_H

#include "core/deeglobal.h"

#include <GL/glx.h>

namespace Dee {

/**
 * \cond HIDDEN_DOC
 */
class __DeeHide__ X11Bridge {
  
public:
  
  static void openDisplay();
  static void closeDisplay();
  static void processEvents();
  
  static GLXFBConfig getBestFbConfig();
  static void registerWindow(::Window handle);
  static GLXContext glXCreateContextAttribsARB(Display* display, GLXFBConfig fbConfig,
                                               GLXContext shareContext, Bool direct,
                                               const int* attribs);
  
  inline static Key::Code mapKey(unsigned code) {
    return static_cast<Key::Code>(code);
  }
  
  struct GlXVersion { int major, minor; };
  
  inline static Display* display() {
    DeeAssert(__display);
    return __display;
  }
  
  inline static const GlXVersion& glxVersion() {
    return __glxVersion;
  }
  
  X11Bridge() = delete;
  
private:
  
  static Atom& __wmCloseMessage();
  
  static int __x11ErrorHandler(Display* display, XErrorEvent* error);
  
  static Display*   __display;
  static GlXVersion __glxVersion;

};

using X11 = X11Bridge;
/**
 * \endcond
 */

} /* namespace Dee */

#endif // X11BRIDGE_H
