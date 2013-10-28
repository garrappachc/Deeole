/*
 * singleton.h
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


#ifndef SINGLETON_H
#define SINGLETON_H

#include <cstdint>

#include "core/deeglobal.h"

namespace Dee {

/**
 * \ingroup Core
 * @{
 * 
 * Singleton prevents from creating more than one instance of the class.
 * 
 * Usage:
 * 
 * ~~~~{.cpp}
 * class Foo : public Dee::Singleton<Foo>
 * { ... }
 * ~~~~
 * 
 * Subclassing Singleton provides getSingleton() and getSingletonPtr()
 * methods.
 */
template <typename T>
  class __DeeExport__ Singleton {
  
  public:
    
    /**
     * The default constructor.
     */
    Singleton() {
      DeeAssert(!__singleton);

      /*
       * This is a little bit complicated, but the best singleton implementation
       * I've ever seen.
       * It counts the relative inherited class's address and stores it in
       * __ms_Singleton. Notice that derived class can inherit from more than one
       * Singleton class, but in that case 'this' of the derived class can differ
       * from 'this' of the Singleton. Solution of this problem is to get
       * non-existent object from address 0x1, casting it to both types and
       * check the difference, which is in fact the distance between
       * Singleton< T > and its derived type T.
       */
      intptr_t offset = (intptr_t)(T*)1 - (intptr_t)(Singleton*)(T*)1;
      __singleton = (T*)((intptr_t)this + offset);
    }

    /**
     * The destructor.
     */
    ~Singleton() {
      DeeAssert(__singleton);
      __singleton = nullptr;
    }

    /**
     * Obtains the instance reference.
     */
    static T& singleton() {
      DeeAssert(__singleton);
      return *__singleton;
    }

    /**
     * Obtains the instance pointer.
     */
    static T* singletonPtr() {
      DeeAssert(__singleton);
      return __singleton;
    }
    
  private:
    static T* __singleton;
    
  }; /** @} */

template <typename T>
  T* Singleton<T>::__singleton = nullptr;
  
} /* namespace Dee */

#endif  /* SINGLETON_H */
