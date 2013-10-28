/*
 * output.cpp
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

#include <cstdio>

#include "output.h"

namespace Dee {
  
Output::Output(Output::Stream stream) :
    __stream(stream) {
  setbuf(stdout, nullptr);
}

Output& Output::operator <<(Output::Special s) {
  switch (s) {
    case Line:
      printf("\n");
  }
  
  return *this;
}

Output& Output::operator <<(char c) {
  printf("%c", c);
  return *this;
}

Output& Output::operator <<(const char* s) {
  printf("%s", s);
  return *this;
}

Output& Output::operator<<(const unsigned char* s) {
  printf("%s", s);
  return *this;
}

Output& Output::operator <<(int i) {
  printf("%d", i);
  return *this;
}

Output& Output::operator<<(unsigned i) {
  printf("%u", i);
  return *this;
}

Output& Output::operator<<(long i) {
  printf("%ld", i);
  return *this;
}

Output& Output::operator<<(long unsigned i) {
  printf("%lu", i);
  return *this;
}

Output& Output::operator <<(float f) {
  printf("%f", f);
  return *this;
}

Output& Output::operator <<(const double& d) {
  printf("%f", d);
  return *this;
}

Output& Output::operator <<(const std::string& s) {
  printf("%s", s.c_str());
  return *this;
}

} /* namespace Dee */
