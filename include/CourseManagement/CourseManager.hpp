#ifndef COURSEMANAGER_COURSEMANAGER_HPP
#define COURSEMANAGER_COURSEMANAGER_HPP

#include <string>
#include <vector>
#include <optional>

#include "CourseManagement/CourseManager.hpp"
#include "ValidationTools/Validator.hpp"
#include "ValidationTools/Err.hpp"
#include "Database/DataManager.hpp"
#include "Database/User.hpp"


class CourseManager {

    public:
    /**
     * @brief Loads master vector of Course objects into memory from a CSV file.
     * @param t_filePath Path to the CSV file.
     * @return Vector of all loaded CourseSystem::Course objects.
     * @pre The CSV file must exist and be readable.
     * @post Returns the master list; suitable for testing or further operations.
     */
    std::vector<CourseData::Course> loadCourses(const std::string& t_filePath);

    /**
     * @brief Performs a linear search for a specific course by ID.
     * @param t_courses Vector of Course objects to search.
     * @param t_courseId Target course ID to find.
     * @post If found, prints the course ID, title and its prerequisites to std::cout.
     */
    void searchCourse(
        const std::vector<CourseData::Course>& t_courses,
        const std::string& t_courseId
    );

    /**
     * @brief Prints all courses in the provided vector to std::cout,
     *        including their ID, title, and prerequisites.
     * @param t_allCourses Vector of all Course objects to print.
     * @pre Each CourseSystem::Course must have valid data.
     * @post Outputs all courses and their prerequisites.
     */
    void printAllCourses(const std::vector<CourseData::Course>& t_allCourses);

    /**
     * @brief Displays the textual menu choices for the application.
     * @post Prints the menu options (e.g., “Print All Courses”, “Search for Course”, …) to std::cout.
     */
    void displayMenu();

    /// @brief Load all courses from SQLite database
    /// @return preloads the courses into the database
    std::vector<CourseData::Course> loadCoursesFromDB();

    /// @brief Adds a course object to the database
    /// @param t_course the course to add
    /// @return boolean on whether the addition was successful
    bool addCourseToDB(
        const CourseData::Course& t_course
    );

    /// @brief Delete the course object from the database
    /// @param t_courseID the targeted course to delete from the database 
    /// @return boolean on whether the deletion was successful
    bool deleteCourseFromDB(
        const std::string& t_courseId
    );

    /// @brief search the database for a courseID
    /// @param t_courseID the course id to search for 
    /// @return optionally returns a Course object; could return a nullopt
    std::optional<CourseData::Course> searchCourseByIDFromDB(
        const std::string& t_courseID
    );

    /// @brief  searches the database for a Title
    /// @param t_title the title to search the db for 
    /// @return a vector of the title returned; titles are not unique
    std::vector<CourseData::Course> searchCourseByTitleDB(
        const std::string& t_title
    );

    /// @brief Load courses into a datebase from the seed CSV files
    /// @param t_csvPath the pathway to the CSV file
    /// @return returns a master factor with all the courses.
    std::vector<CourseData::Course> loadCoursesFromDBWithSeed(
        const std::string& t_csvPath
    );

    /// @brief  Updates a course in a database
    /// @param t_course A course object
    /// @return A boolean on whether the update was a success or failure 
    bool updateCourseInDB(
        const CourseData::Course t_course
    );

    Data::DatabaseManager& getDatabaseManager();

    /// @brief Prints all the CRUD operations via a simple funciton; see the CourseManager.cpp for more info
    void printCRUDOperations();

    /// @brief handles user input to manage the CRUD operations
    /// @param manager takes the manager object to handle
    /// @param user the credentials of the user attempting to operate
    void takeCRUDOperation(
        CourseManager& manager,
        const Auth::User& user
    );

    /// @brief Print the course information of one single course
    /// @param t_course the course to print its information
    void printSingleCourse(
        const CourseData::Course& t_course
    );

    private:
        Data::DatabaseManager m_database{"courses.db"};

};

#endif // COURSEMANAGER_COURSEMANAGER_HPP
