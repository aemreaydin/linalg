#include "linalg/mat3.hpp"
#include "linalg/mat4.hpp"
#include "linalg/transform.hpp"
#include <benchmark/benchmark.h>

using namespace linalg;

static void bm_mat3_multiply( benchmark::State& state )
{
  Mat3 a{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F };
  Mat3 b{ 9.0F, 8.0F, 7.0F, 6.0F, 5.0F, 4.0F, 3.0F, 2.0F, 1.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( a * b );
  }
}
BENCHMARK( bm_mat3_multiply );

static void bm_mat3_determinant( benchmark::State& state )
{
  Mat3 a{ 1.0F, 2.0F, 3.0F, 0.0F, 4.0F, 5.0F, 1.0F, 0.0F, 6.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( determinant( a ) );
  }
}
BENCHMARK( bm_mat3_determinant );

static void bm_mat3_inverse( benchmark::State& state )
{
  Mat3 a{ 1.0F, 2.0F, 3.0F, 0.0F, 4.0F, 5.0F, 1.0F, 0.0F, 6.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( inverse( a ) );
  }
}
BENCHMARK( bm_mat3_inverse );

static void bm_mat3_transpose( benchmark::State& state )
{
  Mat3 a{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( transpose( a ) );
  }
}
BENCHMARK( bm_mat3_transpose );

static void bm_mat3_times_vec3( benchmark::State& state )
{
  Mat3 m{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F };
  Vec3 v{ 1.0F, 2.0F, 3.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( m * v );
  }
}
BENCHMARK( bm_mat3_times_vec3 );

static void bm_mat4_multiply( benchmark::State& state )
{
  Mat4 a{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F, 13.0F, 14.0F, 15.0F, 16.0F };
  Mat4 b{ 16.0F, 15.0F, 14.0F, 13.0F, 12.0F, 11.0F, 10.0F, 9.0F, 8.0F, 7.0F, 6.0F, 5.0F, 4.0F, 3.0F, 2.0F, 1.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( a * b );
  }
}
BENCHMARK( bm_mat4_multiply );

static void bm_mat4_inverse( benchmark::State& state )
{
  Mat4 a{ 1.0F, 0.0F, 2.0F, 1.0F, 0.0F, 1.0F, 0.0F, 1.0F, 2.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( inverse( a ) );
  }
}
BENCHMARK( bm_mat4_inverse );

static void bm_mat4_transpose( benchmark::State& state )
{
  Mat4 a{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F, 13.0F, 14.0F, 15.0F, 16.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( transpose( a ) );
  }
}
BENCHMARK( bm_mat4_transpose );

static void bm_mat4_times_vec4( benchmark::State& state )
{
  Mat4 m{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F, 13.0F, 14.0F, 15.0F, 16.0F };
  Vec4 v{ 1.0F, 2.0F, 3.0F, 4.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( m * v );
  }
}
BENCHMARK( bm_mat4_times_vec4 );

static void bm_transform4_times_point3( benchmark::State& state )
{
  Transform4 t{ 1.0F, 0.0F, 0.0F, 5.0F, 0.0F, 1.0F, 0.0F, 6.0F, 0.0F, 0.0F, 1.0F, 7.0F };
  Point3     p{ 1.0F, 2.0F, 3.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( t * p );
  }
}
BENCHMARK( bm_transform4_times_point3 );

static void bm_transform4_times_vec3( benchmark::State& state )
{
  Transform4 t{ 1.0F, 0.0F, 0.0F, 5.0F, 0.0F, 1.0F, 0.0F, 6.0F, 0.0F, 0.0F, 1.0F, 7.0F };
  Vec3       v{ 1.0F, 2.0F, 3.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( t * v );
  }
}
BENCHMARK( bm_transform4_times_vec3 );

static void bm_transform4_inverse( benchmark::State& state )
{
  Transform4 t{ 1.0F, 0.0F, 0.0F, 5.0F, 0.0F, 1.0F, 0.0F, 6.0F, 0.0F, 0.0F, 1.0F, 7.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( inverse( t ) );
  }
}
BENCHMARK( bm_transform4_inverse );
