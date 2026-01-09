#include "linalg/vec.hpp"
#include <gtest/gtest.h>

using namespace linalg;

class Vec4Test : public ::testing::Test
{
protected:
  Vec4 v1{ 1.0F, 2.0F, 3.0F, 4.0F };
  Vec4 v2{ 4.0F, 3.0F, 2.0F, 1.0F };
};

TEST_F( Vec4Test, Getters )
{
  EXPECT_FLOAT_EQ( v1.x(), 1.0F );
  EXPECT_FLOAT_EQ( v1.y(), 2.0F );
  EXPECT_FLOAT_EQ( v1.z(), 3.0F );
  EXPECT_FLOAT_EQ( v1.w(), 4.0F );
}

TEST_F( Vec4Test, AdditionOperator )
{
  Vec4 vec3 = v1 + v2;
  EXPECT_FLOAT_EQ( vec3.x(), 5.0F );
  EXPECT_FLOAT_EQ( vec3.y(), 5.0F );
  EXPECT_FLOAT_EQ( vec3.z(), 5.0F );
  EXPECT_FLOAT_EQ( vec3.w(), 5.0F );
}

TEST_F( Vec4Test, SubtractionOperator )
{
  Vec4 vec3 = v1 - v2;
  EXPECT_FLOAT_EQ( vec3.x(), -3.0F );
  EXPECT_FLOAT_EQ( vec3.y(), -1.0F );
  EXPECT_FLOAT_EQ( vec3.z(), 1.0F );
  EXPECT_FLOAT_EQ( vec3.w(), 3.0F );
}

TEST_F( Vec4Test, MultiplicationOperatorScalar )
{
  Vec4 vec3 = v1 * 2.0F;
  EXPECT_FLOAT_EQ( vec3.x(), 2.0F );
  EXPECT_FLOAT_EQ( vec3.y(), 4.0F );
  EXPECT_FLOAT_EQ( vec3.z(), 6.0F );
  EXPECT_FLOAT_EQ( vec3.w(), 8.0F );
}

TEST_F( Vec4Test, DivisionOperatorScalar )
{
  Vec4 vec3 = v1 / 2.0F;
  EXPECT_FLOAT_EQ( vec3.x(), 0.5F );
  EXPECT_FLOAT_EQ( vec3.y(), 1.0F );
  EXPECT_FLOAT_EQ( vec3.z(), 1.5F );
  EXPECT_FLOAT_EQ( vec3.w(), 2.0F );
}

TEST_F( Vec4Test, StringOutput ) { EXPECT_EQ( std::string( v1 ), "Vec4(1.0, 2.0, 3.0, 4.0)" ); }

TEST_F( Vec4Test, Magnitude )
{
  float mag = magnitude( v1 );
  EXPECT_NEAR( mag, std::sqrt( 30.0F ), 0.0001 );
}

TEST_F( Vec4Test, Normalize )
{
  Vec4  norm = normalized( v1 );
  float mag  = magnitude( norm );
  EXPECT_NEAR( mag, 1.0F, 0.0001 );
}

TEST_F( Vec4Test, DotProduct )
{
  float dot_product = dot( v1, v2 );
  EXPECT_FLOAT_EQ( dot_product, 20.0F );
}
