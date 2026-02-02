#pragma once

#include "mat4.hpp"
#include <cassert>
#include <cmath>

namespace linalg {

[[nodiscard]] inline Mat4 look_at( const Vec3& eye, const Vec3& center, const Vec3& up )
{
  const Vec3 f = normalized( center - eye );
  const Vec3 s = normalized( cross( f, up ) );
  const Vec3 u = cross( s, f );

  return Mat4{
    s.x(),
    s.y(),
    s.z(),
    -dot( s, eye ),
    u.x(),
    u.y(),
    u.z(),
    -dot( u, eye ),
    -f.x(),
    -f.y(),
    -f.z(),
    dot( f, eye ),
    0.0F,
    0.0F,
    0.0F,
    1.0F,
  };
}

[[nodiscard]] inline Mat4 perspective( float fovy, float aspect, float near_p, float far_p )
{
  assert( std::abs( aspect ) > epsilon );
  assert( far_p > near_p );

  const float tan_half_fov = std::tan( fovy / 2.0F );

  Mat4 result{};
  result( 0, 0 ) = 1.0F / ( aspect * tan_half_fov );
  result( 1, 1 ) = 1.0F / tan_half_fov;
  result( 2, 2 ) = far_p / ( near_p - far_p );
  result( 2, 3 ) = -( far_p * near_p ) / ( far_p - near_p );
  result( 3, 2 ) = -1.0F;

  return result;
}

[[nodiscard]] inline Mat4 ortho( float left, float right, float bottom, float top, float near_p, float far_p )
{
  Mat4 result{};
  result( 0, 0 ) = 2.0F / ( right - left );
  result( 1, 1 ) = 2.0F / ( top - bottom );
  result( 2, 2 ) = -1.0F / ( far_p - near_p );
  result( 0, 3 ) = -( right + left ) / ( right - left );
  result( 1, 3 ) = -( top + bottom ) / ( top - bottom );
  result( 2, 3 ) = -near_p / ( far_p - near_p );
  result( 3, 3 ) = 1.0F;

  return result;
}

} // namespace linalg
