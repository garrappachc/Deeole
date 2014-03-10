/*
 * event.h
 * Copyright (C) 2014  Michał Garapich <michal@garapich.pl>
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

#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "core/deeglobal.h"

namespace Dee {
  
  class X11Bridge;

/**
 * \ingroup Core
 * @{
 * 
 * The base class for all events.
 */
class __DeeExport__ Event {
  
  friend class X11Bridge;
  
public:
  Event();
  virtual ~Event() = default;
  virtual std::string name() const = 0;
  
  inline bool spontaneous() const {
    return __spontaneous;
  }
  
private:
  void setSpontaneous(bool spontaneous);
  
  bool __spontaneous;
  
}; /** @} */

} /* namespace Dee */

#endif // EVENT_H
