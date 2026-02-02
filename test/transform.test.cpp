#include "linalg/transform.hpp"
#include "test_utils.hpp"
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

using namespace linalg;

class Transform4Test : public ::testing::Test
{
protected:
  Transform4 translation{
    Vec3{},
    Vec3{},
    Vec3{},
    Point3{ 1.0F, 2.0F, 3.0F }
  };
};

TEST_F( Transform4Test, IndexOperators )
{
  Transform4 index_mat = {
    Vec3{ 7.0F, 3.0F, 1.0F },
    Vec3{ 9.0F, 4.0F, 2.0F },
    Vec3{ 8.0F, 1.0F, 7.0F },
    Point3{ 2.0F, 7.0F, 5.0F }
  };

  EXPECT_FLOAT_EQ( index_mat( 1, 3 ), 7.0F );
  EXPECT_FLOAT_EQ( index_mat( 2, 3 ), 5.0F );
  EXPECT_FLOAT_EQ( index_mat( 3, 3 ), 1.0F );
  EXPECT_FLOAT_EQ( index_mat( 0, 2 ), 8.0F );
  EXPECT_FLOAT_EQ( index_mat( 3, 1 ), 0.0F );
  EXPECT_FLOAT_EQ( index_mat( 1, 1 ), 4.0F );
  EXPECT_FLOAT_EQ( index_mat( 0, 1 ), 9.0F );
  EXPECT_FLOAT_EQ( index_mat( 2, 1 ), 2.0F );

  Vec3 index_vec3 = index_mat[1];
  EXPECT_FLOAT_EQ( index_vec3[0], 9.0F );
  EXPECT_FLOAT_EQ( index_vec3[1], 4.0F );
  EXPECT_FLOAT_EQ( index_vec3[2], 2.0F );
}

TEST_F( Transform4Test, Translation )
{
  Point3 point = translation.get_translation();
  EXPECT_FLOAT_EQ( point.x(), 1.0F );
  EXPECT_FLOAT_EQ( point.y(), 2.0F );
  EXPECT_FLOAT_EQ( point.z(), 3.0F );

  translation.set_translation( Point3{ 4.0F, 5.0F, 6.0F } );
  point = translation.get_translation();
  EXPECT_FLOAT_EQ( point.x(), 4.0F );
  EXPECT_FLOAT_EQ( point.y(), 5.0F );
  EXPECT_FLOAT_EQ( point.z(), 6.0F );
}

TEST_F( Transform4Test, Inverse )
{
  Transform4 mat{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F };
  Transform4 inv = inverse( mat );

  are_matrices_equal( inv, Transform4::identity() );
}

TEST_F( Transform4Test, PointVsVector )
{
  Vec3   vec{ 1.0F, 2.0F, 3.0F };
  Point3 point{ 1.0F, 1.0F, 1.0F };

  Point3     translate{ 1.0F, 2.0F, 3.0F };
  Transform4 translation_mat{ Transform4::identity() };
  translation_mat.set_translation( translate );

  Vec3   vec_translated   = translation_mat * vec;
  Point3 point_translated = translation_mat * point;

  EXPECT_FLOAT_EQ( vec.x(), vec_translated.x() );
  EXPECT_FLOAT_EQ( vec.y(), vec_translated.y() );
  EXPECT_FLOAT_EQ( vec.z(), vec_translated.z() );

  EXPECT_FLOAT_EQ( point.x() + translate.x(), point_translated.x() );
  EXPECT_FLOAT_EQ( point.y() + translate.y(), point_translated.y() );
  EXPECT_FLOAT_EQ( point.z() + translate.z(), point_translated.z() );
}

TEST_F( Transform4Test, DefaultConstructor )
{
  Transform4 t;
  for ( size_t i = 0; i < 4; ++i )
  {
    for ( size_t j = 0; j < 4; ++j )
    {
      EXPECT_FLOAT_EQ( t( i, j ), 0.0F );
    }
  }
}

TEST_F( Transform4Test, ConstructFromVec3AndPoint3 )
{
  Vec3   col0{ 1.0F, 0.0F, 0.0F };
  Vec3   col1{ 0.0F, 1.0F, 0.0F };
  Vec3   col2{ 0.0F, 0.0F, 1.0F };
  Point3 col3{ 5.0F, 6.0F, 7.0F };

  Transform4 t{ col0, col1, col2, col3 };
  EXPECT_FLOAT_EQ( t( 0, 0 ), 1.0F );
  EXPECT_FLOAT_EQ( t( 1, 1 ), 1.0F );
  EXPECT_FLOAT_EQ( t( 2, 2 ), 1.0F );
  EXPECT_FLOAT_EQ( t( 3, 3 ), 1.0F );
  EXPECT_FLOAT_EQ( t( 0, 3 ), 5.0F );
  EXPECT_FLOAT_EQ( t( 1, 3 ), 6.0F );
  EXPECT_FLOAT_EQ( t( 2, 3 ), 7.0F );
}

TEST_F( Transform4Test, ConstructFromMat4 )
{
  Mat4       mat = Mat4::identity();
  Transform4 t( mat );
  EXPECT_TRUE( are_matrices_equal( t, mat ) );
}

TEST_F( Transform4Test, GetColumn3 )
{
  Transform4 t{
    Vec3{  1.0F,  2.0F,  3.0F },
    Vec3{  4.0F,  5.0F,  6.0F },
    Vec3{  7.0F,  8.0F,  9.0F },
    Point3{ 10.0F, 11.0F, 12.0F }
  };

  Vec3 col0 = t.get_column3( 0 );
  EXPECT_FLOAT_EQ( col0.x(), 1.0F );
  EXPECT_FLOAT_EQ( col0.y(), 2.0F );
  EXPECT_FLOAT_EQ( col0.z(), 3.0F );

  Vec3 col2 = t.get_column3( 2 );
  EXPECT_FLOAT_EQ( col2.x(), 7.0F );
  EXPECT_FLOAT_EQ( col2.y(), 8.0F );
  EXPECT_FLOAT_EQ( col2.z(), 9.0F );
}

TEST_F( Transform4Test, TransformComposition )
{
  Transform4 t1{ Transform4::identity() };
  t1.set_translation( Point3{ 1.0F, 0.0F, 0.0F } );

  Transform4 t2{ Transform4::identity() };
  t2.set_translation( Point3{ 0.0F, 1.0F, 0.0F } );

  Mat4 composed = t2 * t1;
  EXPECT_FLOAT_EQ( composed( 0, 3 ), 1.0F );
  EXPECT_FLOAT_EQ( composed( 1, 3 ), 1.0F );
  EXPECT_FLOAT_EQ( composed( 2, 3 ), 0.0F );
}

TEST_F( Transform4Test, InverseRoundtrip )
{
  Transform4 t{
    Vec3{ 1.0F, 0.0F, 0.0F },
    Vec3{ 0.0F, 1.0F, 0.0F },
    Vec3{ 0.0F, 0.0F, 1.0F },
    Point3{ 5.0F, 6.0F, 7.0F }
  };

  Transform4 inv    = inverse( t );
  Mat4       result = t * inv;
  EXPECT_TRUE( are_matrices_equal( result, Mat4::identity(), 1e-5F ) );
}

TEST_F( Transform4Test, NormalTransformation )
{
  Vec3 normal{ 0.0F, 1.0F, 0.0F };

  Transform4 t{ Transform4::identity() };
  t.set_translation( Point3{ 10.0F, 20.0F, 30.0F } );

  Vec3 transformed = transform_normal( normal, t );
  EXPECT_FLOAT_EQ( transformed.x(), 0.0F );
  EXPECT_FLOAT_EQ( transformed.y(), 1.0F );
  EXPECT_FLOAT_EQ( transformed.z(), 0.0F );
}

TEST_F( Transform4Test, NormalTransformationOperator )
{
  Vec3 normal{ 0.0F, 1.0F, 0.0F };

  Transform4 t{ Transform4::identity() };
  t.set_translation( Point3{ 10.0F, 20.0F, 30.0F } );

  Vec3 transformed = normal * t;
  EXPECT_FLOAT_EQ( transformed.x(), 0.0F );
  EXPECT_FLOAT_EQ( transformed.y(), 1.0F );
  EXPECT_FLOAT_EQ( transformed.z(), 0.0F );
}

TEST_F( Transform4Test, ScalingTransform )
{
  Transform4 scale{ 2.0F, 0.0F, 0.0F, 0.0F, 0.0F, 3.0F, 0.0F, 0.0F, 0.0F, 0.0F, 4.0F, 0.0F };

  Vec3 vec{ 1.0F, 1.0F, 1.0F };
  Vec3 scaled = scale * vec;
  EXPECT_FLOAT_EQ( scaled.x(), 2.0F );
  EXPECT_FLOAT_EQ( scaled.y(), 3.0F );
  EXPECT_FLOAT_EQ( scaled.z(), 4.0F );

  Point3 point{ 1.0F, 1.0F, 1.0F };
  Point3 scaled_point = scale * point;
  EXPECT_FLOAT_EQ( scaled_point.x(), 2.0F );
  EXPECT_FLOAT_EQ( scaled_point.y(), 3.0F );
  EXPECT_FLOAT_EQ( scaled_point.z(), 4.0F );
}

TEST_F( Transform4Test, MakeTranslation )
{
  Transform4 t = make_translation( Vec3{ 3.0F, 4.0F, 5.0F } );

  EXPECT_FLOAT_EQ( t( 0, 0 ), 1.0F );
  EXPECT_FLOAT_EQ( t( 1, 1 ), 1.0F );
  EXPECT_FLOAT_EQ( t( 2, 2 ), 1.0F );
  EXPECT_FLOAT_EQ( t( 0, 3 ), 3.0F );
  EXPECT_FLOAT_EQ( t( 1, 3 ), 4.0F );
  EXPECT_FLOAT_EQ( t( 2, 3 ), 5.0F );
  EXPECT_FLOAT_EQ( t( 3, 3 ), 1.0F );
  EXPECT_FLOAT_EQ( t( 3, 0 ), 0.0F );
}

TEST_F( Transform4Test, MakeTranslationApplyToPoint )
{
  Transform4 t     = make_translation( Vec3{ 1.0F, 2.0F, 3.0F } );
  Point3     point = t * Point3{ 0.0F, 0.0F, 0.0F };
  EXPECT_FLOAT_EQ( point.x(), 1.0F );
  EXPECT_FLOAT_EQ( point.y(), 2.0F );
  EXPECT_FLOAT_EQ( point.z(), 3.0F );
}

TEST_F( Transform4Test, MakeRotation4x4 )
{
  float      angle = linalg::pi / 2.0F;
  Transform4 t     = make_rotation4( angle, Vec3{ 0.0F, 0.0F, 1.0F } );

  Vec3 result = t * Vec3{ 1.0F, 0.0F, 0.0F };
  EXPECT_NEAR( result.x(), 0.0F, 1e-5F );
  EXPECT_NEAR( result.y(), 1.0F, 1e-5F );
  EXPECT_NEAR( result.z(), 0.0F, 1e-5F );

  EXPECT_FLOAT_EQ( t( 0, 3 ), 0.0F );
  EXPECT_FLOAT_EQ( t( 1, 3 ), 0.0F );
  EXPECT_FLOAT_EQ( t( 2, 3 ), 0.0F );
}

TEST_F( Transform4Test, MakeScaleVec3 )
{
  Transform4 t = make_scale( Vec3{ 2.0F, 3.0F, 4.0F } );

  EXPECT_FLOAT_EQ( t( 0, 0 ), 2.0F );
  EXPECT_FLOAT_EQ( t( 1, 1 ), 3.0F );
  EXPECT_FLOAT_EQ( t( 2, 2 ), 4.0F );
  EXPECT_FLOAT_EQ( t( 3, 3 ), 1.0F );
  EXPECT_FLOAT_EQ( t( 0, 1 ), 0.0F );
  EXPECT_FLOAT_EQ( t( 0, 3 ), 0.0F );
}

TEST_F( Transform4Test, MakeScaleApply )
{
  Transform4 t      = make_scale( Vec3{ 2.0F, 3.0F, 4.0F } );
  Point3     scaled = t * Point3{ 1.0F, 1.0F, 1.0F };
  EXPECT_FLOAT_EQ( scaled.x(), 2.0F );
  EXPECT_FLOAT_EQ( scaled.y(), 3.0F );
  EXPECT_FLOAT_EQ( scaled.z(), 4.0F );
}
