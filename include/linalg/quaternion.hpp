#pragma once

#include "mat3.hpp"
#include "mat4.hpp"
#include "vec.hpp"

namespace linalg {

class Quaternion : public Vec4
{
public:
  using Vec4::Vec;

  [[nodiscard]] constexpr Vec3 get_vector() const { return to_sub_vec<3>(); }

  [[nodiscard]] constexpr Mat3 get_rotation_matrix()
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

  [[nodiscard]] constexpr Mat4 to_mat4()
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

    return Mat4{ 1.0F - 2.0F * y2 - 2.0F * z2,
      2.0F * ( xy - wz ),
      2.0F * ( xz + wy ),
      0.0F,
      2.0F * ( xy + wz ),
      1.0F - 2.0F * x2 - 2.0F * z2,
      2.0F * ( yz - wx ),
      0.0F,
      2.0F * ( xz - wy ),
      2.0F * ( yz + wx ),
      1.0F - 2.0F * x2 - 2.0F * y2,
      0.0F,
      0.0F,
      0.0F,
      0.0F,
      1.0F };
  }

  void set_rotation_from_matrix( const Mat3& rotation_mat )
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

  void set_rotation_from_mat4( const Mat4& m )
  {
    Mat3 rot{ m( 0, 0 ), m( 0, 1 ), m( 0, 2 ), m( 1, 0 ), m( 1, 1 ), m( 1, 2 ), m( 2, 0 ), m( 2, 1 ), m( 2, 2 ) };
    set_rotation_from_matrix( rot );
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
  const Vec3& b         = quat.get_vector();
  const float c         = quat.w();
  const float b_squared = magnitude_squared( b );

  return ( c * c - b_squared ) * vec + 2.0F * dot( vec, b ) * b + 2.0F * c * cross( b, vec );
}

[[nodiscard]] inline Vec3 euler_angles( const Quaternion& q )
{
  float sinr_cosp = 2.0F * ( q.w() * q.x() + q.y() * q.z() );
  float cosr_cosp = 1.0F - 2.0F * ( q.x() * q.x() + q.y() * q.y() );
  float pitch     = std::atan2( sinr_cosp, cosr_cosp );

  float sinp = 2.0F * ( q.w() * q.y() - q.z() * q.x() );
  float yaw;
  if ( std::abs( sinp ) >= 1.0F )
  {
    yaw = std::copysign( pi / 2.0F, sinp );
  } else
  {
    yaw = std::asin( sinp );
  }

  float siny_cosp = 2.0F * ( q.w() * q.z() + q.x() * q.y() );
  float cosy_cosp = 1.0F - 2.0F * ( q.y() * q.y() + q.z() * q.z() );
  float roll      = std::atan2( siny_cosp, cosy_cosp );

  return Vec3{ pitch, yaw, roll };
}

[[nodiscard]] inline Quaternion quat_from_euler( const Vec3& euler )
{
  float cx = std::cos( euler.x() * 0.5F );
  float sx = std::sin( euler.x() * 0.5F );
  float cy = std::cos( euler.y() * 0.5F );
  float sy = std::sin( euler.y() * 0.5F );
  float cz = std::cos( euler.z() * 0.5F );
  float sz = std::sin( euler.z() * 0.5F );

  return Quaternion{
    sx * cy * cz - cx * sy * sz,
    cx * sy * cz + sx * cy * sz,
    cx * cy * sz - sx * sy * cz,
    cx * cy * cz + sx * sy * sz,
  };
}

[[nodiscard]] inline Quaternion slerp( const Quaternion& a, const Quaternion& b, float t )
{
  float cos_theta = dot( static_cast<const Vec4&>( a ), static_cast<const Vec4&>( b ) );

  Quaternion b_adj = b;
  if ( cos_theta < 0.0F )
  {
    cos_theta = -cos_theta;
    b_adj     = Quaternion{ -b.x(), -b.y(), -b.z(), -b.w() };
  }

  if ( cos_theta > 1.0F - epsilon )
  {
    return Quaternion{
      a.x() + t * ( b_adj.x() - a.x() ),
      a.y() + t * ( b_adj.y() - a.y() ),
      a.z() + t * ( b_adj.z() - a.z() ),
      a.w() + t * ( b_adj.w() - a.w() ),
    };
  }

  float theta     = std::acos( cos_theta );
  float sin_theta = std::sin( theta );
  float wa        = std::sin( ( 1.0F - t ) * theta ) / sin_theta;
  float wb        = std::sin( t * theta ) / sin_theta;

  return Quaternion{
    wa * a.x() + wb * b_adj.x(),
    wa * a.y() + wb * b_adj.y(),
    wa * a.z() + wb * b_adj.z(),
    wa * a.w() + wb * b_adj.w(),
  };
}

using Quat = Quaternion;

} // namespace linalg
