#include "linalg/point.hpp"
#include <gtest/gtest.h>

using namespace linalg;

class Point3Test : public ::testing::Test
{
protected:
  Point3 defaultPoint;
  Point3 testPoint;
  Vec3   testVec;

  void SetUp() override
  {
    testPoint = Point3{ 1.0F, 2.0F, 3.0F };
    testVec   = Vec3{ 4.0F, 5.0F, 6.0F };
  }
};

TEST_F( Point3Test, DefaultConstructor )
{
  EXPECT_EQ( defaultPoint.x(), 0.0F );
  EXPECT_EQ( defaultPoint.y(), 0.0F );
  EXPECT_EQ( defaultPoint.z(), 0.0F );
}

TEST_F( Point3Test, ParameterizedConstructor )
{
  EXPECT_EQ( testPoint.x(), 1.0F );
  EXPECT_EQ( testPoint.y(), 2.0F );
  EXPECT_EQ( testPoint.z(), 3.0F );
}

TEST_F( Point3Test, ConstructFromVec3 )
{
  Point3 point( testVec );
  EXPECT_EQ( point.x(), 4.0F );
  EXPECT_EQ( point.y(), 5.0F );
  EXPECT_EQ( point.z(), 6.0F );
}

TEST_F( Point3Test, AddVectorToPoint )
{
  Point3 result = testPoint + testVec;
  EXPECT_EQ( result.x(), 5.0F );
  EXPECT_EQ( result.y(), 7.0F );
  EXPECT_EQ( result.z(), 9.0F );
}

TEST_F( Point3Test, SubtractVectorFromPoint )
{
  Point3 result = testPoint - testVec;
  EXPECT_EQ( result.x(), -3.0F );
  EXPECT_EQ( result.y(), -3.0F );
  EXPECT_EQ( result.z(), -3.0F );
}

TEST_F( Point3Test, SubtractPointFromPoint )
{
  Point3 point_a{ 5.0F, 7.0F, 9.0F };
  Point3 point_b{ 1.0F, 2.0F, 3.0F };
  Vec3   result = point_a - point_b;
  EXPECT_EQ( result.x(), 4.0F );
  EXPECT_EQ( result.y(), 5.0F );
  EXPECT_EQ( result.z(), 6.0F );
}

TEST_F( Point3Test, IndexOperator )
{
  EXPECT_EQ( testPoint[0], 1.0F );
  EXPECT_EQ( testPoint[1], 2.0F );
  EXPECT_EQ( testPoint[2], 3.0F );
}

TEST_F( Point3Test, MutableIndexOperator )
{
  Point3 point{ 0.0F, 0.0F, 0.0F };
  point[0] = 10.0F;
  point[1] = 20.0F;
  point[2] = 30.0F;
  EXPECT_EQ( point.x(), 10.0F );
  EXPECT_EQ( point.y(), 20.0F );
  EXPECT_EQ( point.z(), 30.0F );
}

TEST_F( Point3Test, MutableAccessors )
{
  Point3 point{ 0.0F, 0.0F, 0.0F };
  point.x() = 1.0F;
  point.y() = 2.0F;
  point.z() = 3.0F;
  EXPECT_EQ( point.x(), 1.0F );
  EXPECT_EQ( point.y(), 2.0F );
  EXPECT_EQ( point.z(), 3.0F );
}

TEST_F( Point3Test, DistanceBetweenPoints )
{
  Point3 point_a{ 0.0F, 0.0F, 0.0F };
  Point3 point_b{ 3.0F, 4.0F, 0.0F };
  Vec3   diff = point_b - point_a;
  float  dist = magnitude( diff );
  EXPECT_FLOAT_EQ( dist, 5.0F );
}

TEST_F( Point3Test, ChainedOperations )
{
  Vec3   displacement1{ 1.0F, 0.0F, 0.0F };
  Vec3   displacement2{ 0.0F, 1.0F, 0.0F };
  Point3 origin{ 0.0F, 0.0F, 0.0F };
  Point3 result = origin + displacement1 + displacement2;
  EXPECT_EQ( result.x(), 1.0F );
  EXPECT_EQ( result.y(), 1.0F );
  EXPECT_EQ( result.z(), 0.0F );
}
