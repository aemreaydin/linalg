#pragma once

#include "vec.hpp"

namespace linalg {

class Point3 : public Vec3
{
public:
  constexpr Point3() = default;
  constexpr Point3( float x, float y, float z ) : Vec3( x, y, z ) {}
  constexpr Point3( const Vec3& vec ) : Vec3( vec ) {};
};

[[nodiscard]] constexpr Point3 operator+( const Point3& point, const Vec3& vec )
{
  return Point3{ point.x() + vec.x(), point.y() + vec.y(), point.z() + vec.z() };
}

[[nodiscard]] constexpr Point3 operator-( const Point3& point, const Vec3& vec )
{
  return Point3{ point.x() - vec.x(), point.y() - vec.y(), point.z() - vec.z() };
}

[[nodiscard]] constexpr Vec3 operator-( const Point3& a, const Point3& b )
{
  return Vec3{ a.x() - b.x(), a.y() - b.y(), a.z() - b.z() };
}

} // namespace linalg
