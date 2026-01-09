#pragma once
#include "linalg/constants.hpp"
#include "linalg/mat.hpp"

template<typename T, size_t N>
static bool are_matrices_equal(
  const linalg::Mat<T, N, N>& mat1, const linalg::Mat<T, N, N>& mat2, float tol = linalg::epsilon )
{
  for ( auto i = 0; i != N; ++i )
  {
    for ( auto j = 0; j != N; ++j )
    {
      if ( std::fabs( mat1[i][j] - mat2[i][j] ) > tol )
      {
        return false;
      }
    }
  }
  return true;
}

template<typename T, size_t N>
static bool are_vectors_equal(
  const linalg::Vec<T, N>& vec1, const linalg::Vec<T, N>& vec2, float tol = linalg::epsilon )
{
  for ( auto i = 0; i != N; ++i )
  {
    if ( std::fabs( vec1[i] - vec2[i] ) > tol )
    {
      return false;
    }
  }
  return true;
}
