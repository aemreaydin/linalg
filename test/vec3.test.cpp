#include "linalg/vec.hpp"
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

using namespace linalg;

class Vec3Test : public ::testing::Test
{
protected:
  Vec3 v1{ 1.0F, 2.0F, 3.0F };
  Vec3 v2{ 4.0F, 5.0F, 6.0F };
};

TEST_F( Vec3Test, Constructor )
{
  Vec3 vec3{ 1.0F, 2.0F, 3.0F };
  EXPECT_EQ( vec3.x(), 1.0F );
  EXPECT_EQ( vec3.y(), 2.0F );
  EXPECT_EQ( vec3.z(), 3.0F );
  vec3 += 1.0F;
}

TEST_F( Vec3Test, DefaultConstructor )
{
  Vec3 vec3;
  EXPECT_EQ( vec3.x(), 0.0F );
  EXPECT_EQ( vec3.y(), 0.0F );
  EXPECT_EQ( vec3.z(), 0.0F );
}

TEST_F( Vec3Test, ParameterizedConstructor )
{
  EXPECT_EQ( v1.x(), 1.0F );
  EXPECT_EQ( v1.y(), 2.0F );
  EXPECT_EQ( v1.z(), 3.0F );
}

TEST_F( Vec3Test, IndexingOperator )
{
  EXPECT_EQ( v1[0], 1.0F );
  EXPECT_EQ( v1[1], 2.0F );
  EXPECT_EQ( v1[2], 3.0F );

  EXPECT_DEATH( { (void)v1[3]; }, "" );
}

TEST_F( Vec3Test, AdditionOperator )
{
  Vec3 result = v1 + v2;
  EXPECT_EQ( result.x(), 5.0F );
  EXPECT_EQ( result.y(), 7.0F );
  EXPECT_EQ( result.z(), 9.0F );
}

TEST_F( Vec3Test, SubtractionOperator )
{
  Vec3 result = v1 - v2;
  EXPECT_EQ( result.x(), -3.0F );
  EXPECT_EQ( result.y(), -3.0F );
  EXPECT_EQ( result.z(), -3.0F );
}

TEST_F( Vec3Test, MultiplicationOperatorScalar )
{
  Vec3 result = v1 * 2.0F;
  EXPECT_EQ( result.x(), 2.0F );
  EXPECT_EQ( result.y(), 4.0F );
  EXPECT_EQ( result.z(), 6.0F );
}

TEST_F( Vec3Test, DivisionOperatorScalar )
{
  Vec3 result = v2 / 2.0F;
  EXPECT_EQ( result.x(), 2.0F );
  EXPECT_EQ( result.y(), 2.5F );
  EXPECT_EQ( result.z(), 3.0F );

  EXPECT_DEATH( { (void)( v2 / 0.0F ); }, "" );
}

TEST_F( Vec3Test, UnaryNegationOperator )
{
  Vec3 result = -v1;
  EXPECT_EQ( result.x(), -1.0F );
  EXPECT_EQ( result.y(), -2.0F );
  EXPECT_EQ( result.z(), -3.0F );
}

TEST_F( Vec3Test, CompoundAdditionAssignmentOperator )
{
  Vec3 result = v1;
  result += 2.0F;
  EXPECT_EQ( result.x(), 3.0F );
  EXPECT_EQ( result.y(), 4.0F );
  EXPECT_EQ( result.z(), 5.0F );
}

TEST_F( Vec3Test, CompoundSubtractionAssignmentOperator )
{
  Vec3 result = v2;
  result -= 1.0F;
  EXPECT_EQ( result.x(), 3.0F );
  EXPECT_EQ( result.y(), 4.0F );
  EXPECT_EQ( result.z(), 5.0F );
}

TEST_F( Vec3Test, CompoundMultiplicationAssignmentOperator )
{
  auto result = v1;
  result *= 2.0F;
  EXPECT_EQ( result.x(), 2.0F );
  EXPECT_EQ( result.y(), 4.0F );
  EXPECT_EQ( result.z(), 6.0F );
}

TEST_F( Vec3Test, CompoundDivisionAssignmentOperator )
{
  auto result = v2;
  result /= 2.0F;
  EXPECT_EQ( result.x(), 2.0F );
  EXPECT_EQ( result.y(), 2.5F );
  EXPECT_EQ( result.z(), 3.0F );

  EXPECT_DEATH( { result /= 0.0F; }, "" );
}

TEST_F( Vec3Test, StringOutput ) { EXPECT_EQ( std::string( v1 ), "Vec3(1.0, 2.0, 3.0)" ); }

TEST_F( Vec3Test, Magnitude )
{
  EXPECT_FLOAT_EQ( magnitude( v1 ), std::sqrt( 14.0F ) );
  EXPECT_FLOAT_EQ( magnitude( v2 ), std::sqrt( 77.0F ) );
}

TEST_F( Vec3Test, Normalize )
{
  auto normalized_v1 = normalized( v1 );
  auto normalized_v2 = normalized( v2 );

  auto magnitude_v1 = magnitude( v1 );
  auto magnitude_v2 = magnitude( v2 );

  EXPECT_FLOAT_EQ( magnitude( normalized_v1 ), 1.0F );
  EXPECT_FLOAT_EQ( magnitude( normalized_v2 ), 1.0F );

  for ( int i = 0; i < 3; ++i )
  {
    EXPECT_FLOAT_EQ( normalized_v1[i], v1[i] / magnitude_v1 );
    EXPECT_FLOAT_EQ( normalized_v2[i], v2[i] / magnitude_v2 );
  }
}

TEST_F( Vec3Test, DotProduct )
{
  Vec3 vec1{ 1.0F, 0.0F, 0.0F };
  Vec3 vec2{ 0.0F, 1.0F, 0.0F };
  Vec3 vec3{ 1.0F, 1.0F, 0.0F };

  EXPECT_FLOAT_EQ( dot( vec1, vec2 ), 0.0F );
  EXPECT_FLOAT_EQ( dot( vec1, vec3 ), 1.0F );
  EXPECT_FLOAT_EQ( dot( vec1, vec3 ), dot( vec3, vec1 ) );
}

TEST_F( Vec3Test, CrossProduct )
{
  Vec3 vec1{ 1.0F, 0.0F, 0.0F };
  Vec3 vec2{ 0.0F, 1.0F, 0.0F };
  Vec3 vec3{ 0.0F, 0.0F, 1.0F };

  auto cross_result = cross( vec1, vec2 );
  EXPECT_FLOAT_EQ( cross_result.x(), vec3.x() );
  EXPECT_FLOAT_EQ( cross_result.y(), vec3.y() );
  EXPECT_FLOAT_EQ( cross_result.z(), vec3.z() );

  auto parallel_cross_result = cross( vec1, Vec3{ 2.0F, 0.0F, 0.0F } );
  EXPECT_FLOAT_EQ( parallel_cross_result.x(), 0.0F );
  EXPECT_FLOAT_EQ( parallel_cross_result.y(), 0.0F );
  EXPECT_FLOAT_EQ( parallel_cross_result.z(), 0.0F );

  auto negative_cross_result = cross( vec2, vec1 );
  EXPECT_FLOAT_EQ( negative_cross_result.x(), -cross_result.x() );
  EXPECT_FLOAT_EQ( negative_cross_result.y(), -cross_result.y() );
  EXPECT_FLOAT_EQ( negative_cross_result.z(), -cross_result.z() );
}

TEST_F( Vec3Test, ProjectionAndRejection )
{
  Vec3 source{ 2.0F, 3.0F, 0.0F };
  Vec3 target{ 5.0F, 0.0F, 0.0F };
  auto projected = project( source, target );
  EXPECT_EQ( projected.x(), 2.0F );
  EXPECT_EQ( projected.y(), 0.0F );
  EXPECT_EQ( projected.z(), 0.0F );

  auto rejected = reject( source, target );
  EXPECT_EQ( rejected.x(), 0.0F );
  EXPECT_EQ( rejected.y(), 3.0F );
  EXPECT_EQ( rejected.z(), 0.0F );
}

TEST_F( Vec3Test, CheckUnitVector )
{
  const float inv_sqrt3 = 1.0F / std::sqrt( 3.0F );
  Vec3        unit_vec{ inv_sqrt3, inv_sqrt3, inv_sqrt3 };
  EXPECT_TRUE( isUnitVector( unit_vec ) );
  Vec3 non_unit_vec{ 1.0F, 2.0F, 3.0F };
  EXPECT_FALSE( isUnitVector( non_unit_vec ) );
}
