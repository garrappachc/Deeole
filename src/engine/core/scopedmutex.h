/*
 * scopedmutex.h
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

#ifndef SCOPEDMUTEX_H
#define SCOPEDMUTEX_H

#include "core/deeglobal.h"

namespace Dee {
  
  class Mutex;

/**
 * \ingroup Core
 * @{
 * 
 * The ScopedMutex class provides easy auto-unlocking mechanism for mutex.
 * 
 * Without ScopedMutex:
 * 
 * ~~~~{.cpp}
 * Foo* returnFoo(int cond) {
 *   static Foo foo;
 *   static Mutex mutex;
 *   mutex.lock();
 *   
 *   if (cond == 0) {
 *     if (!foo->bar()) {
 *       foo->doBar();
 *       mutex.unlock();
 *       return foo;
 *     } else {
 *       foo->doBaz();
 *     }
 *   } else {
 *     foo->doSomethingElse();
 *     mutex.unlock();
 *     return foo;
 *   }
 *   
 *   foo->final();
 *   mutex.unlock();
 *   return foo;
 * }
 * ~~~~
 * 
 * As we see, we have to call mutex.unlock() each time just before the
 * `return` statement. ScopedMutex simplifies mutex unlocking, doing this
 * automatically when it goes out of the scope:
 * 
 * ~~~~{.cpp}
 * Foo* returnFoo(int cond) {
 *   static Foo foo;
 *   static Mutex mutex;
 *   ScopedMutex(&mutex);
 *   
 *   if (cond == 0) {
 *     if (!foo->bar()) {
 *       foo->doBar();
 *       return foo;
 *     } else {
 *       foo->doBaz();
 *     }
 *   } else {
 *      foo->doSomethingElse();
 *      return foo;
 *   }
 *   
 *   foo->final();
 *   return foo;
 * }
 * ~~~~
 * 
 * Not only is it shorter, but it also prevents from forgetting about Mutex
 * unlocking, which may end in deadlock.
 * 
 * \sa Mutex.
 */
class __DeeExport__ ScopedMutex {
  
public:
  
  /**
   * The constructor.
   * 
   * This constructor gets the Mutex pointer and locks it.
   * 
   * \param mutex Mutex to be used.
   * \sa Mutex::lock().
   */
  ScopedMutex(Mutex* mutex);
  
  /**
   * THe destructor unlocks the mutex.
   */
  virtual ~ScopedMutex();
  
private:
  
  Mutex* __mutex;
  

}; /** @} */

} /* namespace Dee */

#endif // SCOPEDMUTEX_H
