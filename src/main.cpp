#include <iostream>

#include "SamplingPipeline.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <input_file> <output_directory>\n";
    return static_cast<int>(ErrorCode::InvalidArguments);
  }

  const SamplingPipeline pipeline{argv[1], argv[2]};
  const Status status = pipeline.run();

  if (!status.isOk()) {
    std::cerr << "Error: " << status.getMessage() << '\n';
    return static_cast<int>(status.getCode());
  }

  return static_cast<int>(ErrorCode::Ok);
}