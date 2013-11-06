/*
 * application.h
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

#ifndef APPLICATION_H
#define APPLICATION_H

#include "core/deeglobal.h"

#include "core/object.h"
#include "core/signal.h"
#include "core/singleton.h"

namespace Dee {
  
  class InputHandler;
  class SlotQueue;
  class Window;

/**
 * \ingroup Core
 * @{
 * 
 * Dee::Application is the base class for all Dee applications.
 * 
 * This class must have exactly one instance. It provides the event loop for
 * the whole application as well as instances of InputHandler or the main
 * Window. The event loop can be started by calling run(). If the application
 * is closed correctly (i.e. by calling quit() or closing the main window),
 * the aboutToQuit signal is emitted at the very end.
 * 
 * NOTE: No signal-slot connections can be made before the instance of
 * Dee::Application is created.
 */
class __DeeExport__ Application :
    public Object,
    public Singleton<Application> {
  
public:
  
  /**
   * The constructor.
   * 
   * This constructor parses the command line arguments and initializes
   * the application.
   * 
   * Available command line options are:
   * - `--no-fullscreen`
   *   disables the fullscreen mode (enabled by default). This can be also
   *   achieved by calling `Window::setFullscreen(false)` on the main window.
   * 
   * \param argc Number of arguments, as passed to the main() function.
   * \param argv Array of arguments, as passed to the main() function.
   * \sa run().
   */
  Application(int argc, char** argv);
  
  /**
   * The destructor.
   * 
   * The destructor closes the window and cleans the application.
   * 
   * \sa quit() and terminate().
   */
  virtual ~Application();
  
  /**
   * Starts the event loop.
   * 
   * This method shows the main window and starts the event loop.
   * To break the event loop, call quit() or close the main window.
   * 
   * \return The reeturn code - 0 on success.
   * \sa quit() and terminate().
   */
  int run();
  
  /**
   * Quits the event loop.
   * 
   * After this slot is called, the event loop is broken (after emitting
   * the last signal - aboutToQuit), the main window is closed and the
   * application exits by returning the success code in run().
   * 
   * \sa terminate().
   */
  DeeSlot quit();
  
  /**
   * Terminates the application.
   * 
   * Usage of this function is highly discouraged. It does not break the
   * event loop, does not call any cleanup functions and does not
   * exit the application properly. It just aborts the execution of the
   * application immediately.
   * 
   * \sa quit().
   */
  DeeSlot terminate();
  
  /**
   * Processes all pending slots until the queue is empty.
   */
  static void processEvents();
  
  inline static InputHandler* input() {
    return singleton().__inputHandler;
  }
  
  inline static Window* window() {
    return singleton().__window;
  }
  
  // signals
  Signal<> aboutToQuit; /**< Emitted just before the event loop stops. */
  Signal<> beforeRender; /**< Emitted just before the scene starts to be rendered. */
  Signal<> afterRender; /**< Emitted just after the scene is rendered, but before
                             the buffers are swapped. */
  
  Application() = delete;
  
private:
  
  InputHandler* __inputHandler;
  SlotQueue*    __slotQueue;
  Window*       __window;
  
  bool       __isRunning;
  int        __exitCode;

}; /** @} */

} /* namespace Dee */

#define deeApp Dee::Application::singletonPtr()

#endif // APPLICATION_H
