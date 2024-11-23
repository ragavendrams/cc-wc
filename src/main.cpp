#include <fstream>
#include <iostream>

#include "file_stats_counter.h"
#include "process_arguments.h"

int main(int argc, char* argv[]) {
    auto [options, files, file_read_from_stdin] = ccwc::process_arguments(argc, argv);

    ccwc::FileStatsCounter counter(options, files);
    std::cout << counter.calculate_counts(file_read_from_stdin);

    return 0;
}