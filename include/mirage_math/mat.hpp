#pragma once

#include "vec.hpp"
#include <array>
#include <cassert>
#include <cstddef>

namespace Mirage::Math {

template<typename T, size_t Row, size_t Col, typename... Ts>
concept MatConstructorT = ( ... && IsSame<T, Ts> ) && ( ( sizeof...( Ts ) == Row * Col ) );

template<typename T, size_t Row, size_t Col, typename... Ts>
concept MatConstructorVec = ( ... && IsSame<Vec<T, Row>, Ts> ) && ( ( sizeof...( Ts ) == Row ) );

template<typename T, size_t Row, size_t Col>
  requires Arithmetic<T>
class Mat
{
  std::array<Vec<T, Col>, Row> m_data{};

public:
  Mat() = default;

  [[nodiscard]] static constexpr Mat identity()
    requires( Row == Col )
  {
    Mat result{};
    for ( size_t i = 0; i != Row; ++i )
    {
      result( i, i ) = 1.0F;
    }
    return result;
  }

  constexpr T& operator()( size_t i, size_t j )
  {
    assert( i < Row && j < Col );
    return m_data[j][i];
  }

  [[nodiscard]] constexpr const T& operator()( size_t i, size_t j ) const
  {
    assert( i < Row && j < Col );
    return m_data[j][i];
  }

  constexpr Vec<T, Col>& operator[]( const size_t i )
  {
    assert( i < Col );
    return m_data[i];
  }

  [[nodiscard]] constexpr const Vec<T, Col>& operator[]( size_t i ) const
  {
    assert( i < Col );
    return m_data[i];
  }

  constexpr Mat& operator+=( const Mat& other )
  {
    for ( size_t i = 0; i != Row; ++i )
    {
      for ( size_t j = 0; j != Col; ++j )
      {
        m_data[i][j] += other.m_data[i][j];
      }
    }
    return *this;
  }

  constexpr Mat& operator-=( const Mat& other )
  {
    for ( size_t i = 0; i != Row; ++i )
    {
      for ( size_t j = 0; j != Col; ++j )
      {
        m_data[i][j] -= other.m_data[i][j];
      }
    }
    return *this;
  }

  [[nodiscard]] constexpr Mat operator-() const
  {
    Mat result;
    for ( size_t i = 0; i != Row; ++i )
    {
      for ( size_t j = 0; j != Col; ++j )
      {
        result.m_data[i][j] = -m_data[i][j];
      }
    }
    return result;
  }

  template<typename U>
    requires IsSame<T, U>
  constexpr Mat& operator*=( U mul )
  {
    for ( size_t i = 0; i != Row; ++i )
    {
      for ( size_t j = 0; j != Col; ++j )
      {
        m_data[i][j] *= mul;
      }
    }
    return *this;
  }

  template<typename U>
    requires IsSame<T, U>
  constexpr Mat& operator/=( U div )
  {
    assert( div != 0.0F );
    for ( size_t i = 0; i != Row; ++i )
    {
      for ( size_t j = 0; j != Col; ++j )
      {
        m_data[i][j] /= div;
      }
    }
    return *this;
  }
};

template<typename T, size_t N>
[[nodiscard]] constexpr Mat<T, N, N> operator+( const Mat<T, N, N>& left, const Mat<T, N, N>& right )
{
  auto mat = left;
  mat += right;
  return mat;
}

template<typename T, size_t N>
[[nodiscard]] constexpr Mat<T, N, N> operator-( const Mat<T, N, N>& left, const Mat<T, N, N>& right )
{
  auto mat = left;
  mat -= right;
  return mat;
}

template<typename T, size_t N>
[[nodiscard]] constexpr Mat<T, N, N> operator*( const Mat<T, N, N>& left, const Mat<T, N, N>& right )
{
  Mat<T, N, N> mat{};
  for ( size_t i = 0; i != N; ++i )
  {
    for ( size_t j = 0; j != N; ++j )
    {
      for ( size_t k = 0; k != N; ++k )
      {
        mat( j, i ) += left( k, i ) * right( j, k );
      }
    }
  }
  return mat;
}

template<typename T, size_t N>
[[nodiscard]] constexpr Vec<T, N> operator*( const Mat<T, N, N>& mat, const Vec<T, N>& vec )
{
  Vec<T, N> result{};
  for ( size_t i = 0; i != N; ++i )
  {
    for ( size_t j = 0; j != N; ++j )
    {
      result[i] += mat( j, i ) * vec[j];
    }
  }
  return result;
}

template<typename T, size_t N>
[[nodiscard]] constexpr Mat<T, N, N> operator*( const Mat<T, N, N>& a, float mul )
{
  auto mat = a;
  mat *= mul;
  return mat;
}

template<typename T, size_t N>
[[nodiscard]] constexpr Mat<T, N, N> operator/( const Mat<T, N, N>& a, float div )
{
  auto mat = a;
  mat /= div;
  return mat;
}

template<typename T, size_t N>
[[nodiscard]] constexpr Mat<T, N, N> transpose( const Mat<T, N, N>& mat )
{
  Mat<T, N, N> result{};
  for ( size_t i = 0; i < N; ++i )
  {
    for ( size_t j = 0; j < N; ++j )
    {
      result( j, i ) = mat( i, j );
    }
  }
  return result;
}

} // namespace Mirage::Math
