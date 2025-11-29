#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "Database/Recorder.hpp"
#include "ValidationTools/Err.hpp"

// Lifted from ErrLogger
std::string Recorder::genTimeStamp() {
    // Acquire the time
    const auto tp_utc{std::chrono::system_clock::now()};

    // Measure time and convert it to a string
    std::time_t t_timeToUTC = std::chrono::system_clock::to_time_t(tp_utc);
    std::ostringstream oss;
    oss << std::put_time(std::gmtime(&t_timeToUTC), "%Y-%m-%d %H:%M:%S");
    std::string t_time_str = oss.str();

    return t_time_str;

}

void Recorder::logChange(
    const std::string& t_username,
    const std::string& t_action,
    const std::string& t_courseId,
    const std::string& t_courseTitle
) {
    
    // Create the fresh directory
    std::filesystem::create_directories("logs");
    // Define the log's path; call it audit
    std::string logPath = "logs/audit.log";

    std::ofstream file(logPath, std::ios::out | std::ios::app);
    if (!file) {
        ErrLog err;
        err.genLogFile("[Recorder] Failed to open audit log.\n");
        return;
    }

    file << genTimeStamp()
         << ", USER: " << t_username
         << ", ACTION: " << t_action
         << ", COURSE ID: " << t_courseId;

    if (!t_courseTitle.empty()) {
        file << ", TITLE: " << t_courseTitle;
    }

    file << '\n';
}
