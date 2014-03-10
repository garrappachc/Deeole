/*
 * resizeevent.h
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

#ifndef RESIZEEVENT_H
#define RESIZEEVENT_H

#include "core/deeglobal.h"
#include "core/size.h"
#include "events/event.h"

namespace Dee {

/**
 * \ingroup Core
 * @{
 * 
 * The ResizeEvent is used to notify the window that user requests
 * to change its size, i.e. by calling Window::setSize().
 */
class __DeeExport__ ResizeEvent : public Event {
  
public:
  ResizeEvent(const Size& oldSize, const Size& newSize);
  
  std::string name() const override;
  
  inline const Size& oldSize() const {
    return __oldSize;
  }
  
  inline const Size& newSize() const {
    return __newSize;
  }
  
private:
  Size __oldSize;
  Size __newSize;
  
  
};  /** @} */

} /* namespace Dee */

#endif // RESIZEEVENT_H
