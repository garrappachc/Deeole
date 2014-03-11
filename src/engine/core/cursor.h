/*
 * cursor.h
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

#ifndef CURSOR_H
#define CURSOR_H

#include "core/deeglobal.h"

namespace Dee {

/**
 * \ingroup Core
 * @{
 * 
 * The Cursor class represents the mouse cursor on the screen.
 * 
 * This class gives direct access to the mouse cursor. One can
 * set its position on the screen and set its visibility.
 * 
 * \sa Application::cursor().
 * \TODO Change cursor shape.
 */
class __DeeExport__ Cursor {
  
public:
  
  /**
   * Sets cursor position on the screen. The position is relative
   * to the window.
   * 
   * \param x X coordinate of the new position.
   * \param y Y coordinate of the new position.
   */
  virtual void setPosition(int x, int y) = 0;
  
  /**
   * Sets the visibility.
   * 
   * \param visible If false, the cursor will be hidden, otherwise - shown.
   */
  virtual void setVisible(bool visible) = 0;
  
  /**
   * Shows the cursor.
   * 
   * This function is equivalent to setVisible(true).
   */
  void show();
  
  /**
   * Hides the cursor.
   * 
   * This function is equivalent to setVisible(false).
   */
  void hide();
  
}; /** @} */

} /* namespace Dee */

#endif // CURSOR_H
