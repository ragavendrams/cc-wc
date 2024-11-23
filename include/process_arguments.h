#ifndef PROCESS_ARGUMENTS_H
#define PROCESS_ARGUMENTS_H

#include <string>
#include <tuple>
#include <vector>

namespace ccwc {

using Options = std::vector<std::string>;
using Files = std::vector<std::string>;

std::tuple<Options, Files, bool> process_arguments(int argc, char* argv[]);

}  // namespace ccwc

#endif