/*
 * timer.h
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

#ifndef TIMER_H
#define TIMER_H

#include <chrono>

#include "core/deeglobal.h"

#include "core/thread.h"

namespace Dee {

/**
 * \ingroup Core
 * @{
 * 
 * The Timer class provides high-precission system clock.
 * 
 * The timer can be used to launch slots every given interval.
 * 
 * \sa Thread.
 */
class __DeeExport__ Timer : public Thread {
  
  /* Change to std::chrono::high_resolution_clock if desire */
  using Clock = std::chrono::steady_clock;
  
public:
  
  /**
   * Type used to define milliseconds.
   */
  using Milliseconds = long unsigned int;
  
  /**
   * Time point type.
   */
  using TimePoint = Clock::time_point;
  
  /**
   * The constructor.
   * 
   * \param timeout Timeout (in milliseconds).
   * \sa setTimeout().
   */
  Timer(Milliseconds timeout = 0);
  
  /**
   * The destructor stops the timer (if it is running).
   */
  virtual ~Timer();
  
  /**
   * Sets the timeout to the desired value.
   * 
   * When timeout is reached, the _timeout()_ signal is emitted.
   * 
   * \param timeout Timeout in milliseconds.
   * \sa start() and timeout.
   */
  void setTimeout(Milliseconds timeout);
  
  /**
   * Starts the timer.
   * 
   * The timer will emit the _timeout()_ signal when amount of _timeout_
   * miliseconds (as passed in the constructor or setTimeout() method) is
   * reached. To stop the timer call stop().
   * 
   * \sa timeout and setTimeout().
   */
  void start();
  
  /**
   * Obtains the current system time.
   * 
   * \returns The current timestamp.
   */
  inline static TimePoint now() {
    return Clock::now();
  }
  
  /**
   * Counts the number of milliseconds that have elapsed.
   * 
   * \param from Timestamp.
   * \return Number of milliseconds that have elapsed since _from_.
   * \sa now().
   */
  inline static Milliseconds elapsed(TimePoint from) {
    return std::chrono::duration_cast<std::chrono::milliseconds>
        (now() - from).count();
  }
  
  // signals
  Signal<> timeout; /**< Emited when timer counts the given amount
                         of miliseconds.
                         \sa setTimeout(). */
  
protected:
  
  /**
   * Runs the timer.
   */
  void threaded();
  
private:
  Milliseconds __timeout;
  
}; /** @} */

} /* namespace Dee */

#endif // TIMER_H
