#pragma once

enum class ErrorCode {
  Ok = 0,

  InvalidArguments,

  FailedToReadInputData,
  FailedToCreateOutputDirectory,
  FailedToOpenFile,

  ShapeTypeMismatch,

  InvalidGeometry,

  UnknownError
};