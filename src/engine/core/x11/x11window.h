/*
 * x11window.h
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

#ifndef X11WINDOW_H
#define X11WINDOW_H

#include <GL/glx.h>

#include "core/deeglobal.h"

#include "core/window.h"

namespace Dee {
  
  class X11Bridge;

/**
 * \ingroup Core
 * @{
 * 
 * The X11Window class provides a single window representation on Linux
 * systems with X11.
 * 
 * Generally, you will not need to use this class, at least not directly.
 * 
 * \sa Window.
 */
class __DeeExport__ X11Window : public Window {
  
  friend class X11Bridge; // events
  
public:
  typedef ::Window     HandleType;
  typedef ::GLXContext ContextType;
  
  X11Window(std::string name = "");
  virtual ~X11Window();
  
  void swapBuffers() override;
  
  inline HandleType handle() const {
    return __handle;
  }
  
protected:
  void updateVisibility(bool visible) override;
  void updateName(const std::string& name) override;
  void updateSize(int width, int height) override;
  bool updateFullscreen(bool fullscreen) override;
  
private:
  void __setupWindow();
  void __destroyWindow();
  
  HandleType __handle;
  ContextType __context;
  

}; /** @} */

} /* namespace Dee */

#endif // X11WINDOW_H
