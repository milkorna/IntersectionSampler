#include <exception>
#include <iostream>

#include "SamplingPipeline.h"

int main(int argc, char *argv[]) {
  try {
    if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " <input_file> <output_directory>\n";
      return 1;
    }

    const SamplingPipeline application{argv[1], argv[2]};
    application.run();

  } catch (const std::exception &error) {
    std::cerr << "Error: " << error.what() << '\n';
    return 1;
  }

  return 0;
}