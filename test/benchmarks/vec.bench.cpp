#include "linalg/vec.hpp"
#include <benchmark/benchmark.h>

using namespace linalg;

static void bm_vec3_dot( benchmark::State& state )
{
  Vec3 a{ 1.0F, 2.0F, 3.0F };
  Vec3 b{ 4.0F, 5.0F, 6.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( dot( a, b ) );
  }
}
BENCHMARK( bm_vec3_dot );

static void bm_vec3_cross( benchmark::State& state )
{
  Vec3 a{ 1.0F, 2.0F, 3.0F };
  Vec3 b{ 4.0F, 5.0F, 6.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( cross( a, b ) );
  }
}
BENCHMARK( bm_vec3_cross );

static void bm_vec3_normalize( benchmark::State& state )
{
  Vec3 v{ 1.0F, 2.0F, 3.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( normalized( v ) );
  }
}
BENCHMARK( bm_vec3_normalize );

static void bm_vec3_magnitude( benchmark::State& state )
{
  Vec3 v{ 1.0F, 2.0F, 3.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( magnitude( v ) );
  }
}
BENCHMARK( bm_vec3_magnitude );

static void bm_vec3_addition( benchmark::State& state )
{
  Vec3 a{ 1.0F, 2.0F, 3.0F };
  Vec3 b{ 4.0F, 5.0F, 6.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( a + b );
  }
}
BENCHMARK( bm_vec3_addition );

static void bm_vec4_dot( benchmark::State& state )
{
  Vec4 a{ 1.0F, 2.0F, 3.0F, 4.0F };
  Vec4 b{ 5.0F, 6.0F, 7.0F, 8.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( dot( a, b ) );
  }
}
BENCHMARK( bm_vec4_dot );

static void bm_vec4_normalize( benchmark::State& state )
{
  Vec4 v{ 1.0F, 2.0F, 3.0F, 4.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( normalized( v ) );
  }
}
BENCHMARK( bm_vec4_normalize );
