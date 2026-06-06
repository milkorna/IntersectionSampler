#pragma once

#include <string>

#include "Common/ErrorCode.h"

/**
 * @brief Stores error code and message
 */
class Status {
private:
  /**
   * @brief Creates status from error code and message
   *
   * @param[in] code Error code
   * @param[in] message Status message
   */
  explicit Status(ErrorCode code, std::string message);

public:
  /**
   * @brief Creates successful status
   *
   * @return Successful status
   */
  static Status ok();

  /**
   * @brief Creates error status
   *
   * @param[in] code Error code
   * @param[in] message Error message
   *
   * @return Error status
   */
  static Status error(ErrorCode code, std::string message);

  /**
   * @brief Checks if status is successful
   *
   * @return True if status is successful
   */
  bool isOk() const;

  /**
   * @brief Gets error code
   *
   * @return Error code
   */
  ErrorCode getCode() const;

  /**
   * @brief Gets status message
   *
   * @return Status message
   */
  const std::string &getMessage() const;

private:
  ErrorCode m_code{ErrorCode::Ok};
  std::string m_message;
};