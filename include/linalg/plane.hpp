#pragma once

#include "linalg/line.hpp"
#include "point.hpp"
#include "transform.hpp"
#include "vec.hpp"
#include <optional>

namespace linalg {

class Plane : public Vec4
{
public:
  using Vec4::Vec4;

  [[nodiscard]] constexpr Vec3 get_normal() const { return to_sub_vec<3>(); }

  void normalize_in_place()
  {
    float mag = magnitude( get_normal() );
    *this /= mag;
  }
};

[[nodiscard]] constexpr float dot( const Plane& plane, const Point3& point )
{
  return plane.x() * point.x() + plane.y() * point.y() + plane.z() * point.z() + plane.w();
}

[[nodiscard]] constexpr float dot( const Plane& plane, const Vec3& point )
{
  return plane.x() * point.x() + plane.y() * point.y() + plane.z() * point.z();
}

[[nodiscard]] constexpr Plane operator*( const Plane& plane, const Transform4& transform )
{
  return Plane{
    plane.x() * transform( 0, 0 ) + plane.y() * transform( 1, 0 ) + plane.z() * transform( 2, 0 ),
    plane.x() * transform( 0, 1 ) + plane.y() * transform( 1, 1 ) + plane.z() * transform( 2, 1 ),
    plane.x() * transform( 0, 2 ) + plane.y() * transform( 1, 2 ) + plane.z() * transform( 2, 2 ),
    plane.x() * transform( 0, 3 ) + plane.y() * transform( 1, 3 ) + plane.z() * transform( 2, 3 ) + plane.w(),
  };
}

[[nodiscard]] constexpr Transform4 make_reflection( const Plane& plane )
{
  float nx_sq = -2.0F * plane.x() * plane.x();
  float ny_sq = -2.0F * plane.y() * plane.y();
  float nz_sq = -2.0F * plane.z() * plane.z();
  float nx_ny = -2.0F * plane.x() * plane.y();
  float nx_nz = -2.0F * plane.x() * plane.z();
  float ny_nz = -2.0F * plane.y() * plane.z();
  float nx_d  = -2.0F * plane.x() * plane.w();
  float ny_d  = -2.0F * plane.y() * plane.w();
  float nz_d  = -2.0F * plane.z() * plane.w();

  return Transform4{
    1.0F + nx_sq,
    nx_ny,
    nx_nz,
    nx_d,
    nx_ny,
    1.0F + ny_sq,
    ny_nz,
    ny_d,
    nx_nz,
    ny_nz,
    1.0F + nz_sq,
    nz_d,
  };
}

[[nodiscard]] inline std::optional<Point3> get_intersection( const Plane& plane, const Line& line )
{
  float fp = dot( plane, line.point() );
  float fv = dot( plane, line.vector() );
  return std::fabs( fv ) > float_min ? std::optional{ line.point() - ( fp / fv ) * line.vector() } : std::nullopt;
}

[[nodiscard]] inline std::optional<Point3> get_intersection( const Plane& a, const Plane& b, const Plane& c )
{
  const Vec3& na = a.get_normal();
  const Vec3& nb = b.get_normal();
  const Vec3& nc = c.get_normal();

  Vec3  cross_na_nb           = cross( na, nb );
  float scalar_triple_product = dot( cross_na_nb, nc );

  return std::fabs( scalar_triple_product ) > float_min
           ? std::optional{ ( a.w() * cross( nc, nb ) + b.w() * cross( na, nc ) - c.w() * cross_na_nb )
                            / scalar_triple_product }
           : std::nullopt;
}

[[nodiscard]] inline std::optional<Line> get_intersection( const Plane& a, const Plane& b )
{
  const Vec3& na = a.get_normal();
  const Vec3& nb = b.get_normal();

  const Vec3& vec                   = cross( na, nb );
  float       scalar_triple_product = dot( vec, vec );
  if ( std::fabs( scalar_triple_product ) > float_min )
  {
    Point3 point{ ( a.w() * cross( vec, nb ) + b.w() * cross( na, vec ) ) / scalar_triple_product };
    return std::optional{
      Line{ point, vec }
    };
  }
  return std::nullopt;
}

} // namespace linalg
