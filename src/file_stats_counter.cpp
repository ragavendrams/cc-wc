#include "file_stats_counter.h"

#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

namespace ccwc {

std::uint64_t FileStatsCounter::calculate_num_bytes(const std::string& file_path) {
    std::ifstream file_stream(file_path);
    file_stream.seekg(0, std::ios_base::end);
    std::uint64_t num_bytes = file_stream.tellg();
    file_stream.close();
    return num_bytes;
}

std::uint64_t FileStatsCounter::calculate_num_lines(const std::string& file_path) {
    std::ifstream file_stream(file_path);
    std::string line;
    std::uint16_t num_lines = 0;
    while (std::getline(file_stream, line)) {
        ++num_lines;
    }
    file_stream.close();
    return num_lines;
}

std::uint64_t FileStatsCounter::calculate_num_words(const std::string& file_path) {
    std::ifstream file_stream(file_path);
    std::string word;
    std::uint16_t num_words = 0;
    while (file_stream >> word) {
        ++num_words;
    }
    file_stream.close();
    return num_words;
}

std::uint64_t FileStatsCounter::calculate_num_chars(const std::string& file_path) {
    std::wifstream file_stream(file_path, std::ios::binary);
    // Assume locale/encoding is C.UTF-8
    // For ASCII and UTF-8 encoded files, char count will be accurate.
    file_stream.imbue(std::locale("C.UTF-8"));
    wchar_t ch;
    std::uint64_t num_chars = 0;
    while (file_stream.get(ch)) {
        ++num_chars;
    }
    file_stream.close();
    return num_chars;
}

std::string FileStatsCounter::process_option(const std::string& option, const std::string& file) {
    std::string file_output;

    if (option == "-c") {
        file_output += std::to_string(calculate_num_bytes(file));
        file_output += " ";
    }
    else if (option == "-l") {
        file_output += std::to_string(calculate_num_lines(file));
        file_output += " ";
    }
    else if (option == "-w") {
        file_output += std::to_string(calculate_num_words(file));
        file_output += " ";
    }
    else if (option == "-m") {
        file_output += std::to_string(calculate_num_chars(file));
        file_output += " ";
    }
    else {
        std::runtime_error("Unsupported options");
    }

    return file_output;
}

std::string FileStatsCounter::calculate_counts(bool file_read_from_stdin) {
    std::string output_counts;

    for (const std::string& file : m_files) {
        for (const std::string& option : m_options) {
            output_counts += process_option(option, file);
        }
        if (!file_read_from_stdin)
            output_counts += file;
        output_counts += '\n';
    }

    return output_counts;
}

}  // namespace ccwc
