#pragma once

#include <exception>
#include <string>

#include "ErrorCode.h"

class AppError final : public std::exception {
public:
  AppError(ErrorCode code, std::string message);

  ErrorCode getCode() const;

  const char *what() const noexcept override;

private:
  ErrorCode m_code{ErrorCode::UnknownError};
  std::string m_message;
};