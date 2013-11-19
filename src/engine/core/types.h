/*
 * types.h
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

#ifndef TYPES_H
#define TYPES_H

namespace Dee {

/**
 * Type traits for Deeole.
 */
namespace Types {
  template <typename T, typename...>
    struct all_of_type;
    
  template <typename T>
    struct all_of_type<T> :
      std::true_type
    {};
    
  template <typename T, typename First, typename ...Rest>
    struct all_of_type<T, First, Rest...> :
      std::integral_constant<bool,
        std::is_convertible<T, First>::value && all_of_type<T, Rest...>::value>
    {};
}

}

#endif // TYPES_H
