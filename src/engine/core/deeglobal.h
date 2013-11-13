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
  
  constexpr float Pi = 3.14159265359f;
  
  template <typename T>
    float deg2Rad(const T& deg) {
      static constexpr float coeff = Pi / 180.0f;
      return deg * coeff;
    }
  
  template <typename T>
    T bound(const T& min, const T& value, const T& max) {
      if (value < min)
        return min;
      if (value > max)
        return max;
      return value;
    }
  
  float cos(float angle);
  float sin(float angle);
  float tan(float angle);
  
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
  
  namespace Key {
    
    /**
     * \ingroup Core
     * 
     * Convenience enum to provide each key code in a readable form.
     */
    enum Code {
      Void = 0x0,
      
      Esc = 0x9,
      
      Key1 = 0xA,
      Key2 = 0xB,
      Key3 = 0xC,
      Key4 = 0xD,
      Key5 = 0xE,
      Key6 = 0xF,
      Key7 = 0x10,
      Key8 = 0x11,
      Key9 = 0x12,
      Key0 = 0x13,
      
      Minus     = 0x14,
      Equal     = 0x15,
      Backspace = 0x16,
      
      Tab = 0x17,
      
      Q = 0x18,
      W = 0x19,
      E = 0x1A,
      R = 0x1B,
      T = 0x1C,
      Y = 0x1D,
      U = 0x1E,
      I = 0x1F,
      O = 0x20,
      P = 0x21,
      
      BracketOpen  = 0x22, /**< Square bracket left */
      BracketClose = 0x23, /**< Square bracket right */
      
      Enter = 0x24,
      LCtrl = 0x25,
      
      A = 0x26,
      S = 0x27,
      D = 0x28,
      F = 0x29,
      G = 0x2A,
      H = 0x2B,
      J = 0x2C,
      K = 0x2D,
      L = 0x2E,
      
      Semicolon = 0x2F,
      Quote     = 0x30,
      LShift    = 0x32,
      Backquote = 0x31,
      Backslash = 0x33,
      
      Z = 0x34,
      X = 0x35,
      C = 0x36,
      V = 0x37,
      B = 0x38,
      N = 0x39,
      M = 0x3A,
      
      Comma       = 0x3B,
      Period      = 0x3C,
      Slash       = 0x3D,
      RShift      = 0x3E,
      NumMultiply = 0x3F,
      
      LAlt     = 0x40,
      Space    = 0x41,
      CapsLock = 0x42,
      
      F1 =  0x43,
      F2 =  0x44,
      F3 =  0x45,
      F4 =  0x46,
      F5 =  0x47,
      F6 =  0x48,
      F7 =  0x49,
      F8 =  0x4A,
      F9 =  0x4B,
      F10 = 0x4C,
      
      NumLock    = 0x4D,
      
      Num7     = 0x4F,
      Num8     = 0x50,
      Num9     = 0x51,
      NumMinus = 0x52,
      Num4     = 0x53,
      Num5     = 0x54,
      Num6     = 0x55,
      NumAdd   = 0x56,
      Num1     = 0x57,
      Num2     = 0x58,
      Num3     = 0x59,
      Num0     = 0x5A,
      NumDel   = 0x5B,
      
      LBackslash = 0x5E,
      
      F11 = 0x5F,
      F12 = 0x60,
      
      NumEnter = 0x68,
      RCtrl    = 0x69,
      NumSlash = 0x6A,
      RAlt     = 0x6C,
      Home     = 0x6E,
      Up       = 0x6F,
      PageUp   = 0x70,
      Left     = 0x71,
      Right    = 0x72,
      Down     = 0x74,
      PageDown = 0x75,
      End      = 0x73,
      Delete   = 0x77,
      Pause    = 0x7F,
      Super    = 0x85,
    };
  } /* namespace Key */
  
}

#endif // DEEGLOBAL_H
