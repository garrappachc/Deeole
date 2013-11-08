/*
 * mouse.h
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

#ifndef MOUSE_H
#define MOUSE_H

#include "core/deeglobal.h"

#include "core/vector.h"

namespace Dee {
  
  class InputHandler;

class __DeeExport__ Mouse {

  friend class InputHandler; // clearState() and events
  
public:
  /**
   * \cond HIDDEN_DOC
   * A constructor.
   * One should not create instances of this class on his own,
   * unless he knows what he is doing.
   */
  Mouse();
  /**
   * \endcond
   */
  
  inline int x() const {
    return __x;
  }
  
  inline int y() const {
    return __y;
  }
  
  inline int dx() const {
    return __dx;
  }
  
  inline int dy() const {
    return __dy;
  }
  
  inline Vector3d motion() const {
    return std::move(Vector3d(
      static_cast<float>(dx()),
      static_cast<float>(dy()),
      .0f
    ));
  }
  
private:
  void motionEvent(int x, int y);
  void clearDiff();
  
  int __x;
  int __y;
  int __dx;
  int __dy;

};

} /* namespace Dee */

#endif // MOUSE_H
