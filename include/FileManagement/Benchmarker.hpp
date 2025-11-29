#ifndef BENCHMARK_WRITER_HPP
#define BENCHMARK_WRITER_HPP

#include <fstream>
#include <string>
#include "Sorters/Sorter.hpp"   // for SortTimingResults

class Benchmarker {
public:
    /// @brief a helper function that writes a writes the CSV for benchmarking analysis
    /// @param results a structure to manipulated (this is the 'return`)
    /// @param filePath a filepath of the CSV to be created
    /// @param timestamp the timestamp to add to the file
    /// @param t_inputSize The size of the vector inputted
    static void writeCSV(
        const SortTimingResults& results, 
        const std::string& filePath,
        const std::string& timestamp,
        const std::size_t t_inputSize
    );

    /// @brief creates a timestamp
    /// @return returns a string that is added to the file
    std::string genTimeStamp();

    /// @brief Runs benchmarks on all algorithms, measures, and inputs the details into a CSV.
    /// @param t_coursesToSort Course vector to sort
    void performBenchMark(
        std::vector<CourseData::Course> t_coursesToSort
    );
   /// @brief  prints all benchmark results to std::cout; here for ease of ouse
   void printBenchmarkResults() const;

   /// @brief prints the most optimized algorithm into std::cout
   void printMostOptimized() const;
   /// @brief creates a markdown report into the project's directory
   void generateMarkdownReport() const;

};

#endif
