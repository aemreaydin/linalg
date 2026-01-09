# Linalg

A high-performance, header-only C++23 linear algebra library designed for graphics, physics, and general-purpose mathematics.

## Features

- **Header-Only:** Easy to integrate, just add the `include` directory to your project.
- **Modern C++:** Built with C++23, strictly enforcing types via **Concepts** and leveraging `constexpr` for compile-time safety and performance.
- **SIMD Optimized:** (WIP) Support for AVX2, SSE4.1, and NEON optimizations.
- **Comprehensive Math Suite:**
  - **Vectors:** `Vec2`, `Vec3`, `Vec4` (float) and `IVec3`, `IVec4` (int).
  - **Matrices:** `Mat3`, `Mat4` with support for common operations like inverse and determinant.
  - **Quaternions:** For robust rotation representation.
  - **Transforms:** 4x4 Transformation matrices specifically for 3D graphics.
  - **Geometry:** `Plane` and `Line` primitives with intersection and distance functions.
- **Strictly Tested:** Extensive unit test suite using GoogleTest.
- **Benchmarks:** Built-in performance tracking with Google Benchmark.

## Requirements

- **C++23 Compiler:** GCC 14+ or Clang 17+ recommended.
- **CMake:** Version 3.28 or higher.
- **Task (optional):** [go-task](https://taskfile.dev/) for simplified build/test/bench workflows.

## Usage

Since it is a header-only library, you can simply include the headers you need:

```cpp
#include <linalg/vec.hpp>
#include <linalg/mat4.hpp>

using namespace linalg;

void example() {
    Vec3 position{1.0f, 0.0f, 0.0f};
    Vec3 direction{0.0f, 1.0f, 0.0f};

    // Vector arithmetic
    Vec3 result = position + direction;

    // Dot and Cross products
    float d = dot(position, direction);
    Vec3 n = cross(position, direction);

    // Matrices
    Mat4 identity = Mat4::identity();
}
```

## Development

The project uses `go-task` to manage common development tasks.

### Running Tests

```bash
go-task test
```

### Running Benchmarks

```bash
go-task bench
```

### Static Analysis (clang-tidy)

```bash
go-task tidy
```

### Code Formatting

```bash
go-task format
```
