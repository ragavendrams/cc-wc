#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "file_stats_counter.h"
#include "process_arguments.h"

namespace {
std::vector<char*> create_argv(const std::vector<std::string>& arguments) {
    std::vector<char*> argv;
    for (const auto& arg : arguments)
        argv.push_back((char*)arg.data());
    argv.push_back(nullptr);

    return argv;
}
}  // namespace

TEST_CASE("process_arguments() with no extra arguments", "[ccwc][no_arguments]") {
    // Simulate input for stdin
    std::istringstream simulated_input("aaaa\nbbbb\nééééé");
    std::cin.rdbuf(simulated_input.rdbuf());

    std::vector<char*> argv = create_argv({"ccwc"});
    auto [options, files, read_from_stdin] = ccwc::process_arguments(argv.size() - 1, argv.data());

    std::cin.rdbuf(nullptr);

    CHECK(options.size() == 3);
    CHECK(files.size() == 1);  // cin redirected to file internally
    CHECK(read_from_stdin);
}

TEST_CASE("process_arguments() with one option and one file",
          "[ccwc][process_arguments_one_option_one_file]") {
    std::string option = GENERATE("-w", "-c", "-l", "-m");
    std::vector<char*> argv = create_argv({"ccwc", option, "test.txt"});
    auto [options, files, read_from_stdin] = ccwc::process_arguments(argv.size() - 1, argv.data());

    CHECK(options.size() == 1);
    CHECK(files.size() == 1);
    CHECK_FALSE(read_from_stdin);
}

TEST_CASE("process_arguments() with multiple options and one file",
          "[ccwc][process_arguments_multiple_options_one_file]") {
    std::vector<char*> argv = create_argv({"ccwc", "-w", "-c", "test.txt"});
    auto [options, files, read_from_stdin] = ccwc::process_arguments(argv.size() - 1, argv.data());

    CHECK(options.size() == 2);
    CHECK(files.size() == 1);
    CHECK_FALSE(read_from_stdin);
}

TEST_CASE("process_arguments() with one option and multiple files",
          "[ccwc][process_arguments_one_option_multiple_files]") {
    std::vector<char*> argv = create_argv({"ccwc", "-w", "test.txt", "test2.txt"});
    auto [options, files, read_from_stdin] = ccwc::process_arguments(argv.size() - 1, argv.data());

    CHECK(options.size() == 1);
    CHECK(files.size() == 2);
    CHECK_FALSE(read_from_stdin);
}

TEST_CASE("process_arguments() with multiple options and multiple files",
          "[ccwc][process_arguments_multiple_options_multiple_files]") {
    std::vector<char*> argv = create_argv({"ccwc", "-w", "-m", "test.txt", "test2.txt"});
    auto [options, files, read_from_stdin] = ccwc::process_arguments(argv.size() - 1, argv.data());

    CHECK(options.size() == 2);
    CHECK(files.size() == 2);
    CHECK_FALSE(read_from_stdin);
}

TEST_CASE("FileStatsCounter::calculate_counts() with -w option and one file",
          "[ccwc][FileStatsCounter_w_option_one_file]") {
    std::vector<std::string> options{"-w"};
    std::vector<std::string> files{"test2.txt"};

    ccwc::FileStatsCounter counter(options, files);
    std::string expected_output("58164 test2.txt\n");
    CHECK(counter.calculate_counts(false) == expected_output);
}

TEST_CASE("FileStatsCounter::calculate_counts() with -m option and one file",
          "[ccwc][FileStatsCounter_m_option_one_file]") {
    std::vector<std::string> options{"-m"};
    std::vector<std::string> files{"test2.txt"};

    ccwc::FileStatsCounter counter(options, files);
    std::string expected_output("339292 test2.txt\n");
    CHECK(counter.calculate_counts(false) == expected_output);
}
TEST_CASE("FileStatsCounter::calculate_counts() with -c option and one file",
          "[ccwc][FileStatsCounter_c_option_one_file]") {
    std::vector<std::string> options{"-c"};
    std::vector<std::string> files{"test2.txt"};

    ccwc::FileStatsCounter counter(options, files);
    std::string expected_output("342190 test2.txt\n");
    CHECK(counter.calculate_counts(false) == expected_output);
}

TEST_CASE("FileStatsCounter::calculate_counts() with -l option and one file",
          "[ccwc][FileStatsCounter_l_option_one_file]") {
    std::vector<std::string> options{"-l"};
    std::vector<std::string> files{"test2.txt"};

    ccwc::FileStatsCounter counter(options, files);
    std::string expected_output("7145 test2.txt\n");
    CHECK(counter.calculate_counts(false) == expected_output);
}

TEST_CASE("FileStatsCounter::calculate_counts() with multiple options and multiple files",
          "[ccwc][FileStatsCounter_l_option_one_file]") {
    std::vector<std::string> options{"-l", "-c", "-m", "-w"};
    std::vector<std::string> files{"test.txt", "test2.txt"};

    ccwc::FileStatsCounter counter(options, files);
    std::string expected_output("8 42 42 8 test.txt\n7145 342190 339292 58164 test2.txt\n");
    CHECK(counter.calculate_counts(false) == expected_output);
}
