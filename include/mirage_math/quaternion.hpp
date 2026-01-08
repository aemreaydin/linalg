#pragma once

#include "mat3.hpp"
#include "vec.hpp"

namespace Mirage::Math {

class Quaternion : public Vec4
{
public:
  using Vec4::Vec;

  [[nodiscard]] constexpr Vec3 getVector() const { return toSubVec<3>(); }
  [[nodiscard]] constexpr Mat3 getRotationMatrix()
  {
    float x2 = x() * x();
    float y2 = y() * y();
    float z2 = z() * z();
    float xy = x() * y();
    float xz = x() * z();
    float yz = y() * z();
    float wx = w() * x();
    float wy = w() * y();
    float wz = w() * z();

    return Mat3{ 1.0F - 2.0F * y2 - 2.0F * z2,
      2.0F * ( xy - wz ),
      2.0F * ( xz + wy ),
      2.0F * ( xy + wz ),
      1.0F - 2.0F * x2 - 2.0F * z2,
      2.0F * ( yz - wx ),
      2.0F * ( xz - wy ),
      2.0F * ( yz + wx ),
      1.0F - 2.0F * x2 - 2.0F * y2 };
  }

  void setRotationFromMatrix( const Mat3& rotation_mat )
  {
    float m00 = rotation_mat( 0, 0 );
    float m11 = rotation_mat( 1, 1 );
    float m22 = rotation_mat( 2, 2 );
    float sum = m00 + m11 + m22;

    if ( sum > 0.0F )
    {
      w()     = std::sqrt( sum + 1.0F ) * 0.5F;
      float f = 0.25F / w();

      x() = ( rotation_mat( 2, 1 ) - rotation_mat( 1, 2 ) ) * f;
      y() = ( rotation_mat( 0, 2 ) - rotation_mat( 2, 0 ) ) * f;
      z() = ( rotation_mat( 1, 0 ) - rotation_mat( 0, 1 ) ) * f;
    } else if ( ( m00 > m11 ) && ( m00 > m22 ) )
    {
      x()     = std::sqrt( m00 - m11 - m22 + 1.0F ) * 0.5F;
      float f = 0.25F / x();

      y() = ( rotation_mat( 1, 0 ) + rotation_mat( 0, 1 ) ) * f;
      z() = ( rotation_mat( 0, 2 ) + rotation_mat( 2, 0 ) ) * f;
      w() = ( rotation_mat( 2, 1 ) - rotation_mat( 1, 2 ) ) * f;
    } else if ( m11 > m22 )
    {
      y()     = std::sqrt( m11 - m00 - m22 + 1.0F ) * 0.5F;
      float f = 0.25F / y();

      x() = ( rotation_mat( 1, 0 ) + rotation_mat( 0, 1 ) ) * f;
      z() = ( rotation_mat( 2, 1 ) + rotation_mat( 1, 2 ) ) * f;
      w() = ( rotation_mat( 0, 2 ) - rotation_mat( 2, 0 ) ) * f;
    } else
    {
      z()     = std::sqrt( m22 - m00 - m11 + 1.0F ) * 0.5F;
      float f = 0.25F / z();

      x() = ( rotation_mat( 0, 2 ) + rotation_mat( 2, 0 ) ) * f;
      y() = ( rotation_mat( 2, 1 ) + rotation_mat( 1, 2 ) ) * f;
      w() = ( rotation_mat( 1, 0 ) - rotation_mat( 0, 1 ) ) * f;
    }
  }
};

[[nodiscard]] constexpr Quaternion operator*( const Quaternion& q00, const Quaternion& q01 )
{
  return Quaternion{
    q00.x() * q01.w() + q00.y() * q01.z() - q00.z() * q01.y() + q00.w() * q01.x(),
    q00.y() * q01.w() + q00.z() * q01.x() + q00.w() * q01.y() - q00.x() * q01.z(),
    q00.z() * q01.w() + q00.w() * q01.z() + q00.x() * q01.y() - q00.y() * q01.x(),
    q00.w() * q01.w() - q00.x() * q01.x() - q00.y() * q01.y() - q00.z() * q01.z(),
  };
}

[[nodiscard]] constexpr Vec3 transform( const Vec3& vec, const Quaternion& quat )
{
  const Vec3& b         = quat.getVector();
  const float c         = quat.w();
  const float b_squared = magnitudeSquared( b );

  return ( c * c - b_squared ) * vec + 2.0F * dot( vec, b ) * b + 2.0F * c * cross( b, vec );
}

using Quat = Quaternion;

} // namespace Mirage::Math
