/*
 * renderable.h
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

#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "core/deeglobal.h"

#include "core/object.h"

namespace Dee {
  
  class Scene;

/**
 * \ingroup Core
 * @{
 * 
 * The Renderable class is a base class for every object that can be
 * rendered on the scene.
 */
class __DeeExport__ Renderable : public Object {
  
  friend class Scene;
  
public:
  
  /**
   * Default constructor.
   * 
   * \param visible Indicates wheter the object is visible or not.
   * \sa setVisible() and visible().
   */
  Renderable(bool visible = true);
  
  /**
   * Sets the visibility.
   * 
   * \param visible If true, the object will be rendered, otherwise
   *                it will be omitted.
   * \sa visible().
   */
  DeeSlot setVisible(bool visible);
  
  /**
   * Gets the visibility of the object.
   */
  inline bool visible() const {
    return __visible;
  }
  
protected:
  
  /**
   * Renders the object.
   */
  virtual void render() = 0;
  
private:
  bool __visible;
  
  /**
   * 
   */
  
  
}; /** @} */

} /* namespace Dee */

#endif // RENDERABLE_H
