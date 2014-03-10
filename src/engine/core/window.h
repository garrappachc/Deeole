/*
 * window.h
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

#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include "core/deeglobal.h"

#include "core/object.h"
#include "core/signal.h"
#include "core/size.h"

namespace Dee {

class FullscreenEvent;
class NameChangeEvent;
class ResizeEvent;
class VisibilityChangeEvent;
  
/**
 * \ingroup Core
 * @{
 * 
 * The Window class provides a basic UI window.
 * 
 * This abstract class is implemented by OS-specific classes. You do not have
 * to worry about that.
 * 
 * To access the main application window, call `Application::window()`.
 */
class __DeeExport__ Window :
    public Object {
  
public:
  
  /**
   * The constructor.
   * 
   * The constructor does not show the window yet.
   * 
   * \param name Name of the window.
   * \sa Application::window().
   */
  Window(std::string name = "");
  
  /**
   * The destructor.
   * 
   * The destructor closes the window (if still visible) and frees
   * resources.
   */
  virtual ~Window();
  
   /**
   * Shows the window and makes it active rendering context for OpenGL.
   * 
   * \sa hide().
   */
  DeeSlot show();
  
  /**
   * Closes the window.
   * 
   * \sa show().
   */
  DeeSlot close();
  
  /**
   * Sets the window name.
   * 
   * \param name The new name.
   * \sa name().
   */
  void setName(std::string name);
  
  /**
   * Resizes the window.
   * 
   * \param width The new width.
   * \param height The new height.
   * \sa size().
   */
  void setSize(int width, int height);
  
  /**
   * Resizes the window.
   * 
   * \param size The new size.
   * \sa size().
   */
  void setSize(const Size& size);
  
  /**
   * Makes the window fullscreen (or not).
   * 
   * This function may behave differently, depending on the platform and
   * desktop environment. To check if window switched to fullscreen mode
   * successfully, use fullscreen() method.
   */
  void setFullscreen(bool fullscreen);
  
  /**
   * Swaps the OpenGL buffers.
   * 
   * This function is called automatically during the render loop.
   * 
   * \sa Application::run().
   */
  virtual void swapBuffers() = 0;
  
  /**
   * Gets the window name.
   * 
   * \return The window name.
   */
  inline const std::string& name() const {
    return __name;
  }
  
  inline int x() const {
    return __x;
  }
  
  inline int y() const {
    return __y;
  }
  
  inline const Size& size() const {
    return __size;
  }
  
  /**
   * Gets the window visibility.
   * 
   * \return True if the window is visible on the screen, otherwise false.
   * \sa show() and hide().
   */
  inline bool visible() const {
    return __visible;
  }
  
  /**
   * Obtains the window fullscreen mode.
   * 
   * \return True if window is fullscreen, otherwise false.
   * \sa setFullscreen().
   */
  inline bool fullscreen() const {
    return __fullscreen;
  }
  
  // signals
  Signal<>      shown;   /**< Emitted just after the window becomes visible. */
  Signal<>      closed;  /**< Emitted just after the window is closed. */
  Signal<Size>  resized; /**< Emitted just after the window gets resized. */
    
  /**
   * \cond HIDDEN_DOC
   */
  Window(const Window&) = delete;
  /**
   * \endcond
   */
  
protected:
  
  /**
   * \cond INTERNAL
   */
  
  /**
   * Called when show() or hide() are called.
   */
  virtual void visibilityChangeEvent(VisibilityChangeEvent* event);
  
  /**
   * Called when setName() is called.
   */
  virtual void nameChangeEvent(NameChangeEvent* event);
  
  /**
   * Called when setSize() is called.
   */
  virtual void resizeEvent(ResizeEvent* event);
  
  /**
   * Called when setFullscreen() is called.
   */
  virtual void fullscreenEvent(FullscreenEvent* event);
  
  /**
   * \endcond
   */
  
private:
  std::string __name;
  int         __x;
  int         __y;
  Size        __size;
  bool        __visible;
  bool        __fullscreen;
  

}; /** @} */

} /* namespace Dee */

#endif // WINDOW_H
