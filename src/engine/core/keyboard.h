/*
 * keyboard.h
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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "core/deeglobal.h"

namespace Dee {
  
  class InputHandler;

class __DeeExport__ Keyboard {
  
  friend class InputHandler; // clearState() and keyPressEvent()
  
public:
  /**
   * \cond HIDDEN_DOC
   * A constructor.
   * One should not create instances of this class on his own,
   * unless he knows what he is doing.
   */
  Keyboard();
  /**
   * \endcond
   */
  
  /**
   * Checks whether particular key is pressed at the moment or not.
   * 
   * \param key Key.
   * \return True or false.
   */
  bool keyDown(Key::Code key) const;
  
private:
  void clearState();
  void keyPressEvent(unsigned key);
  void keyReleaseEvent(unsigned key);
  
  /* State of the keyboard */
  bool __state[0xFF];

};

} /* namespace Dee */

#endif // KEYBOARD_H
