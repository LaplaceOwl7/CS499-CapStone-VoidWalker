#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <filesystem>

#include "ValidationTools/Err.hpp"

/// @brief generates a timestamp for files
/// @return a string of the current time
std::string ErrLog::genTimeStamp() {
    // Acquire the time
    const auto tp_utc{std::chrono::system_clock::now()};

    // Measure time and convert it to a string
    std::time_t t_timeToUTC = std::chrono::system_clock::to_time_t(tp_utc);
    std::ostringstream oss;
    oss << std::put_time(std::gmtime(&t_timeToUTC), "%Y-%m-%d %H:%M:%S");
    std::string t_time_str = oss.str();

    return t_time_str;

}

/// @brief Generates a log text file in the logs folder
/// @param t_message 
void ErrLog::genLogFile(const std::string& t_message) {
    // Define log path
    std::filesystem::create_directories("logs");
    std::string t_logFilePath = "logs/details.log";
    // Open the file; specify appending first
    std::ofstream file(t_logFilePath, std::ios::out | std::ios::app);

    // Is the file actually open?
    if (!file) {
        std::cerr << "Failed to open file\n";
        return; // Exit the function ASAP
    }

    // Assemble the message
    file << 
    genTimeStamp() <<
    ", " <<
    t_message <<
    std::endl;

}