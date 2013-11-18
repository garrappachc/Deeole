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
  
  class Object;
  
/**
 * \cond HIDDEN_DOC
 */
namespace Helpers {
  /* Helpful structs */
  template <int ...S>
    struct Seq {};
  
  template <int N, int ...S>
    struct Gens : Gens<N-1, N-1, S...> {};
  
  template <int ...S>
    struct Gens<0, S...> {
      typedef Seq<S...> type;
    };
}

/**
 * Abstract template class, used to call given slots.
 */
template <typename... Args>
  class __DeeHide__ AbstractSlotCaller {
  public:
    virtual ~AbstractSlotCaller() {}
    virtual void call(const std::tuple<Args...>& args) = 0;
    virtual void call(Args&&... args) = 0;
};

/**
 * Template class, used to call slots on objects.
 */
template <typename... Args>
  class __DeeHide__ ObjectSlotCaller :
    public AbstractSlotCaller<Args...> {
      
    using FunctionType = void (Object::*)(Args...);
     
  public:
    ObjectSlotCaller(Object* receiver, FunctionType function) :
        __receiver(receiver),
        __function(function) {}
    
    void call(const std::tuple<Args...>& args) {
      __unpackCall(args, typename Helpers::Gens<sizeof...(Args)>::type());
    }
    
    void call(Args&&... args) {
      (__receiver->*__function)(args...);
    }
    
    Object* receiver() {
      return __receiver;
    }
    
    FunctionType function() {
      return __function;
    }
    
  private:
    template <int ...S>
      void __unpackCall(const std::tuple<Args...>& args, Helpers::Seq<S...>) {
        (__receiver->*__function)(std::get<S>(args) ...);
      }
    
    Object*    __receiver;
    FunctionType __function;
  };

/**
 * Template class, used to call lambdas (or functions).
 */
template <typename Lambda, typename... Args>
  class __DeeHide__ LambdaSlotCaller :
    public AbstractSlotCaller<Args...> {
    
  public:
    LambdaSlotCaller(Lambda lambda) :
        __lambda(lambda) {}
    
    void call(const std::tuple<Args...>& args) {
      __unpackCall(args, typename Helpers::Gens<sizeof...(Args)>::type());
    }
    
    void call(Args&&... args) {
      __lambda(args...);
    }
    
  private:
    template <int ...S>
      void __unpackCall(const std::tuple<Args...>& args, Helpers::Seq<S...>) {
        (__lambda)(std::get<S>(args) ...);
      }
      
    Lambda __lambda;
  };

/**
 * Abstract class, used to store items and callers.
 */
class __DeeHide__ AbstractSlotData {
public:
  virtual ~AbstractSlotData() = default;
  virtual void call() = 0;  
};

/**
 * Class used to store one particular slot.
 */
template <typename... Args>
  class __DeeHide__ SlotData :
    public AbstractSlotData {
    
    using FunctionType = void (Object::*)(Args...);
    
  public:
    SlotData(AbstractSlotCaller<Args...>* caller, Args&&... args) :
        __caller(caller),
        __data(std::forward<Args>(args)...) {}
    
    void call() override {
      __caller->call(__data);
    }
    
  private:
    AbstractSlotCaller<Args...>* __caller;
    std::tuple<Args...>          __data;
    
  };
  
template <typename... Args>
  class __DeeHide__ Slot {
    
    using FunctionType = void (Object::*)(Args...);
    
  public:
    Slot(ConnectionType type, Object* receiver,
         FunctionType function) :
        __connectionType(type),
        __caller(new ObjectSlotCaller<Args...>(receiver, function)) {}
    
    template <typename LambdaType>
      Slot(ConnectionType type, LambdaType lambda):
          __connectionType(type),
          __caller(new LambdaSlotCaller<LambdaType, Args...>(lambda)) {}
    
    virtual ~Slot() {
      delete __caller;
    }
    
    void call(Args&&... args) {
      __connectionType == QueuedConnection ?
          SlotQueue::enqueue(
            new SlotData<Args...>(__caller, std::forward<Args>(args)...)) :
          __caller->call(std::forward<Args>(args)...);
    }
    
    Object* receiver() {
      auto c = dynamic_cast<ObjectSlotCaller<Args...>*>(__caller);
      if (c)
        return c->receiver();
      else
        return nullptr;
    }
    
    FunctionType function() {
      auto c = dynamic_cast<ObjectSlotCaller<Args...>*>(__caller);
      if (c)
        return c->function();
      else
        return nullptr;
    }
    
  private:
    ConnectionType               __connectionType;
    AbstractSlotCaller<Args...>* __caller;
    
  };
/**
 * \endcond
 */

} /* namespace Dee */

#endif // SLOT_H
