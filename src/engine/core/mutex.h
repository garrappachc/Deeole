/*
 * mutex.h
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

#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

#include "core/deeglobal.h"

namespace Dee {

/**
 * \ingroup Core
 * @{
 * 
 * The Mutex class provides safe data access control for multithreaded operations.
 * 
 * The purpose of Mutex class is to protect shared data from multiple writes
 * by two or more threads in the same moment. When one thread needs to write to
 * a block of memory, it locks the mutex. When a particular mutex is locked,
 * no other thread can lock it at the time and must wait until the mutex is
 * unlocked by the owning thread.
 * 
 * \sa ScopedMutex.
 */
class __DeeExport__ Mutex {
  
  using HandleType = pthread_mutex_t;
  
public:
  
  /**
   * The default constructor.
   * 
   * Constructs mutex in an unlocked state.
   * 
   * \sa lock() and unlock().
   */
  Mutex();
  
  /**
   * Destroys the mutex.
   */
  virtual ~Mutex();
  
  /**
   * Locks the mutex. If another thread has locked the mutex before, this
   * function will wait until the lock is removed.
   * 
   * \sa tryLock() and unlock().
   */
  void lock();
  
  /**
   * Tries to lock the mutex. If the attempt was successful, mutex is locked
   * and function returns true. If another thread has locked the mutex before,
   * this function returns false and state of the mutex remains unchanged.
   * 
   * \return True if lock attempt was successful, otherwise false.
   * \sa lock() and unlock().
   */
  bool tryLock();
  
  /**
   * Unlocks the mutex.
   * Trying to unlock the unlocked mutex results in undefined behaviour.
   * 
   * \sa lock().
   */
  void unlock();
  
private:
  HandleType __handle;

}; /** @} */

} /* namespace Dee */

#endif // MUTEX_H
