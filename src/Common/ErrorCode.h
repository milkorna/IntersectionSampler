#pragma once

/**
 * @brief Error codes
 */
enum class ErrorCode {
  /**
   * @brief No error
   */
  Ok = 0,

  /**
   * @brief Invalid arguments
   */
  InvalidArguments,

  /**
   * @brief Failed to read input data
   */
  FailedToReadInputData,

  /**
   * @brief Failed to open file
   */
  FailedToOpenFile,

  /**
   * @brief Shape input type does not match requested shape
   */
  ShapeTypeMismatch,

  /**
   * @brief Invalid or degenerate geometry
   */
  InvalidGeometry,

  /**
   * @brief Unknown error
   */
  UnknownError
};