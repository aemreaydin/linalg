#include "linalg/line.hpp"
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

using namespace linalg;

class LineTest : public ::testing::Test
{
protected:
  Line defaultLine;
  Line testLine;

  void SetUp() override
  {
    testLine = {
      Point3{ 1.0F, 2.0F, 3.0F },
      Vec3{ 4.0F, 5.0F, 6.0F }
    };
  }
};

TEST_F( LineTest, DefaultConstructor )
{
  EXPECT_EQ( defaultLine.point().x(), 0.0F );
  EXPECT_EQ( defaultLine.point().y(), 0.0F );
  EXPECT_EQ( defaultLine.point().z(), 0.0F );
  EXPECT_EQ( defaultLine.vector().x(), 0.0F );
  EXPECT_EQ( defaultLine.vector().y(), 0.0F );
  EXPECT_EQ( defaultLine.vector().z(), 0.0F );
}

TEST_F( LineTest, CustomConstructor )
{
  EXPECT_EQ( testLine.point().x(), 1.0F );
  EXPECT_EQ( testLine.point().y(), 2.0F );
  EXPECT_EQ( testLine.point().z(), 3.0F );
  EXPECT_EQ( testLine.vector().x(), 4.0F );
  EXPECT_EQ( testLine.vector().y(), 5.0F );
  EXPECT_EQ( testLine.vector().z(), 6.0F );
}

TEST_F( LineTest, DistanceOnLine )
{
  Vec3 point_on_line = testLine.point() + testLine.vector();
  EXPECT_FLOAT_EQ( distance( point_on_line, testLine ), 0.0F );
}

TEST_F( LineTest, DistanceFromLine )
{
  Line line{
    Point3{ 1.0F, 2.0F, 3.0F },
    Vec3{ 1.0F, 0.0F, 0.0F }
  };
  Vec3  point{ 4.0F, 5.0F, 6.0F };
  float expected_distance   = 3 * std::numbers::sqrt2_v<float>;
  float calculated_distance = distance( point, line );
  EXPECT_FLOAT_EQ( calculated_distance, expected_distance );

  line = {
    Point3{  0.0F, 2.0F, 3.0F },
    Vec3{ -2.0F, 2.0F, 2.0F }
  };
  point               = Vec3{ -8.0F, 9.0F, 9.0F };
  expected_distance   = std::numbers::sqrt2_v<float>;
  calculated_distance = distance( point, line );
  EXPECT_FLOAT_EQ( calculated_distance, expected_distance );
}

TEST_F( LineTest, DistanceBetweenSkewLines )
{
  Line line_a{
    Point3{ 0.0F, 0.0F, 0.0F },
    Vec3{ 1.0F, 0.0F, 0.0F }
  };
  Line line_b{
    Point3{ 0.0F, 1.0F, 1.0F },
    Vec3{ 0.0F, 1.0F, 0.0F }
  };

  float expected          = 1.0F;
  float distance_computed = distance( line_a, line_b );
  EXPECT_FLOAT_EQ( distance_computed, expected );
}

TEST_F( LineTest, DistanceBetweenParallelLines )
{
  Line line_a( Point3{ 0.0F, 0.0F, 0.0F }, Vec3{ 1.0F, 1.0F, 1.0F } );
  Line line_b( Point3{ 0.0F, 1.0F, 1.0F }, Vec3{ 1.0F, 1.0F, 1.0F } );

  float expected          = std::sqrt( 2.0F / 3.0F );
  float distance_computed = distance( line_a, line_b );
  EXPECT_FLOAT_EQ( distance_computed, expected );
}

TEST_F( LineTest, DistanceBetweenIntersectingLines )
{
  Line line_a( Point3{ 0.0F, 0.0F, 0.0F }, Vec3{ 1.0F, 0.0F, 0.0F } );
  Line line_b( Point3{ 0.0F, 0.0F, 0.0F }, Vec3{ 0.0F, 1.0F, 0.0F } );

  float expected          = 0.0F;
  float distance_computed = distance( line_a, line_b );
  EXPECT_FLOAT_EQ( distance_computed, expected );
}
