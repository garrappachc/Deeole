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

#include "core/eventful.h"
#include "core/signal.h"

namespace Dee {
  
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
    public Eventful {
  
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
   * Hides the window.
   * 
   * \sa show().
   */
  DeeSlot hide();
  
  /**
   * Sets the window name.
   * 
   * \param name The new name.
   */
  void setName(std::string name);
  
  /**
   * Sets the window width.
   * 
   * \param width The new width.
   * \sa width() and setSize().
   */
  void setWidth(int width);
  
  /**
   * Sets the window height.
   * 
   * \param height The new height.
   * \sa height() and setSize().
   */
  void setHeight(int height);
  
  /**
   * Sets the window dimensions.
   * 
   * \param width The new width.
   * \param height The new height.
   * \sa width() and height().
   */
  void setSize(int width, int height);
  
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
  void swapBuffers() = 0;
  
  /**
   * Gets the window name.
   * 
   * \return The window name.
   */
  inline const std::string& name() const {
    return __name;
  }
  
  /**
   * Gets the window width.
   * 
   * \return The window current width.
   */
  inline int width() const {
    return __width;
  }
  
  /**
   * Gets the window height.
   * 
   * \return The window current height.
   */
  inline int height() const {
    return __height;
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
  Signal<> shown;  /**< Emitted just after the window becomes visible. */
  Signal<> closed; /**< Emitted just after the window is closed. */
  Signal<
      int /* width */,
      int /* height */
    > resized;     /**< Emitted just after the window gets resized. */
    
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
   * Called just after show() or hide() are called.
   * 
   * Implement this function to show and hide the window.
   * 
   * \param visible If true, the window must be shown on the screen,
   *    if false - closed.
   */
  void updateVisibility(bool visible);
  
  /**
   * Called just after setName() is called.
   * 
   * Implement this function to update the window's title bar.
   * 
   * \param name The new window name.
   */
  void updateName(const std::string& name) = 0;
  
  /**
   * Called just after setWidth(), setHeight() or setSize() are called.
   * 
   * Implement this function to update the window on the screen.
   * 
   * \param width The new width.
   * \param height The new height.
   */
  void updateSize(int width, int height) = 0;
  
  /**
   * Called just after setFullscreen() is called.
   * 
   * This function may end in failure, and then it should return false.
   * It everything run properly and the window _is_ fullscreen, return
   * true.
   */
  bool updateFullscreen(bool fullscreen) = 0;
  
  /**
   * \endcond
   */
  
private:
  
  std::string __name;
  int         __width;
  int         __height;
  bool        __visible;
  bool        __fullscreen;
  

}; /** @} */

} /* namespace Dee */

#endif // WINDOW_H
