#ifndef BENCHMARK_RECORD_HPP
#define BENCHMARK_RECORD_HPP

#include <string>

// Structure to export to a file

struct BenchmarkRecord {
    std::string timestamp;
    std::string algorithm;
    long long duration;
    std::size_t inputSize;
};

#endif
