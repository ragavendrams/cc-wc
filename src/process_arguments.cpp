#include "process_arguments.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace ccwc {

namespace {

bool is_valid_option(
    const std::string& option, const std::array<std::string, 6>& supported_options) {
    return (std::find(supported_options.begin(), supported_options.end(), option)
            != supported_options.end());
}

std::string read_from_stdin() {
    std::filesystem::path out_file_path = std::filesystem::temp_directory_path() / "output.txt";
    if (std::filesystem::exists(out_file_path))
        std::filesystem::remove(out_file_path);

    std::ofstream out_file(out_file_path.c_str());
    std::string line;
    while (std::getline(std::cin, line)) {
        out_file << line << std::endl;
    }

    return out_file_path.string();
}

void print_help_text() {
    const char* help_text =
        R"( Available options: 
                -c Counts number of bytes in the input file or stdin 
                -m Counts number of characters in the input file or stdin 
                -l Counts number of lines in the input file or stdin 
                -w Counts number of words in the input file or stdin 
                --help Prints this help text and ignores other options passed in 
            
            Example usage: 
                ccwc -c file.txt file2.txt 
                ccwc file.txt
                ccwc <stdin> <CTRL-D to stop entering input>
                echo 'temp' | ccwc -c 
                )";

    std::cout << help_text << std::endl;
}
}  // namespace

std::tuple<Options, Files, bool> process_arguments(int argc, char* argv[]) {
    std::array<std::string, 6> supported_options{"-c", "-l", "-m", "-w", "--help"};
    std::vector<std::string> options;
    std::vector<std::string> files;
    std::vector<std::string> arguments;

    for (int i = 1; i < argc; ++i) {
        arguments.emplace_back(argv[i]);
    }

    // Parse options and files from arguments
    for (int i = 0; i < arguments.size(); ++i) {
        if (is_valid_option(arguments[i], supported_options)) {
            if (arguments[i] == std::string("--help")) {
                print_help_text();
                exit(0);
            }
            options.push_back(arguments[i]);
        }
        else if (std::filesystem::is_regular_file(arguments[i])) {
            files.push_back(arguments[i]);
        }
        else {
            throw std::runtime_error("Error: File not found at " + arguments[i]);
        }
    }

    // Default options
    if (options.size() == 0) {
        options.insert(options.begin(), {std::string("-l"), std::string("-w"), std::string("-c")});
    }

    // Use stdin as default stream
    bool file_read_from_stdin = false;
    if (files.size() == 0) {
        std::string file_path = read_from_stdin();
        files.push_back(file_path);
        file_read_from_stdin = true;
    }

    return std::tuple(options, files, file_read_from_stdin);
}

}  // namespace ccwc
