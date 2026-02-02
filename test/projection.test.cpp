#include "linalg/projection.hpp"
#include "linalg/constants.hpp"
#include "test_utils.hpp"
#include <cmath>
#include <gtest/gtest.h>

using namespace linalg;

class ProjectionTest : public ::testing::Test
{
protected:
  void SetUp() override {}
};

TEST_F( ProjectionTest, LookAtIdentity )
{
  Vec3 eye{ 0.0F, 0.0F, 0.0F };
  Vec3 center{ 0.0F, 0.0F, -1.0F };
  Vec3 up{ 0.0F, 1.0F, 0.0F };
  Mat4 view = look_at( eye, center, up );

  EXPECT_FLOAT_EQ( view( 0, 0 ), 1.0F );
  EXPECT_FLOAT_EQ( view( 1, 1 ), 1.0F );
  EXPECT_FLOAT_EQ( view( 2, 2 ), 1.0F );
  EXPECT_FLOAT_EQ( view( 3, 3 ), 1.0F );
  EXPECT_FLOAT_EQ( view( 0, 3 ), 0.0F );
  EXPECT_FLOAT_EQ( view( 1, 3 ), 0.0F );
  EXPECT_FLOAT_EQ( view( 2, 3 ), 0.0F );
}

TEST_F( ProjectionTest, LookAtTranslation )
{
  Vec3 eye{ 0.0F, 0.0F, 5.0F };
  Vec3 center{ 0.0F, 0.0F, 0.0F };
  Vec3 up{ 0.0F, 1.0F, 0.0F };
  Mat4 view = look_at( eye, center, up );

  EXPECT_FLOAT_EQ( view( 2, 3 ), -5.0F );
}

TEST_F( ProjectionTest, PerspectiveBasic )
{
  float fov    = pi / 2.0F;
  float aspect = 1.0F;
  float near_p = 0.1F;
  float far_p  = 100.0F;
  Mat4  proj   = perspective( fov, aspect, near_p, far_p );

  EXPECT_FLOAT_EQ( proj( 0, 0 ), 1.0F );
  EXPECT_FLOAT_EQ( proj( 1, 1 ), 1.0F );
  EXPECT_FLOAT_EQ( proj( 3, 0 ), 0.0F );
  EXPECT_FLOAT_EQ( proj( 3, 1 ), 0.0F );
  EXPECT_FLOAT_EQ( proj( 3, 2 ), -1.0F );
  EXPECT_FLOAT_EQ( proj( 3, 3 ), 0.0F );
}

TEST_F( ProjectionTest, PerspectiveDepthRange )
{
  float near_p = 1.0F;
  float far_p  = 10.0F;
  Mat4  proj   = perspective( pi / 2.0F, 1.0F, near_p, far_p );

  Vec4 near_pt{ 0.0F, 0.0F, -near_p, 1.0F };
  Vec4 near_clip = proj * near_pt;
  EXPECT_NEAR( near_clip.z() / near_clip.w(), 0.0F, 1e-5F );

  Vec4 far_pt{ 0.0F, 0.0F, -far_p, 1.0F };
  Vec4 far_clip = proj * far_pt;
  EXPECT_NEAR( far_clip.z() / far_clip.w(), 1.0F, 1e-5F );
}

TEST_F( ProjectionTest, OrthoBasic )
{
  Mat4 proj = ortho( -1.0F, 1.0F, -1.0F, 1.0F, 0.1F, 100.0F );

  EXPECT_FLOAT_EQ( proj( 0, 0 ), 1.0F );
  EXPECT_FLOAT_EQ( proj( 1, 1 ), 1.0F );
  EXPECT_FLOAT_EQ( proj( 3, 0 ), 0.0F );
  EXPECT_FLOAT_EQ( proj( 3, 1 ), 0.0F );
  EXPECT_FLOAT_EQ( proj( 3, 2 ), 0.0F );
  EXPECT_FLOAT_EQ( proj( 3, 3 ), 1.0F );
}

TEST_F( ProjectionTest, OrthoDepthRange )
{
  float near_p = 1.0F;
  float far_p  = 10.0F;
  Mat4  proj   = ortho( -1.0F, 1.0F, -1.0F, 1.0F, near_p, far_p );

  Vec4 near_pt{ 0.0F, 0.0F, -near_p, 1.0F };
  Vec4 near_clip = proj * near_pt;
  EXPECT_NEAR( near_clip.z(), 0.0F, 1e-5F );

  Vec4 far_pt{ 0.0F, 0.0F, -far_p, 1.0F };
  Vec4 far_clip = proj * far_pt;
  EXPECT_NEAR( far_clip.z(), 1.0F, 1e-5F );
}
