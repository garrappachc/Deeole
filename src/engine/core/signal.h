/*
 * signal.h
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

#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>

#include "core/deeglobal.h"

#include "core/eventful.h"
#include "core/slot.h"

namespace Dee {

/**
 * \cond HIDDEN_DOC
 */
class __DeeHide__ AbstractSignal {
public:
  virtual void disconnect(Eventful* receiver) = 0;
};
/**
 * \endcond
 */

/**
 * \ingroup Core
 * @{
 * 
 * The Signal class is a part of the signals-and-slots system.
 * 
 * When the signal is emitted (operator () is called), all bound
 * slots are queued or called directly (depending on the connection type).
 * The signals-and-slots system is thread-safe.
 * 
 * \todo Sample code.
 * 
 * \sa Eventful and ConnectionType.
 */
template <typename... Args>
  class __DeeExport__ Signal:
    public AbstractSignal {
    
    using FunctionType = void (Eventful::*)(Args...);
    using SlotType     = Slot<Args...>;
    
  public:
    
    /**
     * The default constructor.
     * 
     * You can specify the connection type here. It will be the default
     * connection type when connect() is called with AutoConnection as
     * the last parameter.
     * 
     * \param type The type of connection that will be default for this signal.
     * \sa connect() and disconnect().
     */
    Signal(ConnectionType type = AutoConnection) :
       __connectionType(type == AutoConnection ? QueuedConnection : type) {}
    
    /**
     * The destructor.
     * 
     * The destructor removes all connections bound to this signal.
     */
    virtual ~Signal() {
      __freeReceivers();
    }
    
    /**
     * Creates the connection with the given slot.
     * 
     * When the signal is emitted (`operator ()` is called) all connected slots
     * are either queued or called directly here.
     * 
     * \param receiver Receiver of the slot.
     * \param slot The slot.
     * \param type Type of the connection. This type, unless it is
     *  AutoConnection, overrides the type specified in the constructor.
     * \sa disconnect() and emit.
     */
    template <typename CustomFunctionType>
      void connect(Eventful* receiver, CustomFunctionType slot,
                   ConnectionType type = AutoConnection) {
        static_assert(std::is_member_function_pointer<CustomFunctionType>::value,
                      "Slot must be member function pointer!");
        
        if (type == AutoConnection)
          type = __connectionType;
        
        receiver->addSender(this);
        __slots.push_back(SlotType(type, receiver, static_cast<FunctionType>(slot)));
      }
    
    /**
     * Emits the signal.
     * 
     * To have the signals marked out it is strongly advised that you prepend
     * it with the `emit` macro. It is then easier to distiguish slot emission
     * from a regular function call.
     * 
     * \param args Arguments forwarded to the slot.
     */
    void operator ()(Args... args) {
      for (SlotType& slot: __slots)
        slot.call(std::forward<Args>(args)...);
    }
    
    /**
     * Removes the connection.
     * 
     * All connections between the signal and all connected slots of _receiver_
     * are removed.
     * 
     * \param receiver The slots receiver.
     */
    void disconnect(Eventful* receiver) {
      auto it = __slots.begin();
      while (it != __slots.end()) {
        if (it->receiver() == receiver)
          __slots.erase(it);
        else
          ++it;
      }
    }
    
    /**
     * Removes the connection.
     * 
     * The connection between the signal and the _slot_ is removed.
     * 
     * \param receiver The slot receiver.
     * \param slot The slot.
     */
    template <typename CustomFunctionType>
      void disconnect(Eventful* receiver, CustomFunctionType slot) {
        auto it = __slots.begin();
        while (it != __slots.end()) {
          if (it->receiver() == receiver && it->function() == slot)
            __slots.erase(it);
          else
            ++it;
        }
      }
    
  private:
    
    void __freeReceivers() {
      for (SlotType& slot: __slots)
        slot.receiver()->removeSender(this);
      
      __slots.clear();
    }
    
    ConnectionType        __connectionType;
    std::vector<SlotType> __slots;
    
  }; /** @} */

} /* namespace Dee */

#endif // SIGNAL_H
