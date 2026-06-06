#include "Status.h"

Status::Status(ErrorCode code, std::string message)
    : m_code(code), m_message(std::move(message)) {
}

Status Status::ok() {
  return Status{ErrorCode::Ok, ""};
}

Status Status::error(ErrorCode code, std::string message) {
  return Status{code, std::move(message)};
}

bool Status::isOk() const {
  return m_code == ErrorCode::Ok;
}

ErrorCode Status::getCode() const {
  return m_code;
}

const std::string &Status::getMessage() const {
  return m_message;
}
