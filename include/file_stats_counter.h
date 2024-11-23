#ifndef FILE_STATS_COUNTER_H
#define FILE_STATS_COUNTER_H

#include <string>
#include <vector>

namespace ccwc {

class FileStatsCounter {
  public:
    FileStatsCounter(const std::vector<std::string>& options, const std::vector<std::string>& files)
      : m_files(files), m_options(options) {}

    /// @brief Calculates the number of bytes / lines / words / chars as specified in the options
    /// for the list of files
    /// @param file_read_from_stdin : Indicates if input was read from stdin. Output file name is
    /// left empty in this case.
    /// @return A string with the output results for all files.
    std::string calculate_counts(bool file_read_from_stdin);

  private:
    std::uint64_t calculate_num_bytes(const std::string& file_path);
    std::uint64_t calculate_num_lines(const std::string& file_path);
    std::uint64_t calculate_num_words(const std::string& file_path);
    std::uint64_t calculate_num_chars(const std::string& file_path);
    std::string process_option(const std::string& option, const std::string& file);

    std::vector<std::string> m_options;
    std::vector<std::string> m_files;
};

}  // namespace ccwc

#endif