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
  areVectorsEqual( v, transformed );
}

TEST_F( QuaternionTest, NinetyDegreeRotationAroundZ )
{
  Vec3  v{ 1.0F, 0.0F, 0.0F };
  float sqrt2_2 = 1.0F / std::sqrt( 2.0F );
  Quat  q{ 0.0F, 0.0F, sqrt2_2, sqrt2_2 };
  Vec3  transformed = transform( v, q );
  Vec3  expected{ 0.0F, 1.0F, 0.0F };
  areVectorsEqual( transformed, expected );
}

TEST_F( QuaternionTest, OneEightyDegreeRotationAroundY )
{
  Vec3 v{ 1.0F, 0.0F, 0.0F };
  Quat q{ 0.0F, 0.0F, 1.0F, 0.0F };
  Vec3 transformed = transform( v, q );
  Vec3 expected{ -1.0F, 0.0F, 0.0F };
  areVectorsEqual( transformed, expected );
}

TEST_F( QuaternionTest, TwoRotations )
{
  Vec3 v{ 1.0F, 0.0F, 0.0F };
  Quat q_z{ 0.0F, 0.0F, ONE_OVER_SQRT_TWO, ONE_OVER_SQRT_TWO };
  Quat q_x{ ONE_OVER_SQRT_TWO, 0.0F, 0.0F, ONE_OVER_SQRT_TWO };
  Vec3 transformed = transform( v, q_z );
  transformed      = transform( v, q_x );
  Vec3 expected( 0.0F, 0.0F, 1.0F );
  areVectorsEqual( transformed, expected );

  float deg_45 = PI / 4;
  float sin    = std::sin( deg_45 / 2.0F );
  float cos    = std::cos( deg_45 / 2.0F );

  Vec3 v_x{ 1.0F, 0.0F, 0.0F };
  Quat q_z45{ 0.0F, 0.0F, sin, cos };
  Quat q_y45{ 0.0F, sin, 0.0F, cos };

  transformed = transform( v_x, q_z45 );
  expected    = Vec3{ ONE_OVER_SQRT_TWO, ONE_OVER_SQRT_TWO, 0.0F };
  areVectorsEqual( transformed, expected );
  transformed = transform( v_x, q_y45 );
  expected    = Vec3{ ONE_OVER_SQRT_TWO, ONE_OVER_SQRT_TWO, ONE_OVER_SQRT_TWO };
  areVectorsEqual( transformed, expected );
}

TEST_F( QuaternionTest, SetRotationFromMatrix )
{
  Mat3 identity = Mat3::identity();
  Quat quat{};
  quat.setRotationFromMatrix( identity );
  EXPECT_FLOAT_EQ( quat.w(), 1.0F );
  EXPECT_FLOAT_EQ( quat.x(), 0.0F );
  EXPECT_FLOAT_EQ( quat.y(), 0.0F );
  EXPECT_FLOAT_EQ( quat.z(), 0.0F );
}

TEST_F( QuaternionTest, NinetyDegreeZ )
{
  float angle    = M_PI / 2;
  Mat3  rotation = makeRotationZ( angle );
  Quat  quat{};
  quat.setRotationFromMatrix( rotation );
  EXPECT_FLOAT_EQ( quat.w(), ONE_OVER_SQRT_TWO );
  EXPECT_FLOAT_EQ( quat.x(), 0.0F );
  EXPECT_FLOAT_EQ( quat.y(), 0.0F );
  EXPECT_FLOAT_EQ( quat.z(), ONE_OVER_SQRT_TWO );
}
