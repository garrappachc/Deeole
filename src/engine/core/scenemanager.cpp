/*
 * scenemanager.cpp
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

#include <algorithm>

#include "core/application.h"
#include "core/mutex.h"
#include "core/scene.h"
#include "core/scopedmutex.h"
#include "core/window.h"

#include "scenemanager.h"

namespace Dee {
  
SceneManager::SceneManager() :
    __activeScene(nullptr) {
  deeApp->window()->resized.connect(this, &SceneManager::__windowResize);
  
  addScene(new Scene());
}

SceneManager::~SceneManager() {
  for (Scene* s: __scenes)
    delete s;
}

void SceneManager::addScene(Scene* scene) {
  DeeAssert(scene);
  DeeAssert(std::find(__scenes.begin(), __scenes.end(), scene) == __scenes.end());
  
  __scenes.push_back(scene);
  
  if (__activeScene == nullptr)
    __activeScene = scene;
}

void SceneManager::removeScene(Scene* scene) {
  DeeAssert(scene);
  
  for (auto it = __scenes.begin(); it != __scenes.end(); ++it) {
    if (*it == scene) {
      __scenes.erase(it);
      break;
    }
  }
  
  if (__activeScene == scene) {
    if (__scenes.size() > 0)
      __activeScene = __scenes[0];
    else
      __activeScene = nullptr;
  }
}

void SceneManager::setActiveScene(Scene* scene) {
  static Mutex mutex;
  ScopedMutex m(&mutex);
  
  __activeScene = scene;
}

void SceneManager::render() {
  if (__activeScene)
    __activeScene->render();
}

DeeSlot SceneManager::__windowResize(int width, int height) {
  if (__activeScene)
    __activeScene->resizeViewport(width, height);
}

} /* namespace Dee */
