/*
 * inputhandler.h
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

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "core/deeglobal.h"
#include "core/singleton.h"

namespace Dee {
  
  class Application;
  class Keyboard;
#ifdef LINUX
  class X11Bridge;
#endif

class __DeeExport__ InputHandler : public Singleton<InputHandler> {
  
  friend class Application; // for clearState()
#ifdef LINUX
  friend class X11Bridge; // for keyPressEvent()
#endif

public:
  /**
   * \cond HIDDEN_DOC
   * A constructor.
   * This constructor is disabled by Singleton.
   */
  InputHandler();
  
  /**
   * A destructor.
   */
  virtual ~InputHandler();
  /**
   * \endcond
   */
  
  /**
   * Gives access to the keyboard state.
   * 
   * \return Keyboard pointer.
   */
  inline const Keyboard* keyboard() const {
    return __keyboard;
  }
    
private:
  void clearState();
  void keyPressEvent(unsigned key);
  
  Keyboard * __keyboard;

};

} /* namespace Dee */

#endif // INPUTHANDLER_H
