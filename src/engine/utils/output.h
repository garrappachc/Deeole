/*
 * output.h
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

#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>

#include "core/deeglobal.h"

namespace Dee {
  
  class Size;

/**
 * \ingroup Utils
 * @{
 * 
 * The Output class provides common output stream interface.
 * 
 * The purpose of this class is to provide easy in use and elastic output
 * controller. It can print everything to the standard output or write
 * to the custom log file.
 * 
 * \sa Logger.
 */
class __DeeExport__ Output {
  
public:
  
  /**
   * Specifies the output stream.
   * 
   * \sa setStream() and stream().
   */
  enum Stream {
    
    /**
     * The default stream.
     * 
     * Redirects all output to the standard output.
     */
    StandardOutput
    
  };
  
  /**
   * Defines a couple of special characters and strings.
   */
  enum Special {
    
    /**
     * New line.
     * 
     * On Linux, it is just `\n`, whilst on Windows with stream() = `File` it
     * becomes `\r\n`.
     */
    Line
    
  };
  
  Output(Stream stream = Output::StandardOutput);
  
  Output& operator <<(Output::Special s);
  
  Output& operator <<(char c);
  Output& operator <<(const char* s);
  Output& operator <<(const unsigned char* s);
  Output& operator <<(int i);
  Output& operator <<(unsigned i);
  Output& operator <<(long i);
  Output& operator <<(long unsigned i);
  Output& operator <<(float f);
  Output& operator <<(const double& d);
  
  Output& operator <<(const std::string& s);
  
  Output& operator <<(const Size& size);
  
private:
  
  Stream __stream;

}; /** @} */

} /* namespace Dee */

#endif // OUTPUT_H
