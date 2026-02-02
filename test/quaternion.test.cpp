#include "linalg/quaternion.hpp"
#include "linalg/constants.hpp"
#include "test_utils.hpp"
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

using namespace linalg;

class QuaternionTest : public ::testing::Test
{
protected:
  void SetUp() override {}
};

TEST_F( QuaternionTest, Constructor )
{
  Quat quat{ 1.0F, 2.0F, 3.0F, 4.0F };
  Quat quat_from_vec{
    Vec3{ 5.0F, 6.0F, 7.0F },
    8.0F
  };

  EXPECT_FLOAT_EQ( quat.x(), 1.0F );
  EXPECT_FLOAT_EQ( quat.y(), 2.0F );
  EXPECT_FLOAT_EQ( quat.z(), 3.0F );
  EXPECT_FLOAT_EQ( quat.w(), 4.0F );

  EXPECT_FLOAT_EQ( quat_from_vec.x(), 5.0F );
  EXPECT_FLOAT_EQ( quat_from_vec.y(), 6.0F );
  EXPECT_FLOAT_EQ( quat_from_vec.z(), 7.0F );
  EXPECT_FLOAT_EQ( quat_from_vec.w(), 8.0F );
}

TEST_F( QuaternionTest, ConstructFromVec4 )
{
  Vec4 v{ 1.0F, 2.0F, 3.0F, 4.0F };
  Quat q( v );
  EXPECT_FLOAT_EQ( q.x(), 1.0F );
  EXPECT_FLOAT_EQ( q.y(), 2.0F );
  EXPECT_FLOAT_EQ( q.z(), 3.0F );
  EXPECT_FLOAT_EQ( q.w(), 4.0F );
}

TEST_F( QuaternionTest, ConstructFromNormalizedVec4 )
{
  Quat original{ 0.0F, 0.0F, one_over_sqrt_two, one_over_sqrt_two };
  Vec4 as_vec4 = normalized( static_cast<const Vec4&>( original ) );
  Quat recovered( as_vec4 );
  EXPECT_NEAR( recovered.x(), original.x(), 1e-5F );
  EXPECT_NEAR( recovered.y(), original.y(), 1e-5F );
  EXPECT_NEAR( recovered.z(), original.z(), 1e-5F );
  EXPECT_NEAR( recovered.w(), original.w(), 1e-5F );
}

TEST_F( QuaternionTest, NoRotation )
{
  Vec3 v{ 1.0F, 0.0F, 0.0F };
  Quat q{ 1.0F, 0.0F, 0.0F, 0.0F };
  Vec3 transformed = transform( v, q );
  are_vectors_equal( v, transformed );
}

TEST_F( QuaternionTest, NinetyDegreeRotationAroundZ )
{
  Vec3  v{ 1.0F, 0.0F, 0.0F };
  float sqrt2_2 = 1.0F / std::numbers::sqrt2_v<float>;
  Quat  q{ 0.0F, 0.0F, sqrt2_2, sqrt2_2 };
  Vec3  transformed = transform( v, q );
  Vec3  expected{ 0.0F, 1.0F, 0.0F };
  are_vectors_equal( transformed, expected );
}

TEST_F( QuaternionTest, OneEightyDegreeRotationAroundY )
{
  Vec3 v{ 1.0F, 0.0F, 0.0F };
  Quat q{ 0.0F, 0.0F, 1.0F, 0.0F };
  Vec3 transformed = transform( v, q );
  Vec3 expected{ -1.0F, 0.0F, 0.0F };
  are_vectors_equal( transformed, expected );
}

TEST_F( QuaternionTest, TwoRotations )
{
  Vec3 v{ 1.0F, 0.0F, 0.0F };
  Quat q_z{ 0.0F, 0.0F, one_over_sqrt_two, one_over_sqrt_two };
  Quat q_x{ one_over_sqrt_two, 0.0F, 0.0F, one_over_sqrt_two };
  Vec3 transformed = transform( v, q_z );
  transformed      = transform( v, q_x );
  Vec3 expected( 0.0F, 0.0F, 1.0F );
  are_vectors_equal( transformed, expected );

  float deg_45 = pi / 4;
  float sin    = std::sin( deg_45 / 2.0F );
  float cos    = std::cos( deg_45 / 2.0F );

  Vec3 v_x{ 1.0F, 0.0F, 0.0F };
  Quat q_z45{ 0.0F, 0.0F, sin, cos };
  Quat q_y45{ 0.0F, sin, 0.0F, cos };

  transformed = transform( v_x, q_z45 );
  expected    = Vec3{ one_over_sqrt_two, one_over_sqrt_two, 0.0F };
  are_vectors_equal( transformed, expected );
  transformed = transform( v_x, q_y45 );
  expected    = Vec3{ one_over_sqrt_two, one_over_sqrt_two, one_over_sqrt_two };
  are_vectors_equal( transformed, expected );
}

TEST_F( QuaternionTest, SetRotationFromMatrix )
{
  Mat3 identity = Mat3::identity();
  Quat quat{};
  quat.set_rotation_from_matrix( identity );
  EXPECT_FLOAT_EQ( quat.w(), 1.0F );
  EXPECT_FLOAT_EQ( quat.x(), 0.0F );
  EXPECT_FLOAT_EQ( quat.y(), 0.0F );
  EXPECT_FLOAT_EQ( quat.z(), 0.0F );
}

TEST_F( QuaternionTest, NinetyDegreeZ )
{
  float angle    = pi / 2;
  Mat3  rotation = make_rotation_z( angle );
  Quat  quat{};
  quat.set_rotation_from_matrix( rotation );
  EXPECT_FLOAT_EQ( quat.w(), one_over_sqrt_two );
  EXPECT_FLOAT_EQ( quat.x(), 0.0F );
  EXPECT_FLOAT_EQ( quat.y(), 0.0F );
  EXPECT_FLOAT_EQ( quat.z(), one_over_sqrt_two );
}

#include "linalg/mat4.hpp"

TEST_F( QuaternionTest, ToMat4Identity )
{
  Quat q{ 0.0F, 0.0F, 0.0F, 1.0F };
  Mat4 m = q.to_mat4();

  EXPECT_TRUE( are_matrices_equal( m, Mat4::identity(), 1e-5F ) );
}

TEST_F( QuaternionTest, ToMat4RotationZ90 )
{
  Quat q{ 0.0F, 0.0F, one_over_sqrt_two, one_over_sqrt_two };
  Mat4 m = q.to_mat4();

  Vec4 v      = m * Vec4{ 1.0F, 0.0F, 0.0F, 1.0F };
  Vec3 result = v.to_sub_vec<3>();
  EXPECT_NEAR( result.x(), 0.0F, 1e-5F );
  EXPECT_NEAR( result.y(), 1.0F, 1e-5F );
  EXPECT_NEAR( result.z(), 0.0F, 1e-5F );
}

TEST_F( QuaternionTest, ToMat4BottomRow )
{
  Quat q{ 0.0F, 0.0F, one_over_sqrt_two, one_over_sqrt_two };
  Mat4 m = q.to_mat4();

  EXPECT_FLOAT_EQ( m( 3, 0 ), 0.0F );
  EXPECT_FLOAT_EQ( m( 3, 1 ), 0.0F );
  EXPECT_FLOAT_EQ( m( 3, 2 ), 0.0F );
  EXPECT_FLOAT_EQ( m( 3, 3 ), 1.0F );
  EXPECT_FLOAT_EQ( m( 0, 3 ), 0.0F );
  EXPECT_FLOAT_EQ( m( 1, 3 ), 0.0F );
  EXPECT_FLOAT_EQ( m( 2, 3 ), 0.0F );
}

TEST_F( QuaternionTest, SetRotationFromMat4 )
{
  Quat original{ 0.0F, 0.0F, one_over_sqrt_two, one_over_sqrt_two };
  Mat4 m = original.to_mat4();

  Quat recovered{};
  recovered.set_rotation_from_mat4( m );

  EXPECT_NEAR( std::abs( recovered.x() ), std::abs( original.x() ), 1e-5F );
  EXPECT_NEAR( std::abs( recovered.y() ), std::abs( original.y() ), 1e-5F );
  EXPECT_NEAR( std::abs( recovered.z() ), std::abs( original.z() ), 1e-5F );
  EXPECT_NEAR( std::abs( recovered.w() ), std::abs( original.w() ), 1e-5F );
}

TEST_F( QuaternionTest, EulerAnglesIdentity )
{
  Quat q{ 0.0F, 0.0F, 0.0F, 1.0F };
  Vec3 e = euler_angles( q );
  EXPECT_NEAR( e.x(), 0.0F, 1e-5F );
  EXPECT_NEAR( e.y(), 0.0F, 1e-5F );
  EXPECT_NEAR( e.z(), 0.0F, 1e-5F );
}

TEST_F( QuaternionTest, EulerAnglesRoundtrip )
{
  Vec3 original_euler{ 0.1F, 0.2F, 0.3F };
  Quat q         = quat_from_euler( original_euler );
  Vec3 recovered = euler_angles( q );
  EXPECT_NEAR( recovered.x(), original_euler.x(), 1e-5F );
  EXPECT_NEAR( recovered.y(), original_euler.y(), 1e-5F );
  EXPECT_NEAR( recovered.z(), original_euler.z(), 1e-5F );
}

TEST_F( QuaternionTest, QuatFromEulerIdentity )
{
  Quat q = quat_from_euler( Vec3{ 0.0F, 0.0F, 0.0F } );
  EXPECT_NEAR( q.x(), 0.0F, 1e-5F );
  EXPECT_NEAR( q.y(), 0.0F, 1e-5F );
  EXPECT_NEAR( q.z(), 0.0F, 1e-5F );
  EXPECT_NEAR( q.w(), 1.0F, 1e-5F );
}

TEST_F( QuaternionTest, SlerpIdentity )
{
  Quat a{ 0.0F, 0.0F, 0.0F, 1.0F };
  Quat b{ 0.0F, 0.0F, one_over_sqrt_two, one_over_sqrt_two };

  Quat r0 = slerp( a, b, 0.0F );
  EXPECT_NEAR( r0.x(), a.x(), 1e-5F );
  EXPECT_NEAR( r0.y(), a.y(), 1e-5F );
  EXPECT_NEAR( r0.z(), a.z(), 1e-5F );
  EXPECT_NEAR( r0.w(), a.w(), 1e-5F );

  Quat r1 = slerp( a, b, 1.0F );
  EXPECT_NEAR( r1.x(), b.x(), 1e-5F );
  EXPECT_NEAR( r1.y(), b.y(), 1e-5F );
  EXPECT_NEAR( r1.z(), b.z(), 1e-5F );
  EXPECT_NEAR( r1.w(), b.w(), 1e-5F );
}

TEST_F( QuaternionTest, SlerpMidpoint )
{
  Quat a{ 0.0F, 0.0F, 0.0F, 1.0F };
  Quat b{ 0.0F, 0.0F, one_over_sqrt_two, one_over_sqrt_two };

  Quat  mid                 = slerp( a, b, 0.5F );
  float expected_half_angle = pi / 8.0F;
  EXPECT_NEAR( mid.z(), std::sin( expected_half_angle ), 1e-5F );
  EXPECT_NEAR( mid.w(), std::cos( expected_half_angle ), 1e-5F );
}
