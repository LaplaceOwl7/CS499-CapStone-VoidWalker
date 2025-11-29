#ifndef DATAMANAGER_HPP
#define DATAMANAGER_HPP

#include <string>
#include <vector>
#include <sqlite3.h>
#include <optional>
#include "CourseManagement/Course.hpp"

namespace Data {

class DatabaseManager {
    public:
        // Define a Constructor
        DatabaseManager(const std::string& t_dbPath);

        // Destructor
        ~DatabaseManager();

        /// @brief Adds a course to the SQLite databases
        /// @param t_course The course object to add to the database
        /// @return returns a boolean if the course was sucessful 
        bool addCourse(
            const CourseData::Course t_course
        );

        /// @brief Removes the course when a string 
        /// @param t_courseToDelete 
        /// @return returns a boolean depending whether the course was found and deleted
        bool removeCourse(
            const std::string& t_courseID
        );

        /// @brief Function to update a selected course
        /// @param t_courseToUpdate The course to search the vector for
        /// @return returns a boolean if the course was sucessfully found and updated
        bool updateCourse(
            const CourseData::Course t_courseToUpdate
        );

        /// @brief Fetches all courses for viewing
        /// @return A vector of all course objects
        std::vector<CourseData::Course> fetchAllCourse() const;

        /// @brief Searches all courses lineraly to find an ID
        /// @param t_courseTitleToSearch A Course Title to search for.
        /// @return A course object if found.
        std::optional<CourseData::Course> searchbyID(
            const std::string& t_courseIDToFind) 
            const;
        
        /// @brief Searches through all the courses via Title
        /// @param t_courseTitleToFind 
        /// @return 
        std::vector<CourseData::Course> searchByTitle(
            const std::string& t_courseTitleToFind) const;

        /// @brief Gives the raw DB pointer for the user database
        /// @return returns the raw db pointer 
        sqlite3* getRawDB()
        const { 
            return m_database;
        }

    private:
        /// @brief The shared database var
        sqlite3 *m_database;

        /// @brief Generates the schema for the SQLite database
        /// @return a boolean if the creation was successful
        bool generateSchema();

        /// @brief Executes a simple SQL statement
        /// @param t_sqlStatement The non-parameterized statement that is excuted
        /// @return True or false; depending upon a successful execution
        bool executeSQLStatement(
            const std::string& t_sqlStatement
        ) const;

    };

}
#endif