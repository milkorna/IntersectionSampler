#pragma once

namespace constants {

inline constexpr double Pi = 3.14159265358979323846;

// General tolerance for comparing coordinates / points.
inline constexpr double PointTolerance = 1.0e-6;

// Tolerance for detecting zero-length vectors / degenerate geometry.
inline constexpr double MinLength = 1.0e-12;

// Tolerance for floating-point divisions and denominator checks.
inline constexpr double ComputationTolerance = 1.0e-9;

} // namespace constants