#include "linalg/mat3.hpp"
#include "test_utils.hpp"
#include <cmath>
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

using namespace linalg;

class Mat3Test : public ::testing::Test
{
protected:
  Mat3 testMat1{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F };
  Mat3 testMat2{ 9.0F, 8.0F, 7.0F, 6.0F, 5.0F, 4.0F, 3.0F, 2.0F, 1.0F };
  Vec3 testVec{ 1.0F, 2.0F, 3.0F };
};

TEST_F( Mat3Test, HandlesElementInitialization )
{
  Mat3 matrix{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F };
  EXPECT_FLOAT_EQ( matrix( 0, 0 ), 1.0F );
  EXPECT_FLOAT_EQ( matrix( 1, 0 ), 4.0F );
  EXPECT_FLOAT_EQ( matrix( 2, 0 ), 7.0F );
  EXPECT_FLOAT_EQ( matrix( 0, 1 ), 2.0F );
  EXPECT_FLOAT_EQ( matrix( 1, 1 ), 5.0F );
  EXPECT_FLOAT_EQ( matrix( 2, 1 ), 8.0F );
  EXPECT_FLOAT_EQ( matrix( 0, 2 ), 3.0F );
  EXPECT_FLOAT_EQ( matrix( 1, 2 ), 6.0F );
  EXPECT_FLOAT_EQ( matrix( 2, 2 ), 9.0F );
}

TEST_F( Mat3Test, HandlesVectorInitialization )
{
  Vec3 vec1{ 1.0F, 4.0F, 7.0F };
  Vec3 vec2{ 2.0F, 5.0F, 8.0F };
  Vec3 vec3{ 3.0F, 6.0F, 9.0F };
  Mat3 matrix{ vec1, vec2, vec3 };
  EXPECT_FLOAT_EQ( matrix( 0, 0 ), 1.0F );
  EXPECT_FLOAT_EQ( matrix( 1, 0 ), 4.0F );
  EXPECT_FLOAT_EQ( matrix( 2, 0 ), 7.0F );
  EXPECT_FLOAT_EQ( matrix( 0, 1 ), 2.0F );
  EXPECT_FLOAT_EQ( matrix( 1, 1 ), 5.0F );
  EXPECT_FLOAT_EQ( matrix( 2, 1 ), 8.0F );
  EXPECT_FLOAT_EQ( matrix( 0, 2 ), 3.0F );
  EXPECT_FLOAT_EQ( matrix( 1, 2 ), 6.0F );
  EXPECT_FLOAT_EQ( matrix( 2, 2 ), 9.0F );
}

TEST_F( Mat3Test, HandlesInitializationList )
{
  Mat3 mat{
    Vec3{ 1.0F, 2.0F, 3.0F },
    Vec3{ 4.0F, 5.0F, 6.0F },
    Vec3{ 7.0F, 8.0F, 9.0F }
  };

  EXPECT_FLOAT_EQ( mat( 0, 0 ), 1.0F );
  EXPECT_FLOAT_EQ( mat( 1, 0 ), 2.0F );
  EXPECT_FLOAT_EQ( mat( 2, 0 ), 3.0F );
  EXPECT_FLOAT_EQ( mat( 0, 1 ), 4.0F );
  EXPECT_FLOAT_EQ( mat( 1, 1 ), 5.0F );
  EXPECT_FLOAT_EQ( mat( 2, 1 ), 6.0F );
  EXPECT_FLOAT_EQ( mat( 0, 2 ), 7.0F );
  EXPECT_FLOAT_EQ( mat( 1, 2 ), 8.0F );
  EXPECT_FLOAT_EQ( mat( 2, 2 ), 9.0F );
}

TEST_F( Mat3Test, UnaryNegation )
{
  Mat3 mat{
    Vec3{ 1.0F, -2.0F, 3.0F },
    Vec3{ 4.0F, -5.0F, 6.0F },
    Vec3{ 7.0F, -8.0F, 9.0F }
  };

  Mat3 negated = -mat;

  Mat3 expected{
    Vec3{ -1.0F, 2.0F, -3.0F },
    Vec3{ -4.0F, 5.0F, -6.0F },
    Vec3{ -7.0F, 8.0F, -9.0F }
  };

  EXPECT_TRUE( are_matrices_equal( negated, expected ) );
}

TEST_F( Mat3Test, HandlesIndexOperator )
{
  Mat3  matrix{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F };
  auto& row = matrix[1];
  EXPECT_FLOAT_EQ( row.x(), 2.0F );
  EXPECT_FLOAT_EQ( row.y(), 5.0F );
  EXPECT_FLOAT_EQ( row.z(), 8.0F );

  row.x() = 10.0F;
  EXPECT_FLOAT_EQ( matrix( 0, 1 ), 10.0F );

  ASSERT_DEATH( (void)matrix( 3, 0 ), "" );
  ASSERT_DEATH( (void)matrix( 0, 3 ), "" );
  ASSERT_DEATH( (void)matrix[3], "" );
}

TEST_F( Mat3Test, AdditionOperator )
{
  Mat3 result = testMat1 + testMat2;
  EXPECT_FLOAT_EQ( result( 0, 0 ), 10.0F );
  EXPECT_FLOAT_EQ( result( 1, 1 ), 10.0F );
  EXPECT_FLOAT_EQ( result( 2, 2 ), 10.0F );
}

TEST_F( Mat3Test, SubtractionOperator )
{
  Mat3 result = testMat1 - testMat2;
  EXPECT_FLOAT_EQ( result( 0, 0 ), -8.0F );
  EXPECT_FLOAT_EQ( result( 1, 1 ), 0.0F );
  EXPECT_FLOAT_EQ( result( 2, 2 ), 8.0F );
}

TEST_F( Mat3Test, ScalarMultiplicationOperator )
{
  Mat3 result = testMat1 * 2.0F;
  EXPECT_FLOAT_EQ( result( 0, 0 ), 2.0F );
  EXPECT_FLOAT_EQ( result( 1, 1 ), 10.0F );
  EXPECT_FLOAT_EQ( result( 2, 2 ), 18.0F );
}

TEST_F( Mat3Test, ScalarDivisionOperator )
{
  Mat3 result = testMat1 / 2.0F;
  EXPECT_FLOAT_EQ( result( 0, 0 ), 0.5F );
  EXPECT_FLOAT_EQ( result( 1, 1 ), 2.5F );
  EXPECT_FLOAT_EQ( result( 2, 2 ), 4.5F );

  ASSERT_DEATH( (void)( testMat1 / 0.0F ), "" );
}

TEST_F( Mat3Test, HandlesMatrixAddition )
{
  auto result = testMat1 + testMat2;
  ASSERT_FLOAT_EQ( result( 0, 0 ), 10.F );
  ASSERT_FLOAT_EQ( result( 1, 0 ), 10.F );
  ASSERT_FLOAT_EQ( result( 2, 0 ), 10.F );
  ASSERT_FLOAT_EQ( result( 0, 1 ), 10.F );
  ASSERT_FLOAT_EQ( result( 1, 1 ), 10.F );
  ASSERT_FLOAT_EQ( result( 2, 1 ), 10.F );
  ASSERT_FLOAT_EQ( result( 0, 2 ), 10.F );
  ASSERT_FLOAT_EQ( result( 1, 2 ), 10.F );
  ASSERT_FLOAT_EQ( result( 2, 2 ), 10.F );
}

TEST_F( Mat3Test, HandlesMatrixSubtraction )
{
  auto result = testMat1 - testMat2;
  ASSERT_FLOAT_EQ( result( 0, 0 ), -8.0F );
  ASSERT_FLOAT_EQ( result( 1, 0 ), -2.0F );
  ASSERT_FLOAT_EQ( result( 2, 0 ), 4.0F );
  ASSERT_FLOAT_EQ( result( 0, 1 ), -6.0F );
  ASSERT_FLOAT_EQ( result( 1, 1 ), 0.0F );
  ASSERT_FLOAT_EQ( result( 2, 1 ), 6.0F );
  ASSERT_FLOAT_EQ( result( 0, 2 ), -4.0F );
  ASSERT_FLOAT_EQ( result( 1, 2 ), 2.0F );
  ASSERT_FLOAT_EQ( result( 2, 2 ), 8.0F );
}

TEST_F( Mat3Test, HandlesMatrixMultiplicationByMatrix )
{
  auto result = testMat1 * testMat2;
  ASSERT_FLOAT_EQ( result( 0, 0 ), 30.0F );
  ASSERT_FLOAT_EQ( result( 0, 1 ), 24.0F );
  ASSERT_FLOAT_EQ( result( 0, 2 ), 18.0F );
  ASSERT_FLOAT_EQ( result( 1, 0 ), 84.0F );
  ASSERT_FLOAT_EQ( result( 1, 1 ), 69.0F );
  ASSERT_FLOAT_EQ( result( 1, 2 ), 54.0F );
  ASSERT_FLOAT_EQ( result( 2, 0 ), 138.0F );
  ASSERT_FLOAT_EQ( result( 2, 1 ), 114.0F );
  ASSERT_FLOAT_EQ( result( 2, 2 ), 90.0F );
}

TEST_F( Mat3Test, HandlesMatrixMultiplicationByVector )
{
  auto result = testMat1 * testVec;
  ASSERT_FLOAT_EQ( result[0], 14.0F );
  ASSERT_FLOAT_EQ( result[1], 32.0F );
  ASSERT_FLOAT_EQ( result[2], 50.0F );

  Mat3 test_mat{
    Vec3{ 1.0F, 4.0F, 7.0F },
    Vec3{ 2.0F, 5.0F, 8.0F },
    Vec3{ 3.0F, 6.0F, 9.0F }
  };
  auto result2 = test_mat * testVec;
  ASSERT_FLOAT_EQ( result2[0], 14.0F );
  ASSERT_FLOAT_EQ( result2[1], 32.0F );
  ASSERT_FLOAT_EQ( result2[2], 50.0F );
}

TEST_F( Mat3Test, Determinant )
{
  Mat3 identity{ 1.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 1.0F };
  EXPECT_FLOAT_EQ( determinant( identity ), 1.0F );

  Mat3 matrix{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F };
  EXPECT_FLOAT_EQ( determinant( matrix ), 0.0F );

  Mat3 matrix2{ 3.0F, 2.0F, 1.0F, 1.0F, 1.0F, 0.0F, 0.0F, 1.0F, 1.0F };
  EXPECT_FLOAT_EQ( determinant( matrix2 ), 2.0F );
}

TEST_F( Mat3Test, Inverse )
{
  const Mat3 mat{ 1.0F, 2.0F, 3.0F, 0.0F, 1.0F, 4.0F, 5.0F, 6.0F, 0.0F };
  Mat3       expected_inverse{
    Vec3{ -24.0F,  20.0F, -5.0F },
    Vec3{  18.0F, -15.0F,  4.0F },
    Vec3{   5.0F,  -4.0F,  1.0F }
  };
  Mat3 actual_inverse = inverse( mat );
  for ( int i = 0; i < 3; ++i )
  {
    for ( int j = 0; j < 3; ++j )
    {
      EXPECT_NEAR( actual_inverse( i, j ), expected_inverse( i, j ), 0.00001F );
    }
  }

  const Mat3 zero_det_mat{ 1.0F, 2.0F, 3.0F, 1.0F, 2.0F, 3.0F, 1.0F, 2.0F, 3.0F };
  ASSERT_DEATH( (void)inverse( zero_det_mat ), "" );
}

TEST_F( Mat3Test, RotationX )
{
  float angle  = pi / 4;
  auto  result = make_rotation_x( angle );
  Mat3  expected{
    1.0F, 0.0F, 0.0F, 0.0F, std::cos( angle ), -std::sin( angle ), 0.0F, std::sin( angle ), std::cos( angle )
  };
  EXPECT_TRUE( are_matrices_equal( result, expected ) );
}

TEST_F( Mat3Test, RotationY )
{
  float angle  = pi / 4;
  auto  result = make_rotation_y( angle );
  Mat3  expected{
    std::cos( angle ), 0.0F, std::sin( angle ), 0.0F, 1.0F, 0.0F, -std::sin( angle ), 0.0F, std::cos( angle )
  };
  EXPECT_TRUE( are_matrices_equal( result, expected ) );
}

TEST_F( Mat3Test, RotationZ )
{
  float angle  = pi / 4;
  auto  result = make_rotation_z( angle );
  Mat3  expected{
    std::cos( angle ), -std::sin( angle ), 0.0F, std::sin( angle ), std::cos( angle ), 0.0F, 0.0F, 0.0F, 1.0F
  };
  EXPECT_TRUE( are_matrices_equal( result, expected ) );
}

TEST_F( Mat3Test, GeneralRotation )
{
  float       angle     = pi / 4;
  const float inv_sqrt3 = std::numbers::inv_sqrt3_v<float>;
  Vec3        axis{ inv_sqrt3, inv_sqrt3, inv_sqrt3 };
  auto        result = make_rotation( angle, axis );
  Mat3        expected{
    0.8047379F, -0.3106172F, 0.5058793F, 0.5058793F, 0.8047379F, -0.3106172F, -0.3106172F, 0.5058793F, 0.8047379F
  };
  EXPECT_TRUE( are_matrices_equal( result, expected ) );
}

TEST_F( Mat3Test, ReflectionMatrix )
{
  Vec3 inv{ 1.0F, 0.0F, 0.0F };
  auto reflection = make_reflection( inv );
  Vec3 vec{ 1.0F, 1.0F, 1.0F };
  auto reflected_v = reflection * vec;
  EXPECT_FLOAT_EQ( reflected_v.x(), -1.0F );
  EXPECT_FLOAT_EQ( reflected_v.y(), 1.0F );
  EXPECT_FLOAT_EQ( reflected_v.z(), 1.0F );
}

TEST_F( Mat3Test, InvolutionMatrix )
{
  Vec3 inv{ 1.0F, 0.0F, 0.0F };
  auto involution = make_involution( inv );
  Vec3 vec{ 1.0F, 1.0F, 1.0F };
  auto involuted_v = involution * vec;
  EXPECT_FLOAT_EQ( involuted_v.x(), 1.0F );
  EXPECT_FLOAT_EQ( involuted_v.y(), -1.0F );
  EXPECT_FLOAT_EQ( involuted_v.z(), -1.0F );
}

TEST_F( Mat3Test, Scale )
{
  Vec3 vec{ 2.0F, 3.0F, 5.0F };
  Mat3 scale = make_scale( 2.0F, 2.0F, 2.0F );

  auto scaled_vec = scale * vec;
  EXPECT_FLOAT_EQ( scaled_vec.x(), 4.0F );
  EXPECT_FLOAT_EQ( scaled_vec.y(), 6.0F );
  EXPECT_FLOAT_EQ( scaled_vec.z(), 10.0F );

  scale      = make_scale( 2.0F, 3.0F, 4.0F );
  scaled_vec = scale * vec;
  EXPECT_FLOAT_EQ( scaled_vec.x(), 4.0F );
  EXPECT_FLOAT_EQ( scaled_vec.y(), 9.0F );
  EXPECT_FLOAT_EQ( scaled_vec.z(), 20.0F );
}

TEST_F( Mat3Test, ScaleOnArbitraryAxis )
{
  Vec3 vec{ 2.0F, 3.0F, 3.0F };
  Mat3 scale      = make_scale( 3.0F, Vec3{ 0.0F, 1.0F, 0.0F } );
  auto scaled_vec = scale * vec;

  EXPECT_FLOAT_EQ( scaled_vec.x(), 2.0F );
  EXPECT_FLOAT_EQ( scaled_vec.y(), 9.0F );
  EXPECT_FLOAT_EQ( scaled_vec.z(), 3.0F );
}

TEST_F( Mat3Test, ZeroAngleSkew )
{
  Vec3  skew_direction{ 1.0F, 1.0F, 1.0F };
  Vec3  projected{ 1.0F, 0.0F, 0.0F };
  float angle = 0.0F;

  auto result = make_skew( angle, skew_direction, projected );
  Mat3 expected{ 1.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 1.0F };

  EXPECT_TRUE( are_matrices_equal( result, expected ) );

  auto output_vec = result * Vec3{ 1.0F, 1.0F, 1.0F };
  EXPECT_FLOAT_EQ( output_vec.x(), 1.0F );
  EXPECT_FLOAT_EQ( output_vec.y(), 1.0F );
  EXPECT_FLOAT_EQ( output_vec.z(), 1.0F );
}

TEST_F( Mat3Test, NonZeroAngleSkew )
{
  Vec3  skew_direction{ 0.0F, 1.0F, 0.0F };
  Vec3  projected{ 1.0F, 0.0F, 0.0F };
  float angle = pi / 4;

  auto result = make_skew( angle, skew_direction, projected );
  auto tan    = std::tan( angle );
  Mat3 expected{ 1.0F, 0.0F, 0.0F, tan, 1.0F, 0.0F, 0.0F, 0.0F, 1.0F };

  EXPECT_TRUE( are_matrices_equal( result, expected ) );

  auto output_vec = result * Vec3{ 1.0F, 0.0F, 0.0F };
  EXPECT_FLOAT_EQ( output_vec.x(), 1.0F );
  EXPECT_FLOAT_EQ( output_vec.y(), tan );
  EXPECT_FLOAT_EQ( output_vec.z(), 0.0F );
}
