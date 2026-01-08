#include "mirage_math/mat3.hpp"
#include "mirage_math/mat4.hpp"
#include "mirage_math/transform.hpp"
#include <benchmark/benchmark.h>

using namespace Mirage::Math;

static void BM_Mat3Multiply( benchmark::State& state )
{
  Mat3 a{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F };
  Mat3 b{ 9.0F, 8.0F, 7.0F, 6.0F, 5.0F, 4.0F, 3.0F, 2.0F, 1.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( a * b );
  }
}
BENCHMARK( BM_Mat3Multiply );

static void BM_Mat3Determinant( benchmark::State& state )
{
  Mat3 a{ 1.0F, 2.0F, 3.0F, 0.0F, 4.0F, 5.0F, 1.0F, 0.0F, 6.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( determinant( a ) );
  }
}
BENCHMARK( BM_Mat3Determinant );

static void BM_Mat3Inverse( benchmark::State& state )
{
  Mat3 a{ 1.0F, 2.0F, 3.0F, 0.0F, 4.0F, 5.0F, 1.0F, 0.0F, 6.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( inverse( a ) );
  }
}
BENCHMARK( BM_Mat3Inverse );

static void BM_Mat3Transpose( benchmark::State& state )
{
  Mat3 a{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( transpose( a ) );
  }
}
BENCHMARK( BM_Mat3Transpose );

static void BM_Mat3TimesVec3( benchmark::State& state )
{
  Mat3 m{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F };
  Vec3 v{ 1.0F, 2.0F, 3.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( m * v );
  }
}
BENCHMARK( BM_Mat3TimesVec3 );

static void BM_Mat4Multiply( benchmark::State& state )
{
  Mat4 a{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F, 13.0F, 14.0F, 15.0F, 16.0F };
  Mat4 b{ 16.0F, 15.0F, 14.0F, 13.0F, 12.0F, 11.0F, 10.0F, 9.0F, 8.0F, 7.0F, 6.0F, 5.0F, 4.0F, 3.0F, 2.0F, 1.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( a * b );
  }
}
BENCHMARK( BM_Mat4Multiply );

static void BM_Mat4Inverse( benchmark::State& state )
{
  Mat4 a{ 1.0F, 0.0F, 2.0F, 1.0F, 0.0F, 1.0F, 0.0F, 1.0F, 2.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( inverse( a ) );
  }
}
BENCHMARK( BM_Mat4Inverse );

static void BM_Mat4Transpose( benchmark::State& state )
{
  Mat4 a{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F, 13.0F, 14.0F, 15.0F, 16.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( transpose( a ) );
  }
}
BENCHMARK( BM_Mat4Transpose );

static void BM_Mat4TimesVec4( benchmark::State& state )
{
  Mat4 m{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F, 10.0F, 11.0F, 12.0F, 13.0F, 14.0F, 15.0F, 16.0F };
  Vec4 v{ 1.0F, 2.0F, 3.0F, 4.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( m * v );
  }
}
BENCHMARK( BM_Mat4TimesVec4 );

static void BM_Transform4TimesPoint3( benchmark::State& state )
{
  Transform4 t{ 1.0F, 0.0F, 0.0F, 5.0F, 0.0F, 1.0F, 0.0F, 6.0F, 0.0F, 0.0F, 1.0F, 7.0F };
  Point3     p{ 1.0F, 2.0F, 3.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( t * p );
  }
}
BENCHMARK( BM_Transform4TimesPoint3 );

static void BM_Transform4TimesVec3( benchmark::State& state )
{
  Transform4 t{ 1.0F, 0.0F, 0.0F, 5.0F, 0.0F, 1.0F, 0.0F, 6.0F, 0.0F, 0.0F, 1.0F, 7.0F };
  Vec3       v{ 1.0F, 2.0F, 3.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( t * v );
  }
}
BENCHMARK( BM_Transform4TimesVec3 );

static void BM_Transform4Inverse( benchmark::State& state )
{
  Transform4 t{ 1.0F, 0.0F, 0.0F, 5.0F, 0.0F, 1.0F, 0.0F, 6.0F, 0.0F, 0.0F, 1.0F, 7.0F };
  for ( auto _ : state )
  {
    benchmark::DoNotOptimize( inverse( t ) );
  }
}
BENCHMARK( BM_Transform4Inverse );
