/*
 * logger.cpp
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

#include "logger.h"

namespace Dee {
  
bool Logger::__hasColor = true;

void Logger::setColor(bool hasColor) {
  __hasColor = hasColor;
}

const std::string& Logger::__colorize(Logger::LogLevel level) {
  static std::string fatal    = "\e[31;1m";
  static std::string warning  = "\e[33m";
  static std::string info     = "\e[34m";
  static std::string debug    = "\e[37m";
  static std::string nope     = "";
  
  if (!hasColor())
    return nope;
  
  switch (level) {
    case Fatal:
      return fatal;
    case Warning:
      return warning;
    case Info:
      return info;
    case Debug:
      return debug;
  }
  
  return __default();
}

const std::string& Logger::__default() {
  static std::string white = "\e[0m";
  static std::string nope  = "";
  
  if (!hasColor())
    return nope;
  
  return white;
}

} /* namespace Dee */
