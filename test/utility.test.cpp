#include "linalg/utility.hpp"
#include "linalg/constants.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

using namespace linalg;

class UtilityTest : public ::testing::Test
{
protected:
  void SetUp() override {}
};

TEST_F( UtilityTest, RadiansToDegrees )
{
  EXPECT_FLOAT_EQ( degrees( pi ), 180.0F );
  EXPECT_FLOAT_EQ( degrees( pi / 2.0F ), 90.0F );
  EXPECT_FLOAT_EQ( degrees( 0.0F ), 0.0F );
}

TEST_F( UtilityTest, DegreesToRadians )
{
  EXPECT_FLOAT_EQ( radians( 180.0F ), pi );
  EXPECT_FLOAT_EQ( radians( 90.0F ), pi / 2.0F );
  EXPECT_FLOAT_EQ( radians( 0.0F ), 0.0F );
}

TEST_F( UtilityTest, RadiansDegreesRoundtrip )
{
  EXPECT_FLOAT_EQ( degrees( radians( 45.0F ) ), 45.0F );
  EXPECT_FLOAT_EQ( radians( degrees( 1.0F ) ), 1.0F );
}

TEST_F( UtilityTest, MixFloat )
{
  EXPECT_FLOAT_EQ( mix( 0.0F, 10.0F, 0.0F ), 0.0F );
  EXPECT_FLOAT_EQ( mix( 0.0F, 10.0F, 1.0F ), 10.0F );
  EXPECT_FLOAT_EQ( mix( 0.0F, 10.0F, 0.5F ), 5.0F );
  EXPECT_FLOAT_EQ( mix( 2.0F, 8.0F, 0.25F ), 3.5F );
}

TEST_F( UtilityTest, MixVec3 )
{
  Vec3 a{ 0.0F, 0.0F, 0.0F };
  Vec3 b{ 10.0F, 20.0F, 30.0F };
  Vec3 result = mix( a, b, 0.5F );
  EXPECT_FLOAT_EQ( result.x(), 5.0F );
  EXPECT_FLOAT_EQ( result.y(), 10.0F );
  EXPECT_FLOAT_EQ( result.z(), 15.0F );
}

TEST_F( UtilityTest, MinVec3 )
{
  Vec3 a{ 1.0F, 5.0F, 3.0F };
  Vec3 b{ 4.0F, 2.0F, 6.0F };
  Vec3 result = min( a, b );
  EXPECT_FLOAT_EQ( result.x(), 1.0F );
  EXPECT_FLOAT_EQ( result.y(), 2.0F );
  EXPECT_FLOAT_EQ( result.z(), 3.0F );
}

TEST_F( UtilityTest, MaxVec3 )
{
  Vec3 a{ 1.0F, 5.0F, 3.0F };
  Vec3 b{ 4.0F, 2.0F, 6.0F };
  Vec3 result = max( a, b );
  EXPECT_FLOAT_EQ( result.x(), 4.0F );
  EXPECT_FLOAT_EQ( result.y(), 5.0F );
  EXPECT_FLOAT_EQ( result.z(), 6.0F );
}
