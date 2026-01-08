#include "mirage_math/vec.hpp"
#include <benchmark/benchmark.h>

using namespace Mirage::Math;

static void BM_Vec3Dot( benchmark::State& state )
{
  Vec3 a{ 1.0F, 2.0F, 3.0F };
  Vec3 b{ 4.0F, 5.0F, 6.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( dot( a, b ) );
  }
}
BENCHMARK( BM_Vec3Dot );

static void BM_Vec3Cross( benchmark::State& state )
{
  Vec3 a{ 1.0F, 2.0F, 3.0F };
  Vec3 b{ 4.0F, 5.0F, 6.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( cross( a, b ) );
  }
}
BENCHMARK( BM_Vec3Cross );

static void BM_Vec3Normalize( benchmark::State& state )
{
  Vec3 v{ 1.0F, 2.0F, 3.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( normalized( v ) );
  }
}
BENCHMARK( BM_Vec3Normalize );

static void BM_Vec3Magnitude( benchmark::State& state )
{
  Vec3 v{ 1.0F, 2.0F, 3.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( magnitude( v ) );
  }
}
BENCHMARK( BM_Vec3Magnitude );

static void BM_Vec3Addition( benchmark::State& state )
{
  Vec3 a{ 1.0F, 2.0F, 3.0F };
  Vec3 b{ 4.0F, 5.0F, 6.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( a + b );
  }
}
BENCHMARK( BM_Vec3Addition );

static void BM_Vec4Dot( benchmark::State& state )
{
  Vec4 a{ 1.0F, 2.0F, 3.0F, 4.0F };
  Vec4 b{ 5.0F, 6.0F, 7.0F, 8.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( dot( a, b ) );
  }
}
BENCHMARK( BM_Vec4Dot );

static void BM_Vec4Normalize( benchmark::State& state )
{
  Vec4 v{ 1.0F, 2.0F, 3.0F, 4.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( normalized( v ) );
  }
}
BENCHMARK( BM_Vec4Normalize );
