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

#include "core/slotqueue.h"
#include "utils/logger.h"

#include "application.h"

namespace Dee {
  
Application::Application(int argc, char** argv) :
    aboutToQuit(QueuedConnection),
    __slotQueue(new SlotQueue),
    __isRunning(false),
    __exitCode(0) {
  Logger::debug("Application: initialized.");
}

Application::~Application() {
  delete __slotQueue;
  
  Logger::debug("Application: destructed.");
}

int Application::run() {
  Logger::debug("Application: running...");
  
  __isRunning = true;
  while (__isRunning) {
    __slotQueue->processSlots();
  }
  
  emit aboutToQuit();
  __slotQueue->processSlots();
  
  return __exitCode;
}

DeeSlot Application::quit() {
  Logger::debug("Application: exiting...");
  
  __exitCode = 0;
  __isRunning = false;
}

DeeSlot Application::terminate() {
  std::terminate();
}

void Application::processEvents() {
  deeApp->__slotQueue->processSlots();
}

} /* namespace Dee */
