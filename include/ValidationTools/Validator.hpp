#ifndef FILE_LOADER_FILE_LOADER_HPP
#define FILE_LOADER_FILE_LOADER_HPP

#include <string>
#include <vector>
#include <unordered_map>

#include "CourseManagement/Course.hpp"

namespace VarLoader {
    bool parseLine(const std::string& t_line,
        std::string& t_id,
        std::string& t_title,
        std::vector<std::string>& t_rawPrereqs);

    /**
     * @brief Takes a CSV and parses it to resolve them into course objects
     * @param t_csvPath, a path to the CSV
     * @return a vector of all the courses from the CSV
     * @pre Needs a valid CSV with correct formatting.
     * @post Produce a vector with course objects with in it.
     */
    std::vector<CourseData::Course> mountCSV(const std::string& t_csvPath);

    /**
     * @brief Safely takes an integer from a user, preventing buffer overflows.
     * @param none
     * @return always an integer
     * @pre handles user inputs by itself
     * @post 
     */
    int getIntFromCin();
} 

#endif 