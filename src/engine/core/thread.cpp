/*
 * thread.cpp
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

#include "core/application.h"
#include "utils/logger.h"

#include "thread.h"

namespace Dee {
  
Thread::Thread() :
    __handle(static_cast<HandleType>(0)),
    __isRunning(false),
    __stopCondition(false) {}

Thread::~Thread() {
  cancel();
}

bool Thread::start() {
  bool result = pthread_create(&__handle, nullptr, __runThreaded, this) == 0;
  Logger::debug("Thread: %i started.", __handle);
  return result;
}

void Thread::stop() {
  __stopCondition = true;
}

void Thread::join() {
  if (__isRunning)
    pthread_join(__handle, nullptr);
}

void Thread::cancel() {
  if (__isRunning)
    pthread_cancel(__handle);
}

Thread::HandleType Thread::self() {
  return pthread_self();
}

void Thread::yield() {
  pthread_yield();
}

void* Thread::__runThreaded(void* args) {
  Thread* instance = reinterpret_cast<Thread*>(args);
  
  instance->__isRunning = true;
  emit instance->started();
  instance->threaded();
  instance->__isRunning = false;
  emit instance->finished();
  
  Logger::debug("Thread: %i finished.", instance->handle());
  
  return nullptr;
}

} /* namespace Dee */
