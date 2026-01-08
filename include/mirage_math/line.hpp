#pragma once

#include "point.hpp"
#include "vec.hpp"

namespace Mirage::Math {

class Line
{
  Point3 m_point;
  Vec3   m_line;

public:
  constexpr Line() = default;
  constexpr Line( const Point3& point, const Vec3& line ) : m_point( point ), m_line( line ) {}

  [[nodiscard]] constexpr const Vec3&   vector() const { return m_line; }
  [[nodiscard]] constexpr const Point3& point() const { return m_point; }
};

[[nodiscard]] inline float distance( const Point3& point, const Line& line )
{
  Vec3 cross_vec = cross( point - line.point(), line.vector() );
  return std::sqrt( dot( cross_vec, cross_vec ) / dot( line.vector(), line.vector() ) );
}

[[nodiscard]] inline float distance( const Line& line_a, const Line& line_b )
{
  Vec3 ab = line_b.point() - line_a.point();

  float v11 = dot( line_a.vector(), line_a.vector() );
  float v22 = dot( line_b.vector(), line_b.vector() );
  float v12 = dot( line_a.vector(), line_b.vector() );

  float det = ( v12 * v12 - v11 * v22 );
  if ( std::fabs( det ) > std::numeric_limits<float>::min() )
  {
    det = 1.0F / det;

    float dot_v1ab = dot( line_a.vector(), ab );
    float dot_v2ab = dot( line_b.vector(), ab );

    float t1 = ( v12 * dot_v2ab - v22 * dot_v1ab ) * det;
    float t2 = ( v11 * dot_v2ab - v12 * dot_v1ab ) * det;

    return magnitude( ( line_b.point() + t2 * line_b.vector() ) - ( line_a.point() + t1 * line_a.vector() ) );
  }

  // Lines are parallel, so just calculate the distance between line_a and point_b
  return distance( line_b.point(), line_a );
}

} // namespace Mirage::Math
