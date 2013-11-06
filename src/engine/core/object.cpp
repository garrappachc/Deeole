/*
 * object.cpp
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

#include "core/signal.h"

#include "object.h"

namespace Dee {
  
Object::~Object() {
  __disconnectAll();
}

void Object::addSender(AbstractSignal* sender) {
  for (AbstractSignal* s: __senders)
    if (s == sender)
      return;
  
  __senders.push_back(sender);
}

void Object::removeSender(AbstractSignal* sender) {
  auto it = __senders.begin();
  
  while (it != __senders.end()) {
    if (*it == sender)
      __senders.erase(it);
    else
      ++it;
  }
}

void Object::__disconnectAll() {
  for (AbstractSignal* s: __senders)
    s->disconnect(this);
  
  __senders.clear();
}

} /* namespace Dee */
