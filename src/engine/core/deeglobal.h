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

/**
 * \defgroup Core
 * Core Deeole classes.
 */

/**
 * \defgroup Utils
 * Deeole utilities (such as Logger).
 */

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

#ifdef DEE_DEBUG
# define DeeAssert(cond) (cond) ? dee_noop() : dee_assert(#cond, __FILE__, __LINE__)
#else
# define DeeAssert(cond) dee_noop()
#endif

#define emit

/**
 * To mark slots, use this type.
 */
typedef void DeeSlot;

namespace Dee {
  
  /**
   * \ingroup Core
   * 
   * Describes signal-slot connection type.
   * 
   * \related Signal.
   */
  enum ConnectionType {
    
    /**
     * Auto connection.
     * 
     * The signal can set its default connection type. It is passed
     * in the constructor. If unsure witch type to use, one should
     * choose this one.
     * 
     * This is the default connection type.
     */
    AutoConnection,
    
    /**
     * Queued connection.
     * 
     * Using Queued connection, every slot is enqueued to be called when
     * next Application::processEvents() is called. The advantages of
     * this connection are that it is thread-safe (slots are always executed
     * on the main application thread) and lets the current loop quit properly
     * (in case, for example, when one connects a signal to the
     * Application::quit() slot). However, this type of connection causes the
     * slot execution is delayed and the data gets copied twice (from signal
     * to the queue and from the queue to the slot), and therefore it is not
     * recommended to be used when the efficiency is the priority.
     */
    QueuedConnection,
    
    /**
     * Direct connection.
     * 
     * The direct connection type is much more efficient than the queued one,
     * as arguments passed to the signal are forwarded directly to the slot.
     * This function, however, is not thread-safe. The slot is called
     * immediately after the signal is emited, on the same thread.
     */
    DirectConnection
  };
  
}

#endif // DEEGLOBAL_H
