/*
 * scene.h
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

#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "core/deeglobal.h"

namespace Dee {
  
  class Camera;
  class Renderable;
  class SceneManager;

/**
 * \ingroup Core
 * @{
 * 
 * Scene is a base class that represents a single view and sets of
 * items, lights and cameras.
 * 
 * This class can be inherited as well as used in its original form.
 * 
 * \sa SceneManager.
 */
class __DeeExport__ Scene {
  
  friend class SceneManager;
  
public:
  
  /**
   * The default constructor.
   * 
   * The default background color is black.
   */
  Scene();
  
  /**
   * The destructor.
   */
  virtual ~Scene();
  
  /**
   * Clears the viewport with the current backgroud color.
   */
  void clear();
  
  /**
   * Adds the object to the set.
   * 
   * Calling this function adds the given _renderable_ object to the rendering
   * set. In other words, the _renderable_ will be shown if
   * Rederable::visible() returns true and it is in the camera range.
   * 
   * \param renderable Pointer to the renderable object.
   * \sa Renderable::visible().
   */
  void addRenderable(Renderable* renderable);
  
  /**
   * Sets the working camera.
   * 
   * After calling this function, the given camera is used to set up the
   * matrices (projection and modelview).
   * 
   * **NOTE**: Calling this function _after_ the render process of the current
   * frame has started may cause an undefined behaviour.
   * 
   * This function is thread-safe.
   * 
   * \param camera The new camera.
   * \sa camera(), Application::beforeRender and Application::afterRender.
   */
  void setCamera(Camera* camera);
  
  /**
   * Gives access to the scene's camera.
   * 
   * \return The working camera.
   * \sa setCamera().
   */
  inline const Camera* camera() const {
    return __camera;
  }
  
protected:
  
  /**
   * Renders the scene.
   * 
   * The default implementation renders all visible renderable items, using
   * the current camera and with all attached lights.
   * 
   * This method can be overriden by your own implementation, providing more
   * and better functionality.
   */
  virtual void render();
  
  /**
   * Called when the main window is resized and only if the scene is
   * the active one.
   * 
   * \param width The new window width.
   * \param height The new window height.
   * \sa SceneManager::setActiveScene() and SceneManager::activeScene().
   */
  virtual void resizeViewport(int width, int height);
  
private:
  
  std::vector<Renderable*> __objects;
  Camera*                  __camera;
  
  
}; /** @} */

} /* namespace Dee */

#endif // SCENE_H
