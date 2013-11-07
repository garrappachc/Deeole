/*
 * freecamera.h
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

#ifndef FREECAMERA_H
#define FREECAMERA_H

#include "core/deeglobal.h"

#include "core/camera.h"

namespace Dee {

class __DeeExport__ FreeCamera : public Camera {
  
protected:
  
  /**
   * Prepares the _projection_ matrix.
   */
  void setProjection() const override;
  
  /**
   * Prepares the _modelview_ matrix.
   */
//   void setView() const override;
  
  
};

} /* namespace Dee */

#endif // FREECAMERA_H
