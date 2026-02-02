#pragma once

#include "constants.hpp"
#include "vec.hpp"
#include <algorithm>
#include <cstddef>

namespace linalg {

[[nodiscard]] constexpr float radians( float deg ) { return deg * ( pi / 180.0F ); }

[[nodiscard]] constexpr float degrees( float rad ) { return rad * ( 180.0F / pi ); }

template<size_t N>
[[nodiscard]] constexpr Vec<float, N> radians( const Vec<float, N>& deg )
{
  Vec<float, N> result{};
  for ( size_t i = 0; i != N; ++i )
  {
    result[i] = radians( deg[i] );
  }
  return result;
}

template<size_t N>
[[nodiscard]] constexpr Vec<float, N> degrees( const Vec<float, N>& rad )
{
  Vec<float, N> result{};
  for ( size_t i = 0; i != N; ++i )
  {
    result[i] = degrees( rad[i] );
  }
  return result;
}

[[nodiscard]] constexpr float mix( float a, float b, float t ) { return a + t * ( b - a ); }

template<typename T, size_t N>
[[nodiscard]] constexpr Vec<T, N> mix( const Vec<T, N>& a, const Vec<T, N>& b, float t )
{
  Vec<T, N> result{};
  for ( size_t i = 0; i != N; ++i )
  {
    result[i] = a[i] + t * ( b[i] - a[i] );
  }
  return result;
}

template<typename T, size_t N>
[[nodiscard]] constexpr Vec<T, N> min( const Vec<T, N>& a, const Vec<T, N>& b )
{
  Vec<T, N> result{};
  for ( size_t i = 0; i != N; ++i )
  {
    result[i] = std::min( a[i], b[i] );
  }
  return result;
}

template<typename T, size_t N>
[[nodiscard]] constexpr Vec<T, N> max( const Vec<T, N>& a, const Vec<T, N>& b )
{
  Vec<T, N> result{};
  for ( size_t i = 0; i != N; ++i )
  {
    result[i] = std::max( a[i], b[i] );
  }
  return result;
}

} // namespace linalg
