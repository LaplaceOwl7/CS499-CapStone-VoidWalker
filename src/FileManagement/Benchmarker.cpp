#include "FileManagement/Benchmarker.hpp"
#include "ValidationTools/Err.hpp"
#include <filesystem>

#include <iomanip>


void Benchmarker::writeCSV(
    const SortTimingResults& t_results, 
    const std::string& t_filePath,
    const std::string& t_timestamp,
    std::size_t t_inputSize
) {

    std::ofstream file(t_filePath, std::ios::app);  // open in append mode

    if (!file.is_open()) {
        ErrLog err;
        err.genLogFile("Failed to Open Benchmark file ");
        return;
    }

    file.seekp(0, std::ios::end); // Begin at the beginning of the file
    
    if (file.tellp() == 0) { // If the file is at the beginning, print the template
        file << "Timestamp,InputSize,BubbleSort,MergeSort,QuickSort,StandardSort\n";
    }

    // Write the details acquired
    file << t_timestamp << ","
         << t_inputSize << ","
         << t_results.bubbleSortTime << ","
         << t_results.mergeSortTime  << ","
         << t_results.quickSortTime  << ","
         << t_results.standardSortTime << "\n";
}

/// @brief generates a timestamp for files
/// @return a string of the current time
std::string Benchmarker::genTimeStamp() {
    // Acquire the time
    const auto tp_utc{std::chrono::system_clock::now()};

    // Measure time and convert it to a string
    std::time_t t_timeToUTC = std::chrono::system_clock::to_time_t(tp_utc);
    std::ostringstream oss;
    oss << std::put_time(std::gmtime(&t_timeToUTC), "%Y-%m-%d %H:%M:%S");
    std::string t_time_str = oss.str();

    return t_time_str;

}

void Benchmarker::performBenchMark(
    std::vector<CourseData::Course> t_coursesToSort
) {

    Sorter<CourseData::Course> sorter;

    // Define the base file:
    std::filesystem::create_directories("data");
    static constexpr const char* benchmarkFileLocation = "data/time_results.csv";


    // Copy data for the vectors.
    std::vector<CourseData::Course> bubbleData = t_coursesToSort;
    std::vector<CourseData::Course> mergeData = t_coursesToSort;
    std::vector<CourseData::Course> quickData = t_coursesToSort;
    std::vector<CourseData::Course> standardData = t_coursesToSort;

    // Define the input size
    std::size_t t_inputSize = t_coursesToSort.size();

    // Intialize the Structure
    SortTimingResults results; 

    // Benchmark Bubble Sort
    // {}s let us freely define local scopes
    {
        Timer timer;
        timer.startTimer();

        sorter.bubbleSort(bubbleData);

        long long duration= timer.stopTimer();

        results.bubbleSortTime = timer.stopTimer();
    }

    // Benchmark Mergesort
    {
        Timer timer;
        timer.startTimer();

        sorter.mergeSort(mergeData);

        long long duration= timer.stopTimer();

        results.mergeSortTime = timer.stopTimer();
    }

    // Benchmark QuickSort
    {
        Timer timer;
        timer.startTimer();

        sorter.quickSort(quickData);

        long long duration= timer.stopTimer();

        results.quickSortTime = timer.stopTimer();
    }

    // Standard Sort
    {
        Timer timer;
        timer.startTimer();

        sorter.standardSort(standardData);

        long long duration= timer.stopTimer();

        results.standardSortTime = timer.stopTimer();
    }

    // Additional Sorters would be added here:
        // - Add new algorithm's class
        // - Add to sorter class
        // - Add to SortTimeResults structure

    // Deploy the results to the file
    Benchmarker benchmarker;

    writeCSV(
        results,
        benchmarkFileLocation,
        benchmarker.genTimeStamp(),
        t_inputSize
    );
}

void Benchmarker::printBenchmarkResults(
) const {
    const std::string benchmarkFilePath = "data/time_results.csv";
    std::ifstream file (benchmarkFilePath);

    // Check if the file is open:
    if (!file.is_open()) {
        ErrLog err;
        err.genLogFile("No Benchmark file found");
        return;
    }

    std::string line;
    std::string last_line;

    // Need to ignore header file
    while(std::getline(file,line)){
        if (!line.empty() && line.find("Timestamp") == std::string::npos){
            last_line = line;
        }
    }

    if (last_line.empty()){
        std::cout << "No benchmark entries found.\n";
        return;
    }

    // Begin to evaluate the benchmark fields
    std::stringstream ss(last_line);
    std::string timestamp, input_size, bubble, merge, quick, stdSort; // All the entires

    
    std::getline(ss, timestamp, ',');
    std::getline(ss, input_size, ',');
    std::getline(ss, bubble, ',');
    std::getline(ss, merge, ',');
    std::getline(ss, quick, ',');
    std::getline(ss, stdSort, ',');
    
    // Print the formatted table; nasty no matter what I do.
    std::cout << "================= Most Recent Benchmark =================\n";
    std::cout << "Timestamp:   " << timestamp << "\n";
    std::cout << "Input Size:  " << input_size << " elements\n\n";
    std::cout << std::left << std::setw(20) << "Algorithm"
              << std::right << std::setw(15) << "Time (microseconds)\n";
    std::cout << "-----------------------------------------------------\n";
    std::cout << std::left << std::setw(20) << "BubbleSort"
              << std::right << std::setw(15) << bubble << "\n";
    std::cout << std::left << std::setw(20) << "MergeSort"
              << std::right << std::setw(15) << merge << "\n";
    std::cout << std::left << std::setw(20) << "QuickSort"
              << std::right << std::setw(15) << quick << "\n";
    std::cout << std::left << std::setw(20) << "Standard Sort"
              << std::right << std::setw(15) << stdSort << "\n";
    std::cout << "=====================================================\n";


}

void Benchmarker::printMostOptimized() 
const {
    // Define path
    const std::string filePath = "data/time_results.csv";
    std::ifstream file(filePath);

    // This section is copy & pasted from printBenchmarkResults
        // Should be modularized:
    // Check if the file is open:
    if (!file.is_open()) {
        ErrLog err;
        err.genLogFile("No Benchmark file found");
        return;
    }

    std::string line;
    std::string last_line;

    // Need to ignore header file
    while(std::getline(file,line)){
        if (!line.empty() && line.find("Timestamp") == std::string::npos){
            last_line = line;
        }
    }

    if (last_line.empty()){
        std::cout << "No benchmark entries found.\n";
        return;
    }

    // Begin to evaluate the benchmark fields
    std::stringstream ss(last_line);
    std::string timestamp, input_size, bubble, merge, quick, stdSort; // All the entires

    
    std::getline(ss, timestamp, ',');
    std::getline(ss, input_size, ',');
    std::getline(ss, bubble, ',');
    std::getline(ss, merge, ',');
    std::getline(ss, quick, ',');
    std::getline(ss, stdSort, ',');

    // Convert times to integers; Rounding issues unlikely
    long long t_bubble = std::stoll(bubble);
    long long t_merge  = std::stoll(merge);
    long long t_quick  = std::stoll(quick);
    long long t_std    = std::stoll(stdSort);

    // What is the fastest var?
    long long fastest = std::min(
        {t_bubble, t_merge, t_quick, t_std}
    );

    std::string bestAlgo;

    if (fastest == t_bubble) bestAlgo = "BubbleSort";
    else if (fastest == t_merge) bestAlgo = "MergeSort";
    else if (fastest == t_quick) bestAlgo = "QuickSort";
    else bestAlgo = "Standard Sort";

    // Print results in a neat little menu
    std::cout << "========== Most Optimized Algorithm ==========\n";
    std::cout << "Timestamp: " << timestamp << "\n";
    std::cout << "Input Size: " << input_size << "\n\n";

    std::cout << "Fastest Algorithm: " << bestAlgo << "\n";
    std::cout << "Execution Time:    " << fastest << " microseconds\n";
    std::cout << "==============================================\n";
}

void Benchmarker::generateMarkdownReport() const {

    const std::string csvFile = "data/time_results.csv";
    const std::string mdFile  = "data/benchmark_report.md";

    std::ifstream file(csvFile);

    // Note: copy & pasted from bestAlgorithm:
        // Check if the file is open:
    if (!file.is_open()) {
        ErrLog err;
        err.genLogFile("No Benchmark file found");
        return;
    }

    std::string line;
    std::string last_line;

    // Need to ignore header file
    while(std::getline(file,line)){
        if (!line.empty() && line.find("Timestamp") == std::string::npos){
            last_line = line;
        }
    }

    if (last_line.empty()){
        std::cout << "No benchmark entries found.\n";
        return;
    }

    // Begin to evaluate the benchmark fields
    std::stringstream ss(last_line);
    std::string timestamp, input_size, bubble, merge, quick, stdSort; // All the entires

    
    std::getline(ss, timestamp, ',');
    std::getline(ss, input_size, ',');
    std::getline(ss, bubble, ',');
    std::getline(ss, merge, ',');
    std::getline(ss, quick, ',');
    std::getline(ss, stdSort, ',');

    // Convert times to integers; Rounding issues unlikely
    long long t_bubble = std::stoll(bubble);
    long long t_merge  = std::stoll(merge);
    long long t_quick  = std::stoll(quick);
    long long t_std    = std::stoll(stdSort);

    // What is the fastest var?
    long long fastest = std::min(
        {t_bubble, t_merge, t_quick, t_std}
    );

    std::string bestAlgo;

    if (fastest == t_bubble) bestAlgo = "BubbleSort";
    else if (fastest == t_merge) bestAlgo = "MergeSort";
    else if (fastest == t_quick) bestAlgo = "QuickSort";
    else bestAlgo = "Standard Sort";
    // 

    // Write Markdown file
    std::ofstream md(mdFile);
    if (!md.is_open()) {
        ErrLog err;
        err.genLogFile("Failed to Open Markdown report");
        return;
    }

    // NOTE: THE BELOW CODE IS AI-ASSISTED

    md << "# Benchmark Report — " << timestamp << "\n\n";
    md << "**Input Size:** " << input_size << " elements\n\n";
    md << "---\n\n";
    md << "## Algorithm Timings (microseconds)\n\n";
    md << "| Algorithm      | Time (microseconds) |\n";
    md << "|----------------|-----------|\n";
    md << "| BubbleSort     | " << t_bubble << " |\n";
    md << "| MergeSort      | " << t_merge  << " |\n";
    md << "| QuickSort      | " << t_quick  << " |\n";
    md << "| Standard Sort  | " << t_std    << " |\n\n";
    md << "---\n\n";
    md << "## Most Optimized Algorithm\n\n";
    md << "**" << bestAlgo << "** — *" << fastest << " µs*\n";

    // NOTE: THE ABOVE CODE IS AI-ASSISTED; Needed AI to make it look pretty.

    md.close();
    std::cout << "Markdown report generated: " << mdFile << "\n";
}


