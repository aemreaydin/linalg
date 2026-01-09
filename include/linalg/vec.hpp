#pragma once

#include "constants.hpp"
#include <array>
#include <cassert>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <format>
#include <string>
#include <type_traits>
#include <utility>

namespace linalg {

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<typename T, size_t N, typename... Ts>
concept VecParams = ( ... && std::same_as<T, Ts> ) && ( ( sizeof...( Ts ) == N ) );

template<typename T, size_t N>
  requires Arithmetic<T>
class Vec
{
public:
  using SizeType      = std::size_t;
  using Iterator      = typename std::array<T, N>::iterator;
  using ConstIterator = typename std::array<T, N>::const_iterator;

private:
  std::array<T, N> m_data{};

  template<size_t SubN, size_t... Is>
  constexpr explicit Vec( const Vec<T, SubN>& other, T val, std::index_sequence<Is...> /*unused*/ )
    : m_data{ other[Is]..., val }
  {}

public:
  Vec() = default;

  template<typename... Args>
    requires VecParams<T, N, Args...>
  constexpr explicit Vec( Args... args ) : m_data{ args... }
  {}

  template<size_t SubN, typename U>
    requires( std::same_as<T, U> && ( SubN + 1 == N ) )
  constexpr Vec( const Vec<T, SubN>& vec, U value ) : Vec( vec, value, std::make_index_sequence<SubN>{} )
  {}

  // Iterator support
  constexpr Iterator      begin() { return m_data.begin(); }
  constexpr ConstIterator begin() const { return m_data.begin(); }
  constexpr ConstIterator cbegin() const { return m_data.cbegin(); }
  constexpr Iterator      end() { return m_data.end(); }
  constexpr ConstIterator end() const { return m_data.end(); }
  constexpr ConstIterator cend() const { return m_data.cend(); }

  [[nodiscard]] constexpr SizeType size() const { return N; }
  [[nodiscard]] constexpr SizeType maxSize() const { return N; }
  [[nodiscard]] constexpr bool     empty() const { return N == 0; }

  constexpr T& operator[]( size_t i )
  {
    assert( i < N );
    return m_data[i];
  }
  constexpr const T& operator[]( size_t i ) const
  {
    assert( i < N );
    return m_data[i];
  }

  constexpr T& x() { return m_data[0]; }
  constexpr T& y() { return m_data[1]; }
  constexpr T& z()
    requires( N >= 3 )
  {
    return m_data[2];
  }
  constexpr T& w()
    requires( N >= 4 )
  {
    return m_data[3];
  }

  [[nodiscard]] constexpr const T& x() const { return m_data[0]; }
  [[nodiscard]] constexpr const T& y() const { return m_data[1]; }
  [[nodiscard]] constexpr const T& z() const
    requires( N >= 3 )
  {
    return m_data[2];
  }
  [[nodiscard]] constexpr const T& w() const
    requires( N >= 4 )
  {
    return m_data[3];
  }

  template<typename U>
  constexpr Vec& operator+=( U val )
    requires std::same_as<T, U>
  {
    for ( auto& data : m_data )
    {
      data += val;
    }
    return *this;
  }

  template<typename U>
  constexpr Vec& operator-=( U val )
    requires std::same_as<T, U>
  {
    for ( auto& data : m_data )
    {
      data -= val;
    }
    return *this;
  }

  template<typename U>
  constexpr Vec& operator*=( U val )
    requires std::same_as<T, U>
  {
    for ( auto& data : m_data )
    {
      data *= val;
    }
    return *this;
  }

  template<typename U>
  constexpr Vec& operator/=( U val )
    requires std::same_as<T, U>
  {
    assert( val != 0.0F );
    for ( auto& data : m_data )
    {
      data /= val;
    }
    return *this;
  }

  template<size_t U>
  [[nodiscard]] constexpr Vec<T, U> toSubVec() const
    requires( U <= N )
  {
    Vec<T, U> result{};
    for ( size_t i = 0; i < U; ++i )
    {
      result[i] = m_data[i];
    }
    return result;
  }

  template<size_t U>
  constexpr void setSubVec( const Vec<T, U>& sub )
    requires( U <= N )
  {
    for ( size_t i = 0; i < U; ++i )
    {
      m_data[i] = sub[i];
    }
  }

  void normalizeInPlace() { *this /= magnitude( *this ); }

  explicit operator std::string() const
  {
    std::string result = "Vec" + std::to_string( N ) + "(";
    for ( size_t i = 0; i < N; i++ )
    {
      if constexpr ( std::floating_point<T> )
      {
        result += std::format( "{:.1f}", m_data[i] );
      } else
      {
        result += std::format( "{}", m_data[i] );
      }
      if ( i < N - 1 )
      {
        result += ", ";
      }
    }
    result += ")";
    return result;
  }
};

// Deduction Guide
template<typename T, typename... Ts>
Vec( T, Ts... ) -> Vec<T, 1 + sizeof...( Ts )>;

template<typename T, size_t N>
[[nodiscard]] constexpr Vec<T, N> operator+( const Vec<T, N>& left, const Vec<T, N>& right )
{
  Vec<T, N> vec{};
  for ( size_t i = 0; i != N; ++i )
  {
    vec[i] = left[i] + right[i];
  }
  return vec;
}

template<typename T, size_t N>
[[nodiscard]] constexpr Vec<T, N> operator-( const Vec<T, N>& left, const Vec<T, N>& right )
{
  Vec<T, N> vec{};
  for ( size_t i = 0; i != N; ++i )
  {
    vec[i] = left[i] - right[i];
  }
  return vec;
}

template<typename T, size_t N>
[[nodiscard]] constexpr Vec<T, N> operator-( const Vec<T, N>& left )
{
  Vec<T, N> vec{};
  for ( size_t i = 0; i != N; ++i )
  {
    vec[i] = -left[i];
  }
  return vec;
}

template<typename T, size_t N>
[[nodiscard]] constexpr Vec<T, N> operator*( const Vec<T, N>& vec, T mul )
{
  Vec<T, N> result{};
  for ( size_t i = 0; i != N; ++i )
  {
    result[i] = vec[i] * mul;
  }
  return result;
}

template<typename T, size_t N>
[[nodiscard]] constexpr Vec<T, N> operator*( T mul, const Vec<T, N>& vec )
{
  return vec * mul;
}

template<typename T, size_t N>
[[nodiscard]] constexpr Vec<T, N> operator/( const Vec<T, N>& left, T div )
{
  assert( div != 0.0F );
  Vec<T, N> vec{};
  for ( size_t i = 0; i != N; ++i )
  {
    vec[i] = left[i] / div;
  }
  return vec;
}

template<typename T, size_t N>
[[nodiscard]] constexpr T magnitudeSquared( const Vec<T, N>& vec )
{
  T result{};
  for ( size_t i = 0; i != N; ++i )
  {
    result += vec[i] * vec[i];
  }
  return result;
}

template<typename T, size_t N>
[[nodiscard]] inline T magnitude( const Vec<T, N>& vec )
{
  return std::sqrt( magnitudeSquared( vec ) );
}

template<typename T, size_t N>
[[nodiscard]] inline Vec<T, N> normalized( const Vec<T, N>& vec )
{
  return vec / magnitude( vec );
}

template<typename T, size_t N>
[[nodiscard]] constexpr T dot( const Vec<T, N>& left, const Vec<T, N>& right )
{
  T result{};
  for ( size_t i = 0; i != N; ++i )
  {
    result += left[i] * right[i];
  }
  return result;
}

template<typename T, size_t N>
[[nodiscard]] constexpr Vec<T, N> cross( const Vec<T, N>& left, const Vec<T, N>& right )
  requires( N == 3 )
{
  return Vec<T, N>{ left[1] * right[2] - left[2] * right[1],
    left[2] * right[0] - left[0] * right[2],
    left[0] * right[1] - left[1] * right[0] };
}

template<typename T, size_t N>
[[nodiscard]] constexpr Vec<T, N> project( const Vec<T, N>& source, const Vec<T, N>& target )
{
  return target * ( dot( source, target ) ) / dot( target, target );
}

template<typename T, size_t N>
[[nodiscard]] constexpr Vec<T, N> reject( const Vec<T, N>& source, const Vec<T, N>& target )
{
  return source - project( source, target );
}

template<typename T, size_t N>
[[nodiscard]] inline bool isUnitVector( const Vec<T, N>& vec, const T epsilon = EPSILON )
{
  return std::abs( dot( vec, vec ) - UNIT ) < epsilon;
}

using Vec2  = Vec<float, 2>;
using Vec3  = Vec<float, 3>;
using Vec4  = Vec<float, 4>;
using IVec3 = Vec<int, 3>;
using IVec4 = Vec<int, 4>;

} // namespace linalg
