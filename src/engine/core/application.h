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

#include <string>
#include <map>

#include "core/deeglobal.h"

#include "core/object.h"
#include "core/signal.h"
#include "core/singleton.h"

namespace Dee {
  
  class Cursor;
  class InputHandler;
  class SceneManager;
  class SlotQueue;
  class UserInterface;
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
   * Later, arguments that the application was launched with can be obtained
   * using hasArgument() and argumentValue() functions. For example, calling
   * the application like this: `foo --bar --baz bee` will provide the following
   * results:
   * - `hasArgument("bar")`
   *    `true`
   * - `hasArgument("baz")`
   *    `true`
   * - `argumentValue("baz")`
   *    `"bee"`
   * - `argumentValue("bar")`
   *    `""`
   * - `hasArgument("trololololo")`
   *    `false`
   * 
   * The default command line options are:
   * - `--no-fullscreen`
   *   disables the fullscreen mode (enabled by default). This can be also
   *   achieved by calling `Window::setFullscreen(false)` on the main window;
   * - `--title <title>`
   *    sets the the window title to _title_.
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
   * Sets the desired scene manager as the working one.
   * 
   * You can subclass SceneManager to implement your own scene managing
   * mechanisms. There must always exist at least one scene manager,
   * so passing nullptr will set back the default scene manager.
   * 
   * This function is thread-safe.
   * 
   * \param manager SceneManager instance pointer.
   * \sa SceneManager and sceneManager().
   */
  void setSceneManager(SceneManager* manager);
  
  /**
   * Returns true if the following key was set when launching the application.
   * 
   * The _argName_ parameter is the string that follows the _--_ in the command
   * line argument.
   * 
   * \param argName The argument name, for example `--foo` will become `foo`.
   * \sa argumentValue().
   */
  bool hasArgument(const std::string& argName);
  
  /**
   * The argument value.
   * 
   * The argument value can be a non-empty string (i.e. `--foo bar`), or
   * just the empty string (if the value  was not provided, i.e. `-foo`).
   * 
   * \param argName The argument name (key).
   * \return The value.
   * \sa hasArgument().
   */
  std::string argumentValue(const std::string& argName);
  
  /**
   * Processes all pending slots until the queue is empty.
   */
  static void processEvents();
  
  /**
   * Provides direct access to the global InputHandler instance that manages
   * the application input system.
   * 
   * \return Pointer to the only global InputHandler instance.
   * \sa InputHandler.
   */
  inline static InputHandler* input() {
    return singleton().__inputHandler;
  }
  
  /**
   * Provides direct access to the main application window.
   * 
   * \return Pointer to the window.
   * \sa Window.
   */
  inline static Window* window() {
    return singleton().__window;
  }
  
  /**
   * Provides direct access to the mouse cursor.
   * 
   * \return Pointer to the Cursor instance that represents the mouse cursor.
   * \sa Cursor.
   */
  inline static Cursor* cursor() {
    return singleton().__cursor;
  }
  
  /**
   * Obtains the currently working scene manager.
   * 
   * \return SceneManager instance pointer.
   */
  inline SceneManager* sceneManager() {
    return __sceneManager;
  }
  
  // signals
  Signal<> aboutToQuit; /**< Emitted just before the event loop stops. */
  Signal<> beforeRender; /**< Emitted just before the scene starts to be rendered. */
  Signal<> afterRender; /**< Emitted just after the scene is rendered, but before
                             the buffers are swapped. */
  
  Application() = delete;
  
private:
  
  void __parseArgs(int argc, char** argv);
  
  InputHandler*  __inputHandler;
  SlotQueue*     __slotQueue;
  UserInterface* __userInterface;
  Window*        __window;
  Cursor*        __cursor;
  
  SceneManager* __sceneManager; /**< Currently working scene manager */
  
  bool       __isRunning;
  int        __exitCode;
  
  std::map<std::string, std::string> __arguments;
  
  static SceneManager* __defaultSceneManager; /**< Default SceneManager instance
                                                   pointer. */

}; /** @} */

} /* namespace Dee */

#define deeApp Dee::Application::singletonPtr()

#endif // APPLICATION_H
