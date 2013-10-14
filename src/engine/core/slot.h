/*
 * slot.h
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

#ifndef SLOT_H
#define SLOT_H

#include <tuple>

#include "core/deeglobal.h"
#include "core/slotqueue.h"

namespace Dee {
  
  class Eventful;
  
/**
 * \cond HIDDEN_DOC
 */
class __DeeHide__ AbstractSlotData {
public:
  virtual ~AbstractSlotData() = default;
  virtual void call() = 0;
};

template <typename... Args>
  class __DeeHide__ SlotData :
    public AbstractSlotData {
    
    using FunctionType = void (Eventful::*)(Args...);
    
    /* Helpful structs */
    template <int ...S>
      struct __seq {};
    
    template <int N, int ...S>
      struct __gens : __gens<N-1, N-1, S...> {};
    
    template <int ...S>
      struct __gens<0, S...> {
        typedef __seq<S...> type;
      };
    
    template <int ...S>
      void __unpackCall(__seq<S...>) {
        (__receiver->*__function)(std::get<S>(__data) ...);
      }
    
  public:
    SlotData(Eventful* receiver, FunctionType function, Args&&... args) :
        __receiver(receiver),
        __function(function),
        __data(std::forward<Args>(args)...) {}
    
    void call() {
      __unpackCall(typename __gens<sizeof...(Args)>::type());
    }
        
  private:
    Eventful*           __receiver;
    FunctionType        __function;
    std::tuple<Args...> __data;
    
  };

template <typename... Args>
  class __DeeHide__ Slot {
    
    using FunctionType = void (Eventful::*)(Args...);
    
  public:
    Slot(ConnectionType type = QueuedConnection, Eventful* receiver = nullptr,
         FunctionType function = nullptr) :
        __connectionType(type),
        __function(function),
        __receiver(receiver) {}
    
    void call(Args&&... args) {
      DeeAssert(__receiver);
      
      __connectionType == QueuedConnection ?
          SlotQueue::enqueue(
            new SlotData<Args...>(__receiver, __function, std::forward<Args>(args)...)) :
          (__receiver->*__function)(std::forward<Args>(args)...);
    }
    
    Eventful* receiver() {
      return __receiver;
    }
    
    FunctionType function() {
      return __function;
    }
    
  private:
    ConnectionType __connectionType;
    FunctionType   __function;
    Eventful*      __receiver;
    
  };
/**
 * \endcond
 */

} /* namespace Dee */

#endif // SLOT_H
