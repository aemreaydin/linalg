#pragma once

#include "mat4.hpp"
#include "point.hpp"

namespace linalg {

class Transform4 : public Mat4
{
public:
  constexpr Transform4() = default;

  constexpr Transform4( float t00,
    float                     t01,
    float                     t02,
    float                     t03,
    float                     t10,
    float                     t11,
    float                     t12,
    float                     t13,
    float                     t20,
    float                     t21,
    float                     t22,
    float                     t23 )
    : Mat4( t00, t01, t02, t03, t10, t11, t12, t13, t20, t21, t22, t23, 0.0F, 0.0F, 0.0F, 1.0F )
  {}

  constexpr Transform4( const Vec3& v00, const Vec3& v01, const Vec3& v02, const Point3& p03 )
    : Mat4( { v00, 0.0F }, { v01, 0.0F }, { v02, 0.0F }, { p03, 1.0F } )
  {}

  constexpr Transform4( const Mat4& mat ) : Mat4( mat ) {}

  [[nodiscard]] constexpr Vec3 getColumn3( size_t i ) const
  {
    const Vec4& vec4 = Mat4::operator[]( i );
    return vec4.toSubVec<3>();
  }

  [[nodiscard]] constexpr Vec3 operator[]( size_t i ) const { return getColumn3( i ); }

  [[nodiscard]] constexpr Point3 getTranslation() const
  {
    return Point3{ ( *this )( 0, 3 ), ( *this )( 1, 3 ), ( *this )( 2, 3 ) };
  }

  constexpr void setTranslation( const Point3& point )
  {
    ( *this )( 0, 3 ) = point.x();
    ( *this )( 1, 3 ) = point.y();
    ( *this )( 2, 3 ) = point.z();
  }
};

[[nodiscard]] constexpr Transform4 inverse( const Transform4& mat )
{
  const Vec3& a = mat[0];
  const Vec3& b = mat[1];
  const Vec3& c = mat[2];
  const Vec3& d = mat[3];

  Vec3 s = cross( a, b );
  Vec3 t = cross( c, d );

  const float inv_det = 1.0F / dot( s, c );
  s *= inv_det;
  t *= inv_det;

  const Vec3 v  = c * inv_det;
  const Vec3 r0 = cross( b, v );
  const Vec3 r1 = cross( v, a );

  return Transform4{
    r0.x(),
    r0.y(),
    r0.z(),
    -dot( b, t ),
    r1.x(),
    r1.y(),
    r1.z(),
    dot( a, t ),
    s.x(),
    s.y(),
    s.z(),
    -dot( d, s ),
  };
}

[[nodiscard]] constexpr Vec3 operator*( const Transform4& t, const Vec3& vec )
{
  return Vec3{
    t( 0, 0 ) * vec.x() + t( 0, 1 ) * vec.y() + t( 0, 2 ) * vec.z(),
    t( 1, 0 ) * vec.x() + t( 1, 1 ) * vec.y() + t( 1, 2 ) * vec.z(),
    t( 2, 0 ) * vec.x() + t( 2, 1 ) * vec.y() + t( 2, 2 ) * vec.z(),
  };
}

[[nodiscard]] constexpr Point3 operator*( const Transform4& t, const Point3& point )
{
  return Point3{
    t( 0, 0 ) * point.x() + t( 0, 1 ) * point.y() + t( 0, 2 ) * point.z() + t( 0, 3 ),
    t( 1, 0 ) * point.x() + t( 1, 1 ) * point.y() + t( 1, 2 ) * point.z() + t( 1, 3 ),
    t( 2, 0 ) * point.x() + t( 2, 1 ) * point.y() + t( 2, 2 ) * point.z() + t( 2, 3 ),
  };
}

[[nodiscard]] constexpr Vec3 transformNormal( const Vec3& normal, const Transform4& t )
{
  return Vec3{
    normal.x() * t( 0, 0 ) + normal.y() * t( 1, 0 ) + normal.z() * t( 2, 0 ),
    normal.x() * t( 0, 1 ) + normal.y() * t( 1, 1 ) + normal.z() * t( 2, 1 ),
    normal.x() * t( 0, 2 ) + normal.y() * t( 1, 2 ) + normal.z() * t( 2, 2 ),
  };
}

[[nodiscard]] constexpr Vec3 operator*( const Vec3& normal_vec, const Transform4& t )
{
  return transformNormal( normal_vec, t );
}

} // namespace linalg
