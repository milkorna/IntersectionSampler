#pragma once

#include <string>

#include "Common/ErrorCode.h"

class Status {

  explicit Status(ErrorCode code, std::string message);

public:
  static Status ok();

  static Status error(ErrorCode code, std::string message);

  bool isOk() const;

  ErrorCode getCode() const;

  const std::string &getMessage() const;

private:
  ErrorCode m_code{ErrorCode::Ok};
  std::string m_message;
};