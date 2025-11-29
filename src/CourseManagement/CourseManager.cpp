#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>
#include <sstream>
#include <map>

#include "CourseManagement/Course.hpp"
#include "CourseManagement/CourseManager.hpp"
#include "Sorters/Sorter.hpp"
#include "ValidationTools/Validator.hpp"
#include "ValidationTools/Err.hpp"
#include "FileManagement/Benchmarker.hpp"
#include "Database/DataManager.hpp" // For SQLite capabilities
#include "Database/User.hpp"
#include "Database/Recorder.hpp"

/// @brief  The data structure for usernames
struct User {
    std::string username;
    bool is_admin;
};


std::vector<CourseData::Course> 
CourseManager::loadCourses(const std::string& t_file_path) 
{
    std::vector<CourseData::Course> allCourses;

    std::ifstream fin(t_file_path);
    if (!fin) {
        std::cout << "CSV file not found.\n";
        return allCourses; // Return Empty Vector
    }

    try {
        allCourses = VarLoader::mountCSV(t_file_path);
    }
    catch (const std::ios_base::failure&) {
        std::cout << "Failed to load CSV Database\n";
        return allCourses;
    }

    return allCourses;
}

void CourseManager::searchCourse(
    const std::vector<CourseData::Course>& t_courses,
    const std::string& t_courseId)
{
    for (const auto& course : t_courses) {
        if (course.getCourseID() == t_courseId) {
            std::cout << course.getCourseID() << ", "
                      << course.getCourseTitle() << '\n';

            const auto& prereqs = course.getCoursePrerequisites();
            std::cout << "Prerequisites: ";

            if (prereqs.empty()) {
                std::cout << "None\n";
                return;
            }

            for (size_t i = 0; i < prereqs.size(); ++i) {
                std::cout << prereqs[i];
                if (i < prereqs.size() - 1) std::cout << ", ";
            }
            std::cout << '\n';
            return;
        }
    }

    std::cout << "Course not found: " << t_courseId << '\n';
}

void CourseManager::printAllCourses(
    const std::vector<CourseData::Course>& t_allCourses)
{
    for (const auto& course : t_allCourses) {
        std::cout << course.getCourseID()
                  << ",  " << course.getCourseTitle() << '\n';

        const auto& prereqs = course.getCoursePrerequisites();
        std::cout << "Prerequisites: ";

        if (prereqs.empty()) {
            std::cout << "None\n";
        } else {
            for (size_t i = 0; i < prereqs.size(); ++i) {
                std::cout << prereqs[i];
                if (i < prereqs.size() - 1) std::cout << ", ";
            }
            std::cout << '\n';
        }
    }
}

void CourseManager::displayMenu()
{
    std::map<size_t, std::string> menuChoices = {
        {1, "Print All Courses"},
        {2, "Search for Course"},
        {3, "Sort via Algorithm"},
        {4, "Print Algorithmic Benchmarks"},
        {5, "Print Markdown of Algorithm Stats"},
        {6, "Display Most Optimized Algorithm"},
        {7, "Modify Database"},
        {0, "Quit"}
    };

    for (const auto& mC : menuChoices) {
        std::cout << mC.first << ":\t" << mC.second << "\n";
    }
}

// Wrapper functions that act upon the database
std::vector<CourseData::Course> CourseManager::loadCoursesFromDB(){
    return m_database.fetchAllCourse();
}

bool CourseManager::addCourseToDB(
    const CourseData::Course& t_course
) {
    return m_database.addCourse(t_course);
}

bool CourseManager::deleteCourseFromDB(
    const std::string& t_courseId
) {
    return m_database.removeCourse(t_courseId);
}

std::optional<CourseData::Course> CourseManager::searchCourseByIDFromDB(
    const std::string& t_courseId
) {
    return m_database.searchbyID(t_courseId);
}

std::vector<CourseData::Course> CourseManager::searchCourseByTitleDB(
    const std::string& t_title
) {
    return m_database.searchByTitle(t_title);
}

bool CourseManager::updateCourseInDB(
    const CourseData::Course t_course
) {
    return m_database.updateCourse(t_course);
}
Data::DatabaseManager& CourseManager::getDatabaseManager(){
    return m_database;
}

// Rough helper to seed the db from the CSV; 
std::vector<CourseData::Course> CourseManager::loadCoursesFromDBWithSeed(
    const std::string& t_csvPath
){
    // Try to load from DB first
    std::vector<CourseData::Course> db_seed = m_database.fetchAllCourse();

    if (!db_seed.empty()) {
        std::cout << "Failed to load seeded db\n";
        return db_seed;
    }

    // DB is empty; load it from the CSV
    std::vector<CourseData::Course> fromCsv;

    try {
        fromCsv = loadCourses(t_csvPath); // your existing CSV loader
    } catch (std::ios_base::failure&) {
        ErrLog err;
        err.genLogFile("Failed to load CSV seed for DB");
        return {}; // nothing we can do
    }

    // Seed the DB
    for (const auto& course : fromCsv) {
        m_database.addCourse(course);
    }

    return fromCsv;
}

void CourseManager::printSingleCourse(
    const CourseData::Course& t_course
) {
    // Print the easy info of the course
    std::cout << t_course.getCourseID() << ", " << t_course.getCourseTitle() << "\n";

    // iterate through the preReqs
    const auto& prereqs = t_course.getCoursePrerequisites();

    // Print the PreReqs
    std::cout << "Prerequisites: ";

    if (prereqs.empty()) { // They empty?
        std::cout << "None\n";
    } else {
        for (size_t i = 0; i < prereqs.size(); ++i) {
            // Iterate through each and print them for the 1000th time
            std::cout << prereqs[i];

            if (i < prereqs.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "\n";
    }
}


void CourseManager::printCRUDOperations(){
    std::cout << "\n=== Database CRUD Operations ===\n";
    std::cout << "1. Add a Course\n";
    std::cout << "2. Search Course by ID\n";
    std::cout << "3. Update a Course\n";
    std::cout << "4. Delete a Course\n";
    std::cout << "0. Cancel\n";
}

void CourseManager::takeCRUDOperation(
    CourseManager& manager,
    const Auth::User& user
) {

    // Before anything, does the user even have access?

    if (!user.is_admin){
        std::cout << "Access Denied!\nDatabase Management is only for Administrators\n";
        return;
    }
    // Print all the CRUD options
    printCRUDOperations();

    // Acquire the choice from the user
    int userChoice = VarLoader::getIntFromCin();
    std::string idInput, titleInput, prereqInput;

    // Handle the choices the user dictates
    switch (userChoice) {
        case 1:  // Create operation
            std::cout << "\nEnter new Course ID: ";
            std::getline(std::cin, idInput);
            std::cout << "Enter Course Title: ";
            std::getline(std::cin, titleInput);
            std::cout << "Enter prerequisites (comma-separated): ";
            std::getline(std::cin, prereqInput);

            Recorder audit;

            {
                std::vector<std::string> prereqs = {
                    prereqInput
                };
                // Create the new course object
                CourseData::Course newCourse(idInput, titleInput, prereqs);

                // Does the function return a success?
                if (manager.addCourseToDB(newCourse)) {
                    std::cout << "Course successfully added.\n";

                    audit.logChange(
                        user.username,
                        "Create",
                        newCourse.getCourseID(),
                        newCourse.getCourseTitle()
                    );
                    
                } else {
                    std::cout << "Failed to add course.\n";
                }
            }
            break;

        case 2:  // Read operation; barebones
            std::cout << "\nEnter Course ID to search: ";
            std::getline(std::cin, idInput);

            {
                auto result = manager.searchCourseByIDFromDB(idInput);
                if (result.has_value()) {
                    std::cout << "\nCourse Found:\n";
                    manager.printSingleCourse(result.value());
                    std::cout << "\nMore Course Info Here\n";
                } else {
                    std::cout << "Course not found.\n";
                }
            }
            break;

        case 3:  // The Update operation
            std::cout << "\nEnter Course ID to update: ";
            std::getline(std::cin, idInput);

            {
                auto result = manager.searchCourseByIDFromDB(idInput);
                if (!result.has_value()) {
                    std::cout << "Course not found; failed to update.\n";
                    break;
                }

                CourseData::Course updated = result.value();

                std::cout << "\nEnter new title: ";
                std::getline(std::cin, titleInput);
                if (!titleInput.empty()) { // Is the input empty?
                    updated.setCourseTitle(titleInput);
                }

                std::cout << "Enter new prereqs: ";
                std::getline(std::cin, prereqInput);
                if (!prereqInput.empty()) {
                    std::vector<std::string> prereqs = { prereqInput };
                    updated.setCoursePrerequisites(prereqs);
                }

                if (manager.updateCourseInDB(updated)) {
                    std::cout << "Course updated successfully.\n";
                    
                    // Log the change
                    audit.logChange(
                        user.username,
                        "Update",
                        updated.getCourseID(),
                        updated.getCourseTitle()
                    );

                } else {
                    std::cout << "Failed to update course.\n";
                }
            }
            break;

        case 4:  // DELETE
            std::cout << "\nEnter Course ID to delete: ";
            std::getline(std::cin, idInput);

            if (manager.deleteCourseFromDB(idInput)) {
                std::cout << "Course successfully deleted.\n";

                // Log the change
                audit.logChange(
                    user.username,
                    "Delete",
                    idInput,
                    ""
                );

            } else {
                std::cout << "Failed to delete course.\n";
            }
            break;

        case 0:
            std::cout << "Cancelled CRUD operations.\n";
            break;

        default:
            std::cout << "Invalid option.\n";
    }
}