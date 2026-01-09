#include "linalg/plane.hpp"
#include "linalg/point.hpp"
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

using namespace linalg;

class PlaneTest : public ::testing::Test
{
};

TEST_F( PlaneTest, Constructor )
{
  Plane plane_float{ 1.0F, 2.0F, 3.0F, 4.0F };

  EXPECT_FLOAT_EQ( plane_float.x(), 1.0F );
  EXPECT_FLOAT_EQ( plane_float.y(), 2.0F );
  EXPECT_FLOAT_EQ( plane_float.z(), 3.0F );
  EXPECT_FLOAT_EQ( plane_float.w(), 4.0F );

  Plane plane_vec_float{
    Vec3{ 1.0F, 2.0F, 3.0F },
    4.0F
  };

  EXPECT_FLOAT_EQ( plane_vec_float.x(), 1.0F );
  EXPECT_FLOAT_EQ( plane_vec_float.y(), 2.0F );
  EXPECT_FLOAT_EQ( plane_vec_float.z(), 3.0F );
  EXPECT_FLOAT_EQ( plane_vec_float.w(), 4.0F );
}

TEST_F( PlaneTest, DotProduct )
{
  Vec3   normal{ 0.0F, 1.0F, 0.0F };
  Point3 q{ 4.0F, 3.0F, 2.0F };

  float d = dot( normal, q );
  EXPECT_FLOAT_EQ( d, 3.0F );

  Plane  plane{ normal, -d };
  Point3 p{ 0.0F, 3.0F, 0.0F };
  EXPECT_FLOAT_EQ( dot( normal, p ), 3.0F );
  EXPECT_FLOAT_EQ( dot( normal, p - q ), 0.0F );

  EXPECT_FLOAT_EQ( dot( plane, p ), 0.0F );
}

TEST_F( PlaneTest, PointNotOnPlane )
{
  Plane  plane{ 1.0F, 0.0F, 0.0F, -2.0F };
  Point3 point{ 1.0F, 0.0F, 0.0F };
  EXPECT_FLOAT_EQ( dot( plane, point ), -1.0F );
}

TEST_F( PlaneTest, VectorNotPerpendicularToPlane )
{
  Plane plane{ 0.0F, 1.0F, 0.0F, 0.0F };
  Vec3  vector{ 0.0F, 1.0F, 0.0F };
  EXPECT_FLOAT_EQ( dot( plane, vector ), 1.0F );
}

TEST_F( PlaneTest, Reflection )
{
  Plane plane_non_origin{ 1.0F, 2.0F, 3.0F, 14.0F };
  plane_non_origin.normalizeInPlace();
  Plane plane_origin{ 1.0F, 2.0F, 3.0F, 0.0F };
  plane_origin.normalizeInPlace();

  Point3 point{ 2.0F, 4.0F, 6.0F };

  Point3 reflected_non_origin = makeReflection( plane_non_origin ) * point;
  Point3 reflected_origin     = makeReflection( plane_origin ) * point;

  EXPECT_FLOAT_EQ( reflected_non_origin.x(), -4.0F );
  EXPECT_FLOAT_EQ( reflected_non_origin.y(), -8.0F );
  EXPECT_FLOAT_EQ( reflected_non_origin.z(), -12.0F );

  EXPECT_FLOAT_EQ( reflected_origin.x(), -2.0F );
  EXPECT_FLOAT_EQ( reflected_origin.y(), -4.0F );
  EXPECT_FLOAT_EQ( reflected_origin.z(), -6.0F );
}

TEST_F( PlaneTest, PlaneAndLineParallel )
{
  Plane plane{ 0.0F, 1.0F, 0.0F, -5.0F };
  Line  line{
    Point3{ 1.0F, 6.0F, 1.0F },
    Vec3{ 1.0F, 0.0F, 1.0F }
  };

  std::optional<Point3> intersection = getIntersection( plane, line );
  ASSERT_FALSE( intersection );
}

TEST_F( PlaneTest, LineIntersectsPlane )
{
  Plane plane{ 0.0F, 1.0F, 0.0F, -5.0F };
  Line  line{
    Point3{ 1.0F, 0.0F, 1.0F },
    Vec3{ 0.0F, 1.0F, 0.0F }
  };

  auto opt_intersection = getIntersection( plane, line );
  ASSERT_TRUE( opt_intersection.has_value() );
  EXPECT_FLOAT_EQ( opt_intersection->x(), 1.0F );
  EXPECT_FLOAT_EQ( opt_intersection->y(), 5.0F );
  EXPECT_FLOAT_EQ( opt_intersection->x(), 1.0F );
}

TEST_F( PlaneTest, ThreePlanesIntersection )
{
  Plane plane_a{ 1.0F, 2.0F, 3.0F, 4.0F };
  Plane plane_b{ 1.0F, 1.0F, 1.0F, 1.0F };
  Plane plane_c{ 2.0F, 3.0F, 2.0F, 1.0F };

  auto opt_point = getIntersection( plane_a, plane_b, plane_c );
  ASSERT_TRUE( opt_point.has_value() );

  EXPECT_FLOAT_EQ( opt_point->x(), 0.0F );
  EXPECT_FLOAT_EQ( opt_point->y(), 1.0F );
  EXPECT_FLOAT_EQ( opt_point->z(), -2.0F );
}

TEST_F( PlaneTest, ThreePlanesNotLinearlyIndependent )
{
  Plane plane_a{ 2.0F, 2.0F, 2.0F, 4.0F };
  Plane plane_b{ 1.0F, 1.0F, 1.0F, 1.0F };
  Plane plane_c{ 2.0F, 3.0F, 2.0F, 1.0F };

  auto opt_point = getIntersection( plane_a, plane_b, plane_c );
  ASSERT_FALSE( opt_point.has_value() );
}

TEST_F( PlaneTest, TwoPlanesIntersection )
{
  Plane plane_a{ 2.0F, -1.0F, 1.0F, -1.0F };
  Plane plane_b{ 1.0F, 1.0F, 1.0F, -6.0F };

  auto opt_line = getIntersection( plane_a, plane_b );
  ASSERT_TRUE( opt_line.has_value() );

  EXPECT_FLOAT_EQ( opt_line->point().x(), 16.0F / 14.0F );
  EXPECT_FLOAT_EQ( opt_line->point().y(), 43.0F / 14.0F );
  EXPECT_FLOAT_EQ( opt_line->point().z(), 25.0F / 14.0F );

  EXPECT_FLOAT_EQ( opt_line->vector().x(), -2.0F );
  EXPECT_FLOAT_EQ( opt_line->vector().y(), -1.0F );
  EXPECT_FLOAT_EQ( opt_line->vector().z(), 3.0F );
}
