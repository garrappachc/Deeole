/*
 * thread.h
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

#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

#include "core/deeglobal.h"

#include "core/eventful.h"
#include "core/signal.h"

namespace Dee {

/**
 * \ingroup Core
 * @{
 * 
 * The Thread class provides an easy and convenient way to implement
 * multi-threaded operations.
 * 
 * Thread is an abstract class. The threaded() pure virtual method is the
 * one that will be run on the separate thread. One must implement this when
 * subclassing the Thread class.
 * 
 * \sa Mutex, Timer.
 */
class __DeeExport__ Thread :
    public Eventful {
  
  /**
   * The system-dependent handle type.
   */
  using HandleType = pthread_t;
  
public:
  
  /**
   * The default constructor.
   * 
   * \sa start().
   */
  Thread();
  
  /**
   * The destructor.
   * 
   * If the thread is still running, it will be canceled. Therefore, you should
   * call join() before to ensure your thread exited properly.
   * 
   * \sa join() and cancel().
   */
  virtual ~Thread();
  
  /**
   * Starts execution of the threaded process.
   * 
   * \return True if thread creation ended with success. Otherwise false.
   * \sa stop(), join(), cancel() and isRunning().
   */
  bool start();
  
  /**
   * This function makes the stopCondition() returns true.
   * 
   * If your threaded process runs a loop, you should check for stopCondition()
   * in every iteration and break the loop when it returns true. This is the
   * most beautiful way to exit the thread. After calling stop() you can call
   * join() to ensure the loop broke properly.
   * 
   * \sa join().
   */
  DeeSlot stop();
  
  /**
   * Waits for the thread to finish its execution.
   * 
   * \sa cancel().
   */
  void join();
  
  /**
   * Cancels the execution immediately. The thread is simply aborted.
   * 
   * \sa stop() and cancel().
   */
  void cancel();
  
  /**
   * Gets handle of the calling thread.
   * 
   * This method can be used to check which thread we are running on.
   * For example:
   * 
   * ~~~~{.cpp}
   * Dee::Thread* someThread = ...;
   * someThread->start();
   * ~~~~
   * 
   * And later:
   * ~~~~{.cpp}
   * if (Dee::Thread::self() == someThread->handle() {
   *   // we are on the same thread
   * }
   * ~~~~
   * 
   * \return Thread identifier.
   * \sa handle().
   */
  static HandleType self();
  
  /**
   * Causes the calling thread to relinquish the CPU. The
   * thread is placed at the end of the run queue for its static priority
   * and another thread is scheduled to run.
   */
  static void yield();
  
  /**
   * Gets this thread's identifier.
   * 
   * \return The thread's identifier.
   */
  inline HandleType handle() const {
    return __handle;
  }
  
  /**
   * Checks whether the thread is still running or not.
   * 
   * \return True if thread has not yet stopped its execution.
   * \sa start(), join() and cancel().
   */
  inline bool isRunning() const {
      return __isRunning;
    }
  
  // signals
  Signal<> started;  /**< Emitted when the thread is about to start,
                          just before the threaded() method is called. */
  Signal<> finished; /**< Emitted just after the thread finished its
                          execution. */
  
protected:
  
  /**
   * Threaded function.
   * You must implement this. This method will be executed on the
   * new thread when start() is called.
   * 
   * \sa start().
   */
  virtual void threaded() = 0;
  
  /**
   * If true, the thread needs to be exited.
   * 
   * \return Stop condition.
   * \sa stop().
   */
  inline bool stopCondition() const {
    return __stopCondition;
  }
  
private:
  static void* __runThreaded(void* args);
  
  HandleType __handle;
  bool       __isRunning;
  bool       __stopCondition;

}; /** @} */

} /* namespace Dee */

#endif // THREAD_H
