/*
 * logger.h
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

#ifndef LOGGER_H
#define LOGGER_H

#include <string>

#include "core/deeglobal.h"

#include "core/application.h"
#include "core/singleton.h"
#include "core/mutex.h"
#include "core/scopedmutex.h"
#include "utils/output.h"

namespace Dee {

/**
 * \ingroup Utils
 * @{
 * 
 * The Logger class simplifies output management.
 * 
 * There are four functions that report four different levels of messages.
 * Usage is similar to C-style printf, although it is type-safe.
 * 
 * Sample usage:
 * ~~~~{.cpp}    
 * int i = 3;
 * Logger::info("Value of i is %d.", i);
 * ~~~~
 */
class __DeeExport__ Logger :
    public Singleton<Logger> {
  
  enum LogLevel {
    Fatal,
    Warning,
    Info,
    Debug
  };
  
public:
  
  /**
   * \cond HIDDEN_DOC
   */
  inline static void log(const char* str) {
    __out() << str;
  }
  
  template <typename T, typename... Args>
    static void log(const char* str, T value, Args... args) {
      while (*str) {
        if (*str == '%' && *(++str) != '%') {
          __out() << value;
          log(*str ? ++str : str, args...);
          return;
        }
        
        __out() << *str++;
      }
    }
  /**
   * \endcond
   */
  
  /**
   * Reports fatal errors.
   * On Unix terminals, this kind of report is printed in bold red.
   * 
   * **NOTE**: After calling this function the application will terminate.
   * 
   * Sample usage:
   * ~~~~{.cpp}
   * int ret = neededFunction();
   * if (ret)
   *   Logger::fatal("neededFunction() returned %i. Cannot continue.", ret);
   * ~~~~
   *     
   * \param str Format string.
   * \param args Arguments.
   * \sa DeeAssert(), warning(), info() and debug().
   */
  template <typename... Args>
    static void fatal(const char* str, Args... args) {
      __out() << __colorize(Fatal);
      log(str, args...);
      __out() << Output::Line << __default();
      
      deeApp->terminate();
    }
  
  /**
   * Reports warnings.
   * On Unix terminals, this kind of report is printed in yellow.
   * 
   * \param str Format string.
   * \param args Arguments.
   * \sa fatal(), info() and debug().
   */
  template <typename... Args>
    static void warning(const char* str, Args... args) {
      __out() << __colorize(Warning);
      log(str, args...);
      __out() << Output::Line << __default();
    }
  
  /**
   * Reports run-time information.
   * On Unix terminals, this kind of report is printed in blue.
   * 
   * \param str Format string.
   * \param args Arguments.
   * \sa fatal(), warning() and debug().
   */
  template <typename... Args>
    static void info(const char* str, Args... args) {
      __out() << __colorize(Info);
      log(str, args...);
      __out() << Output::Line << __default();
    }
  
  /**
   * Reports run-time debug information.
   * On Unix terminals, this kind of report is printed in white.
   * 
   * \param str Format string.
   * \param args Arguments.
   * \sa fatal(), warning() and info().
   */
  template <typename... Args>
    static void debug(const char* str, Args... args) {
      __out() << __colorize(Debug);
      log(str, args...);
      __out() << Output::Line << __default();
    }
  
  /**
   * Specifies whther the logger should colorize the output or not.
   * 
   * Switching it off may be helpful when launching Deeole-based application
   * in any kind of terminal that does not support colors.
   * 
   * Default: _true_.
   * 
   * \param hasColor If false, Logger will not try to colorize the output.
   */
  static void setColor(bool hasColor);
  
  /**
   * Checks whether currently logger colorizes the output or not.
   * 
   * \return False if the output is not colorized.
   */
  inline static bool hasColor() {
    return __hasColor;
  }
  
  /**
   * \cond HIDDEN_DOC
   */
  Logger() = delete;
  /**
   * \endcond
   */
  
private:
  inline static Output& __out() {
    static Output output;
    static Mutex mutex;
    
    ScopedMutex m(&mutex);
    return output;
  }
  
  static const std::string& __colorize(LogLevel level);
  static const std::string& __default();
  
  static bool __hasColor;

}; /** @} */

} /* namespace Dee */

#endif // LOGGER_H
