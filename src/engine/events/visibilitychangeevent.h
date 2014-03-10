/*
 * visibilitychangeevent.h
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

#ifndef VISIBILITYCHANGEEVENT_H
#define VISIBILITYCHANGEEVENT_H

#include "core/deeglobal.h"
#include "events/event.h"

namespace Dee {

/**
 * \ingroup Core
 * @{
 * 
 * The VisibilityChangeEvent is called whenever user requests the window
 * to hide or show.
 */
class __DeeExport__ VisibilityChangeEvent : public Event {

public:
  VisibilityChangeEvent(bool visible);
  
  std::string name() const override;
  
  inline bool visible() const {
    return __visible;
  }
  
private:
  bool __visible;
  
}; /** @} */

} /* namespace Dee */

#endif // VISIBILITYCHANGEEVENT_H
