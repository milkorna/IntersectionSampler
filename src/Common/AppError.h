#pragma once

#include <exception>
#include <string>

#include "ErrorCode.h"

/**
 * @brief Exception type with error code
 */
class AppError final : public std::exception {
public:
  /**
   * @brief Creates an application error
   *
   * @param[in] code Error code
   * @param[in] message Error message
   */
  AppError(ErrorCode code, std::string message);

  /**
   * @brief Gets the error code
   *
   * @return Error code
   */
  ErrorCode getCode() const;

  /**
   * @brief Gets the error message
   *
   * @return Error message as C string
   */
  const char *what() const noexcept override;

private:
  ErrorCode m_code{ErrorCode::UnknownError};
  std::string m_message;
};