/*
 * deeglobal.h
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

#ifndef DEEGLOBAL_H
#define DEEGLOBAL_H

#include "config.h"

#if defined(LINUX)
# define __DeeExport__ __attribute__((visibility("default")))
# define __DeeHide__   __attribute__((visibility("hidden")))
# define __DeeUnused__ __attribute__((unused))
#else
# define __DeeExport__
# define __DeeHide__
# define __DeeUnused__
# error "Forgive me, but your operating system is not supported."
#endif

inline void dee_noop() {}

void __DeeExport__ dee_assert(const char* cond, const char* file, int line);

#define emit

#ifdef DEE_DEBUG
# define DeeAssert(cond) (cond) ? dee_noop() : dee_assert(#cond, file, line)
#else
# define DeeAssert(cond) dee_noop()
#endif

typedef void DeeSlot;

namespace Dee {
  
  enum ConnectionType {
    AutoConnection,
    QueuedConnection,
    DirectConnection
  };
  
}

#endif // DEEGLOBAL_H
