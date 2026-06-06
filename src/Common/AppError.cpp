#include "AppError.h"

#include <string>
#include <utility>

AppError::AppError(ErrorCode code, std::string message)
    : m_code(code), m_message(std::move(message)) {
}

ErrorCode AppError::getCode() const {
  return m_code;
}

const char *AppError::what() const noexcept {
  return m_message.c_str();
}
