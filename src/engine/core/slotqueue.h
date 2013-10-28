/*
 * slotqueue.h
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

#ifndef SLOTQUEUE_H
#define SLOTQUEUE_H

#include <queue>

#include "core/deeglobal.h"
#include "core/singleton.h"

namespace Dee {
  
  class AbstractSlotData;
  class Application;

/**
 * \cond HIDDEN_DOC
 */
class __DeeHide__ SlotQueue : public Singleton<SlotQueue> {

  friend class Application;
  
public:
  inline static void enqueue(AbstractSlotData* slot) {
      singleton().__enqueueSlot(slot);
    }
  
private:
  void processSlots();
  void __enqueueSlot(AbstractSlotData* slot);
  
  std::queue<AbstractSlotData*> __queue;
  
};
/**
 * \endcond
 */

} /* namespace Dee */

#endif // SLOTQUEUE_H
