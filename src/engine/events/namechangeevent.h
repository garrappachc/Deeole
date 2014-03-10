/*
 * namechangeevent.h
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

#ifndef NAMECHANGEEVENT_H
#define NAMECHANGEEVENT_H

#include "core/deeglobal.h"
#include "events/event.h"

namespace Dee {

/**
 * \ingroup Core
 * @{
 * 
 * The NameChangeEvent is called when user requests the window title
 * to change.
 */
class __DeeExport__ NameChangeEvent : public Event {
public:
  NameChangeEvent(std::string oldName, std::string newName);
  
  virtual std::string name() const;
  
  inline const std::string& oldName() const {
    return __oldName;
  }
  
  inline const std::string& newName() const {
    return __newName;
  }

private:
  std::string __oldName;
  std::string __newName;

}; /** @} */

} /* namespace Dee */

#endif // NAMECHANGEEVENT_H
