/*
 * application.cpp
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

#include "core/inputhandler.h"
#include "core/mutex.h"
#include "core/scenemanager.h"
#include "core/scopedmutex.h"
#include "core/slotqueue.h"
#include "core/userinterface.h"
#include "core/window.h"
#include "utils/logger.h"

#ifdef LINUX
# include "core/x11/x11window.h"
#endif

#include "application.h"

namespace Dee {

Application::Application(int argc, char** argv) :
    aboutToQuit(QueuedConnection),
    beforeRender(DirectConnection),
    afterRender(DirectConnection),
    __inputHandler(new InputHandler()),
    __slotQueue(new SlotQueue),
    __window(nullptr),
    __sceneManager(nullptr),
    __isRunning(false),
    __exitCode(0) {
  
  UserInterface::init();
  
  __window = UserInterface::getPlatformWindow();
  __window->closed.connect(this, &Application::quit);
  __window->setName("Deeole");
  
  __sceneManager = new SceneManager();
  __defaultSceneManager = __sceneManager;
  
  Logger::debug("Application: initialized.");
}

Application::~Application() {
  delete __window;
  
  UserInterface::close();
  
  delete __slotQueue;
  
  delete __defaultSceneManager;
  Logger::debug("Application: destructed.");
}

int Application::run() {
  Logger::debug("Application: running...");
  
  __window->show();
  __window->swapBuffers();
  
  __isRunning = true;
  while (__isRunning) {
    UserInterface::processEvents();
    
    emit beforeRender();
    __sceneManager->render();
    emit afterRender();
    
    __slotQueue->processSlots();
    __window->swapBuffers();
  }
  
  emit aboutToQuit();
  __slotQueue->processSlots();
  
  return __exitCode;
}

DeeSlot Application::quit() {
  __exitCode = 0;
  __isRunning = false;
}

DeeSlot Application::terminate() {
  std::terminate();
}

void Application::setSceneManager(SceneManager* manager) {
  static Mutex mutex;
  ScopedMutex m(&mutex);
  
  if (manager)
    __sceneManager = manager;
  else
    __sceneManager = __defaultSceneManager;
}

void Application::processEvents() {
  deeApp->__slotQueue->processSlots();
}

SceneManager* Application::__defaultSceneManager = nullptr;

} /* namespace Dee */
