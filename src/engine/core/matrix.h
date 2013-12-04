/*
 * matrix.h
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

#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <utility>
#include <cstring>

#include "core/deeglobal.h"

namespace Dee {
  
  template <typename T, int N> class Matrix;
  
namespace {
  template <typename T, int N> T determinant(const Matrix<T, N>&);
}

/**
 * \ingroup Core
 * @{
 * 
 * The Matrix class handles classic square matrix.
 */
template <typename T, int N>
  class __DeeExport__ Matrix {
    
  public:
    
    Matrix() {
      loadIdentity();
    }
    
    Matrix(const Matrix& other) {
      memcpy(__data, other.data, size() * sizeof(T));
    }
    
    Matrix(Matrix&& other) {
      std::move(std::begin(other.__data), std::end(other.__data), __data);
    }
    
    Matrix& operator =(const Matrix& other) {
      memcpy(__data, other.__data, size() * sizeof(T));
      return *this;
    }
    
    constexpr int dimension() {
      return N;
    }
    
    constexpr int size() {
      return N * N;
    }
    
    operator T*() {
      return __data;
    }
    
    operator const T*() const {
      return __data;
    }
    
    T& operator [](int n) {
      DeeAssert(n < size());
      return __data[n];
    }
    
    const T& operator [](int n) const {
      DeeAssert(n < size());
      return __data[n];
    }
    
    /**
     * Unline in matrices in maths in general - we count from 0.
     * 
     * \param i Row.
     * \param j Column.
     */
    T& at(int i, int j) {
      DeeAssert((j < N) && (i < N));
      return __data[j * N + i];
    }
    
    const T& at(int i, int j) const {
      DeeAssert((j < N) && (i < N));
      return __data[j * N + i];
    }
    
    T determinant() const {
      return determinant(*this);
    }
    
    void loadIdentity() {
      memset(__data, 0, size() * sizeof(T));
      for (int i = 0; i < N; ++i)
        at(i, i) = static_cast<T>(1);
    }
    
    void fillWithZeores() {
      memset(__data, 0, size() * sizeof(T));
    }
    
#if defined minor
# undef minor
#endif
    Matrix<T, N - 1> minor(int i, int j) const {
      Matrix< T, N - 1 > result;
      int idx = 0;
      
      for (int k = 0; k < N; ++k) {
        if (k == j)
          continue;
        for (int l = 0; l < N; ++l) {
          if (l == i)
            continue;
          result[idx++] = at(k, l);
        }
      }
      
      return std::move(result);
    }
    
    Matrix<T, N> inverted() const {
      Matrix<T, N> result;
      double det = static_cast<T>(1.0) / determinant();
      for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
          Matrix<T, N - 1> mMinor = minor(j, i);
          result.at(i, j) = det * mMinor.determinant();
          if ((i + j) % 2 == 1)
            result.at(i, j) = -result.at(i, j);
          }
        }
        
      return std::move(result);
    }
    
    Matrix<T, N> operator *(const Matrix<T, N>& other) const {
      Matrix<T, N> result;
      result.fillWithZeores();
      
      /**
       * TODO: Make this faster, i.e. by pararellizing the computation on
       *        several threads.
       */
      
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          for (int n = 0; n < N; ++n) {
            result.at(i, j) += this->at(i, n) * other.at(n, j);
          }
        }
      }
      
      return std::move(result);
    }
    
    Matrix<T, N>& operator *=(const Matrix<T, N>& other) {
      *this = *this * other;
      return *this;
    }
    
  private:
    T __data[N * N];
    
  }; /** @} */

using Matrix2d = Matrix<float, 2>;
using Matrix3d = Matrix<float, 3>;
using Matrix4d = Matrix<float, 4>;

namespace {
  template <typename T, int N>
    T determinant(const Matrix<T, N>& matrix) {
      T det = static_cast<T>(0);
      int i = 0;
      for (int j = 0; j < N; ++j) {
        if ((i + j) % 2 == 0) 
          det += matrix.at(i, j) * matrix.minor(i, j).determinant();
        else
          det -= matrix.at(i, j) * matrix.minor(i, j).determinant();
      }
      
      return det;
    }

  template <typename T, int N>
    T determinant(const Matrix<T, 1>& matrix) {
      return matrix[0];
    }
  
  template <typename T, int N>
    T determinant(const Matrix<T, 2>& matrix) {
      return (matrix[0] * matrix[3]) - (matrix[2] * matrix[1]);
    }
  
  template <typename T, int N>
    T determinant(const Matrix<T, 3>& matrix) {
      return ((matrix[0] * matrix[4] * matrix[8]) + (matrix[3] * matrix[7] * matrix[2]) + (matrix[6] * matrix[1] * matrix[5]))
           - ((matrix[6] * matrix[4] * matrix[2]) + (matrix[3] * matrix[1] * matrix[8]) + (matrix[0] * matrix[7] * matrix[5]));
    }

} /* namespace */

} /* namespace Dee */

#endif // MATRIX_H
