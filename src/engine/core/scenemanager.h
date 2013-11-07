/*
 * scenemanager.h
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

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>

#include "core/deeglobal.h"

#include "core/object.h"

namespace Dee {
  
  class Application;
  class Scene;

/**
 * \ingroup Core
 * @{
 * 
 * SceneManager is a utility class that handles scene manipulation.
 * 
 * The SceneManager class contains all the scenes, switches between
 * them and gives an acesss to all of them.
 * 
 * The default scene manager can be replaces by your own. You can
 * override the render() method and call Application::setSceneManager().
 * However, your scene manager instance has to be deleted manually then.
 * 
 * \sa Application::setSceneManager().
 */
class __DeeExport__ SceneManager : public Object {
  
  friend class Application;
  
public:
  
  /**
   * The default constructor - no scenes, nothing to render.
   */
  SceneManager();
  
  /**
   * The destructor deletes all the scenes (if there are any).
   */
  virtual ~SceneManager();
  
  /**
   * Adds the given scene to the scene set.
   * 
   * If there was no scene in the manager before, this one will
   * become the active one.
   * 
   * This function takes ownership of the scene.
   * 
   * \param scene A pointer to the Scene instance.
   * \sa removeScene() and setActiveScene().
   */
  void addScene(Scene* scene);
  
  /**
   * Removes desired scene from the current scene set.
   * 
   * This function does not delete the instance. Instead, it removes the
   * pointer from the scene manager so you can delete it manually.
   * 
   * \param scene The desired scene to be removed.
   * \sa addScene().
   */
  void removeScene(Scene* scene);
  
  /**
   * Sets the given scene as the active one.
   * 
   * This function is thread-safe.
   * 
   * \param scene The scene pointer.
   * \sa addScene() and activeScene().
   */
  void setActiveScene(Scene* scene);
  
  /**
   * Gets the active scene pointer.
   * 
   * \return Scene instance pointer.
   * \sa setActiveScene().
   */
  inline Scene* activeScene() {
    return __activeScene;
  }
  
  /**
   * Gets the active scene pointer.
   * 
   * \return Scene instance pointer.
   * \sa setActiveScene().
   */
  inline const Scene* activeScene() const {
    return __activeScene;
  }
  
  /**
   * Obtains all the scenes.
   */
  inline const std::vector<Scene*>& scenes() const {
    return __scenes;
  }
  
protected:
  
  /**
   * Renders the active scene.
   * 
   * This function can be overriden, so the scene management
   * can be improved.
   * 
   * \sa Application::setSceneManager().
   */
  virtual void render();
  
private:
  
  DeeSlot __windowResize(int width, int height);
  
  std::vector<Scene*> __scenes;
  Scene*              __activeScene;
  
  
}; /** @} */

} /* namespace Dee */

#endif // SCENEMANAGER_H
