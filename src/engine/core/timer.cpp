/*
 * timer.cpp
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

#include <thread>

#include "utils/logger.h"

#include "timer.h"

namespace Dee {
  
Timer::Timer(Timer::Milliseconds timeout) :
    __timeout(timeout) {}

Timer::~Timer() {
  if (isRunning())
    stop();
}

void Timer::setTimeout(Timer::Milliseconds timeout) {
  __timeout = timeout;
}

void Timer::start() {
  if (__timeout == 0) {
    Logger::warning("Timer: trying to start timer with timeout=0! This timer won't start.");
  } else {
    Thread::start();
  }
}

void Timer::threaded() {
  auto last = Clock::now();
  
  while (!stopCondition()) {
    auto now = Clock::now();
    Milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
    
    if (diff >= __timeout) {
      emit timeout();
      last = now;
    }
    
//     std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

} /* namespace Dee */
