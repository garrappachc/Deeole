/*
 * vector.h
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

#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <cmath>
#include <cstring>
#include <utility>
#include <type_traits>

#include "core/deeglobal.h"

#include "core/types.h"

namespace Dee {
  
  namespace {
    
    /*
     * Helpful template functions.
     */
    template <int ...S>
      struct __seq {};
    
    template <int I, int ...S>
      struct __gens : __gens<I-1, I-1, S...> {};
    
    template <int ...S>
      struct __gens<0, S...> {
        typedef __seq<S...> type;
      };
    
  }
 
/**
 * \ingroup Core
 * @{
 * 
 * Base class for all vectors of the same type.
 * 
 * \param T Type of elements stored in the vector.
 * \sa Point and Matrix
 */
template <typename T>
  class __DeeExport__ AbstractVector {
  
  public:
    
    /**
     * Dimension of the vector.
     * 
     * \return Dimension of the vector.
     */
    virtual const unsigned size() const = 0;
    
    /**
     * Gives access to the specific value of the vector.
     * 
     * \param i Number of the value; i < size().
     * \return Value on the i-th position.
     */
    virtual const T& operator [](unsigned i) const = 0;
    
    /**
     * Gives access to the specific value of the vector.
     * 
     * \param i Number of the value; i < size().
     * \return Value on the i-th position.
     */
    virtual T& operator [](unsigned i) = 0;
    
  }; /** @} */

/**
 * \ingroup Core
 * @{
 * 
 * The Vector class represents classic math vectors.
 * 
 * The Vector class is used to store classic math vectors. It is able to store
 * custom types as well as any dimension desired. The vector implementation
 * is very fast and efficient and it is optimized to be used by OpenGL.
 * 
 * \param T Type of elements stored in the vector.
 * \param N Dimension of the vector.
 * \sa Point and Matrix
 */
template <typename T, unsigned N>
  class __DeeExport__ Vector : public AbstractVector<T> {
    
    template <typename Operator, int ...S>
      Vector __unpackOperator(Operator o, const Vector& other, __seq<S...>) const {
        return Vector(o(__data[S], other.__data[S]) ...);
      }
    
    template <typename Operator, int ...S>
      Vector __unpackOperator(Operator o, const T& scalar, __seq<S...>) const {
        return Vector(o(__data[S], scalar) ...);
      }

  public:
    
    /**
     * Default constructor.
     * 
     * Sets all values to 0.
     * 
     * ~~~~{.cpp}
     * Vector<int, 2> v; // v = { 0, 0 }
     * ~~~~
     */
    Vector() {
      memset(__data, 0, N * sizeof(T));
    }
    
    /**
     * Copy constructor.
     * 
     * \param other Vector to be copied.
     */
    Vector(const Vector& other) {
      memcpy(__data, other.__data, N * sizeof(T));
    }
    
    /**
     * Move constructor.
     * 
     * Declared explicitly because of variadic template constructor.
     * 
     * \param other Vector to be moved.
     */
    Vector(Vector&& other) {
      std::move(std::begin(other.__data), std::end(other.__data), __data);
    }
    
    /**
     * Initializer-list constructor.
     * 
     * ~~~~{.cpp}
     * Vector<int, 3> v = { 1, 2, 3 };
     * ~~~~
     * 
     * \param values Values to have the vector initialized with.
     */
    Vector(std::initializer_list<T>&& values) {
      DeeAssert(values.size() == N);
      
      std::move(values.begin(), values.end(), __data);
    }
    
    /**
     * Constructs the Vector from the given array of values.
     * 
     * ~~~~{.cpp}
     * double[] vals = { 0.0, 0.1, 0.5 };
     * Vector<double, 3> v(vals);
     * ~~~~
     */
    Vector(const T* data) {
      memcpy(__data, data, N * sizeof(T));
    }
    
    /**
     * Variadic template constructor. Just for convenience.
     * 
     * ~~~~{.cpp}
     * Vector<int, 3> v(1, 2, 3);
     * ~~~~
     * 
     * \param values Values to have the vector initialized with.
     */
    template <typename... Args,
              typename = typename std::enable_if<
                Types::all_of_type<T, Args...>::value &&
                sizeof...(Args) == N
              >::type>
      explicit Vector(Args&&... values) :
          __data{ std::forward<Args>(values)... } {}
    
    /**
     * Copy assignment operator.
     * 
     * \param other The other vector to be copied into this vector.
     * \return Reference to this vector.
     */
    Vector& operator =(const Vector& other) {
      memcpy(__data, other.__data, N * sizeof(T));
      return *this;
    }
    
    /**
     * Move assignment operator.
     * 
     * \param other The other vector to be moved.
     * \return Reference to this vector.
     */
    Vector& operator =(Vector&& other) {
      std::move(std::begin(other.__data), std::end(other.__data), __data);
      return *this;
    }
    
    const unsigned size() const {
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
     * Available only if N >= 1.
     * 
     * \return The _x_ attribute of the vector.
     */
    const T& x() const {
      static_assert(N >= 1, "This vector does not have the x-attribute!");
      return __data[0];
    }
    
    /**
     * Available only if N >= 2.
     * 
     * \return The _y_ attribute of the vector.
     */
    const T& y() const {
      static_assert(N >= 2, "This vector does not have the y-attribute!");
      return __data[1];
    }
    
    /**
     * Available only if N >= 3.
     * 
     * \return The _z_ attribute of the vector.
     */
    const T& z() const {
      static_assert(N >= 3, "This vector does not have the z-attribute!");
      return __data[2];
    }
    
    /**
     * Counts length of the vector.
     * 
     * \return Length of the vector.
     * \sa normalize().
     */
    float length() const {
      float len = 0;
      
      for (const T& t: __data)
        len += (t * t);
      
      return sqrt(len);
    }
    
    /**
     * Normalizes the vector.
     * 
     * \sa length().
     */
    void normalize() {
      float len = length();
      
      if (len != 0) {
        for (T& t: __data)
          t /= len;
      }
    }
    
    /**
     * Compares the vector with _other_.
     * 
     * \return True if both vectors are the same.
     */
    bool operator ==(const Vector& other) const {
      return memcmp(__data, other.__data, N * sizeof(T)) == 0;
    }
    
    /**
     * Compares the vector with _other_.
     * 
     * \return False only if both vectors are the same.
     */
    bool operator !=(const Vector& other) const {
      return memcmp(__data, other.__data, N * sizeof(T)) != 0;
    }
    
    /**
     * Adds _other_ vector to this one.
     * 
     * \return Reference to this vector.
     */
    Vector& operator +=(const Vector& other) {
      for (unsigned i = 0; i < N; ++i)
        __data[i] += other[i];
      return *this;
    }
    
    /**
     * Subtracts _other_ from this vector.
     * 
     * \return Reference to this vector.
     */
    Vector& operator -=(const Vector& other) {
      for (unsigned i = 0; i < N; ++i) {
        __data[i] -= other[i];
      }
      return *this;
    }
    
    /**
     * Multiplies each value of this vector by _scalar_.
     * 
     * \return Reference to this vector.
     */
    Vector& operator *=(const T& scalar) {
      for (T& t: __data)
        t *= scalar;
      return *this;
    }
    
    /**
     * Dividies each value of this vector by _scalar_.
     * 
     * \return Reference to this vector.
     */
    Vector& operator /=(const T& scalar) {
      for (T& t: __data)
        t /= scalar;
      return *this;
    }
    
    /**
     * Creates the new vector, which is sum of the two vectors.
     * 
     * This function needs `operator +` defined for T.
     * 
     * \param other The second vector to be added to this one.
     * \return The new vector.
     */
    Vector operator +(const Vector& other) {
      return __unpackOperator(
        [](const T& a, const T& b) -> T {
          return a + b;
        }, other, typename __gens<N>::type());
    }
    
    /**
     * Creates the new vector that is the difference between this vector
     * and _other_ one.
     * 
     * This function needs `operator -` defined for T.
     * 
     * \param other The second vector that will be subtracted from this one.
     * \return The new vector.
     */
    Vector operator -(const Vector& other) {
      return __unpackOperator(
        [](const T& a, const T& b) -> T {
          return a - b;
        }, other, typename __gens<N>::type());
    }
    
    /**
     * Creates the new vector by multiplying this one by _scalar_.
     * 
     * This function needs `operator *` defined for T.
     * 
     * \param scalar The multiplying coefficient.
     * \return The new vector.
     */
    Vector operator *(const T& scalar) const {
      return __unpackOperator(
        [](const T& a, const T& b) -> T {
          return a * b;
        }, scalar, typename __gens<N>::type());
    }
    
    /**
     * Creates the new vector by dividing this one by _scalar_.
     * 
     * This function needs `operator /` defined for T.
     * 
     * \param scalar The divisor.
     * \return The new vector.
     */
    Vector operator /(const T& scalar) const {
      DeeAssert(scalar != 0);
      
      return __unpackOperator(
        [](const T& a, const T& b) -> T {
          return a / b;
        }, scalar, typename __gens<N>::type());
    }
    
    /**
     * Cross product.
     * 
     * Available only if _size_ == 3.
     * 
     * \param other The other vector.
     * \return A new vector that is the cross product between this vector
     *          and _other_.
     */
    Vector cross(const Vector<T, N>& other) const {
      static_assert(N == 3, "Cross product available only for 3-D vectors");
      
      return Vector<T, 3>(
        (__data[1] * other[2]) - (__data[2] * other[1]),
        (__data[2] * other[0]) - (__data[0] * other[2]),
        (__data[0] * other[1]) - (__data[1] * other[0])
      );
    }
    
  private:
    T __data[N];
    
  }; /** @} */

/**
 * \ingroup Core
 * 
 * 2-dimensional vector.
 */
using Vector2d = Vector<float, 2>;

/**
 * \ingroup Core
 * 
 * 3-dimensional vector.
 */
using Vector3d = Vector<float, 3>;

/**
 * \ingroup Core
 * 
 * 4-dimensional vector.
 */
using Vector4d = Vector<float, 4>;

/**
 * \ingroup Core
 * 
 * Calculates the dot product between the two 2-dimensional vectors.
 * 
 * \param a The first vector.
 * \param b The second vector.
 * \return The dot product between _a_ and _b_.
 * \related Vector
 */
inline float dotProduct(const Vector2d& a, const Vector2d& b) {
  return (a.x() * b.x()) + (a.y() * b.y());
}

/**
 * \ingroup Core
 * 
 * Calculates the dot product between the two 3-dimensional vectors.
 * 
 * \param a The first vector.
 * \param b The second vector.
 * \return The dot product between _a_ and _b_.
 * \related Vector
 */
inline float dotProduct(const Vector3d& a, const Vector3d& b) {
  return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
}

/**
 * \ingroup Core
 * 
 * Calculates the dot product between the two 4-dimensional vectors.
 * 
 * \param a The first vector.
 * \param b The second vector.
 * \return The dot product between _a_ and _b_.
 * \related Vector
 */
inline float dotProduct(const Vector4d& a, const Vector4d& b) {
  return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]) + (a[3] * b[3]);
}

} /* namespace Dee */

#endif // VECTOR_H
