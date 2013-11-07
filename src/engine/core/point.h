/*
 * point.h
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

#ifndef POINT_H
#define POINT_H

#include <cstring>
#include <utility>

#include "core/deeglobal.h"

#include "core/vector.h"

namespace Dee {

/**
 * \ingroup Core
 * @{
 * 
 * The AbstractPoint is a base class for all Point classes.
 * 
 * \param T Type of the coordinates.
 * \sa Vector.
 */
template <typename T>
  class __DeeExport__ AbstractPoint {
    
  public:
    
    /**
     * Obtain the dimension of the point.
     * 
     * \return Number of coordinates.
     */
    virtual const unsigned dimension() const = 0;
    
    /**
     * Obtain specific coordinate.
     * 
     * \param i The index of desired coordinate.
     * \return The _i_-th coordinate.
     */
    virtual const T& operator [](unsigned i) const = 0;
    
    /**
     * Obtain specific coordinate.
     * 
     * \param i The index of desired coordinate.
     * \return The _i_-th coordinate.
     */
    virtual T& operator [](unsigned i) = 0;
  }; /** @} */

/**
 * \ingroup Core
 * @{
 * 
 * The Point class is used to define a single point in the N-dimensional
 * space.
 * 
 * \param T Type of the coordinates.
 * \param N Dimension of the point.
 * \sa Vector.
 */
template <typename T, unsigned N>
  class __DeeExport__ Point :
    public AbstractPoint<T>{
  
  public:
    
    /**
     * The default constructor.
     * 
     * All coordinates are set to 0.
     */
    Point() {
      memset(__data, 0, sizeof(T) * N);
    }
    
    /**
     * The copy constructor.
     * 
     * \param other The point that this one will be constructed from.
     */
    Point(const Point& other) {
      memcpy(__data, other.__data, sizeof(T) * N);
    }
    
    /**
     * The variadic template constructor.
     * 
     * Used to construct the point with the given values. The usage is simple:
     * ~~~~{.cpp}
     * Point<int, 3> p(1, 2, 3);
     * Point<float, 2> f(2.5f, .3f);
     * ~~~~
     */
    template <typename... Args>
      Point(Args... values) :
          __data{ values... } {
        static_assert(sizeof...(Args) == N,
                      "Argument count must match the point's dimension!");
      }
    
    /**
     * The copy assignment operator.
     * 
     * \param other The point this point will be replaced with.
     * \return Reference to this point.
     */
    Point& operator =(const Point& other) {
      memcpy(__data, other.__data, sizeof(T) * N);
      return *this;
    }
    
    /**
     * The move assignment operator.
     * 
     * \param other The other point.
     * \return Reference to this point.
     */
    Point& operator =(Point&& other) {
      std::move(std::begin(other.__data), std::end(other.__data), __data);
      return *this;
    }
    
    const unsigned dimension() const {
      return N;
    }
    
    const T& operator [](unsigned i) const {
      DeeAssert(i < N);
      return __data[i];
    }
    
    T& operator [](unsigned i) {
      DeeAssert(i < N);
      return __data[i];
    }
    
    /**
     * Gets the x coordinate.
     * 
     * Available only if N >= 1.
     * 
     * \return The _x_ coordinate of this point.
     */
    const T& x() const {
      static_assert(N >= 1, "This point does not have the x coordinate!");
      return __data[0];
    }
    
    /**
     * Gets the x coordinate.
     * 
     * Available only if N >= 1.
     * 
     * \return The _x_ coordinate of this point.
     */
    T& x() {
      static_assert(N >= 1, "This point does not have the x coordinate!");
      return __data[0];
    }
    
    /**
     * Gets the y coordinate.
     * 
     * Available only if N >= 2.
     * 
     * \return The _y_ coordinate of this point.
     */
    const T& y() const {
      static_assert(N >= 2, "This point does not have the y coordinate!");
      return __data[1];
    }
    
    /**
     * Gets the y coordinate.
     * 
     * Available only if N >= 2.
     * 
     * \return The _y_ coordinate of this point.
     */
    T& y() {
      static_assert(N >= 2, "This point does not have the y coordinate!");
      return __data[1];
    }
    
    /**
     * Gets the z coordinate.
     * 
     * Available only if N >= 3.
     * 
     * \return The _z_ coordinate of this point.
     */
    const T& z() const {
      static_assert(N >= 3, "This point does not have the z coordinate!");
      return __data[2];
    }
    
    /**
     * Gets the z coordinate.
     * 
     * Available only if N >= 3.
     * 
     * \return The _z_ coordinate of this point.
     */
    T& z() {
      static_assert(N >= 3, "This point does not have the z coordinate!");
      return __data[2];
    }
    
    /**
     * Moves the point by the given vector.
     * 
     * \param vector The vector.
     * \return Reference to this point.
     */
    Point& operator +=(const Vector<T, N>& vector) {
      for (unsigned i = 0; i < N; ++i)
        __data[i] += vector[i];
      return *this;
    }
    
    /**
     * Moves the point by the opposite vector.
     * 
     * \param vector The vector.
     * \return Reference to this point.
     */
    Point& operator -=(const Vector<T, N>& vector) {
      for (unsigned i = 0; i < N; ++i)
        __data[i] -= vector[i];
      return *this;
    }
    
  private:
    T __data[N];
    
  }; /** @} */

/**
 * \ingroup Core
 * 
 * 2-dimensional point.
 */
using Point2d = Point<float, 2>;

/**
 * \ingroup Core
 * 
 * 3-dimensional point.
 */
using Point3d = Point<float, 3>;

/**
 * \ingroup Core
 * 
 * 4-dimensional point.
 */
using Point4d = Point<float, 4>;

} /* namespace Dee */

#endif // POINT_H
