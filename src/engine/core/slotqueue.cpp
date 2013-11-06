/*
 * slotqueue.cpp
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

#include "core/object.h"
#include "core/slot.h"

#include "slotqueue.h"

namespace Dee {
  
void SlotQueue::processSlots() {
  while (!__queue.empty()) {
    AbstractSlotData* slot = __queue.front();
    slot->call();
    delete slot;
    
    __queue.pop();
  }
}

void SlotQueue::__enqueueSlot(AbstractSlotData* slot) {
  __queue.push(slot);
}

} /* namespace Dee */
