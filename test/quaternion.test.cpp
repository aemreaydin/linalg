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
