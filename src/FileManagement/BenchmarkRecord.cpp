#include "Benchmarker.hpp"
#include <fstream>
#include <iostream>
#include "ValidationTools/Err.hpp"

void Benchmarker::writeCSV(
    const std::string& t_record,
    const std::string& t_path
) {
    std::ostream file(t_path, std::ios::app);

    // File Open?
    if (!file.is_open()){
        ErrLog::genLogFile("Failed to open Benchmarking CSV");
        return; // abort
    }

    // Draft header file if empty
    file.seek(0,)
}