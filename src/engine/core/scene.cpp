/*
 * scene.cpp
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

#include <GL/gl.h>
#include <algorithm>

#include "core/camera.h"
#include "core/renderable.h"
#include "core/scenemanager.h"

#include "scene.h"

namespace Dee {

Scene::Scene() :
     __hasAntyaliasing(false) {}

Scene::~Scene() {}

void Scene::clear() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::addRenderable(Renderable* renderable) {
  DeeAssert(std::find(__objects.begin(), __objects.end(), renderable) == __objects.end());
  __objects.push_back(renderable);
}

void Scene::setCamera(Camera* camera) {
  __camera = camera;
}

void Scene::setAntyaliasing(bool antyaliasing) {
  __hasAntyaliasing = antyaliasing;
}

void Scene::render() {
  clear();
  
  if (__camera)
    __camera->setView();
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glEnable(GL_DEPTH_TEST);
  
  // Cull backfacing polygons
//   glCullFace(GL_BACK);
//   glEnable(GL_CULL_FACE);
  
  if (__hasAntyaliasing) {
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
  } else {
    glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POLYGON_SMOOTH);
  }
  
  for (Renderable* r: __objects)
    r->render();
  
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void Scene::resizeViewport(int width, int height) {
  glViewport(0, 0, width, height);
  
  if (__camera)
    __camera->setProjection();
  
  clear();
}


} /* namespace Dee */
