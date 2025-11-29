#include "Database/DataManager.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <sqlite3.h>
#include <optional>

#include "CourseManagement/Course.hpp"
#include "ValidationTools/Err.hpp"
#include "ValidationTools/Validator.hpp"
#include "Database/Recorder.hpp"

bool Data::DatabaseManager::executeSQLStatement(
    const std::string& t_sql
) const {
    ErrLog err;
    char* errMsg = nullptr;
    
    // Note: The queries will have to be parameterized per function

    const int rc = sqlite3_exec(
        m_database,
        t_sql.c_str(),
        nullptr,
        nullptr,
        &errMsg
    );

    if (rc != SQLITE_OK) {
        std::string msg = "SQL exec failed: ";
        if (errMsg != nullptr) {
            msg += errMsg;
            sqlite3_free(errMsg);
        }
        err.genLogFile(msg);
        return false;
    }
    return true;
}

bool Data::DatabaseManager::generateSchema(){
    const std::string sqlQuery =
    "CREATE TABLE IF NOT EXISTS courses ("
    "courseID TEXT PRIMARY KEY,"
    "courseName TEXT NOT NULL, "
    "prereqs TEXT"
    ");";

    // Generate a basic user
    const std::string userTable =
    "CREATE TABLE IF NOT EXISTS users ("
    "username TEXT PRIMARY KEY, "
    "password TEXT NOT NULL, "
    "is_admin INTEGER NOT NULL"
    ");";

    executeSQLStatement(userTable);


    return executeSQLStatement(sqlQuery);
}

// Define a Constructor; Opens the database file
Data::DatabaseManager::DatabaseManager(const std::string& t_dbPath)
{
    // Confirm or Deny the database is open. 
    bool db_open = false;
    std::string databaseFile = "my.db";
    int rc;
    ErrLog err;

    rc = sqlite3_open("my.db", &m_database);
    
    if (rc == SQLITE_OK) {
        db_open = true;

        generateSchema();
        
    } else {
        err.genLogFile("Failed to Open SQLDatabase!");
        return;
    }

}

// Destructor
Data::DatabaseManager::~DatabaseManager(){

    // If the database is open, close it.
    if (m_database != nullptr){
        sqlite3_close(m_database);
    }
}


bool Data::DatabaseManager::addCourse(
    const CourseData::Course t_courseToAdd
){
    // Develop the skeleton statement
    const std::string sqlQuery =
    "INSERT INTO courses (courseID, courseName, prereqs) VALUES (?, ?, ?);";

    // Prepare the sql command; making a placeholder
    sqlite3_stmt* sqlCommand = nullptr;

    // Is the database connection still open?
    if (sqlite3_prepare_v2(m_database, sqlQuery.c_str(), -1, &sqlCommand, nullptr) != SQLITE_OK) {
        return false; // Abort
    }

    // Bind text to prepare the course
    sqlite3_bind_text(
        sqlCommand,
        1,
        t_courseToAdd.getCourseID().c_str(),
        -1, 
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        sqlCommand,
        2,
        t_courseToAdd.getCourseTitle().c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    // Prepare the vector for prereqs
    std::ostringstream joinedCourses;

    const auto& prereqs = t_courseToAdd.getCoursePrerequisites();

    // For each preReq,
    for (std::size_t i = 0; i < prereqs.size(); ++i) {
        // Add it
        joinedCourses << prereqs[i];
        if (i + 1 < prereqs.size()) {
            joinedCourses << ",";
        }
    }

    // Bind the PreReq vector
    sqlite3_bind_text(
        sqlCommand,
        3,
        joinedCourses.str().c_str(),
        -1, 
        SQLITE_TRANSIENT
    );

    // Was the insertion a success?
    const bool success = (sqlite3_step(sqlCommand) == SQLITE_DONE);
    sqlite3_finalize(sqlCommand);
    return success;
}

bool Data::DatabaseManager::removeCourse(
    const std::string& t_courseID
){
    // Develop the skeleton statement
    const std::string sqlQuery =
    "DELETE FROM courses WHERE courseID = ?;";

    sqlite3_stmt* sqlCommand = nullptr;

    if (sqlite3_prepare_v2(m_database, sqlQuery.c_str(), -1, &sqlCommand, nullptr) != SQLITE_OK) {
        return false; // Abort
    }

    sqlite3_bind_text(
        sqlCommand,
        1,
        t_courseID.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    const bool success = (sqlite3_step(sqlCommand) == SQLITE_DONE);
    sqlite3_finalize(sqlCommand);
    return success;
}


bool Data::DatabaseManager::updateCourse(const CourseData::Course t_courseToUpdate){
    // Develop the skeleton statement
    const std::string sqlQuery =
    "UPDATE courses SET courseName = ?, prereqs = ? WHERE courseID = ?;";

    // Prepare the sql command; making a placeholder
    sqlite3_stmt* sqlCommand = nullptr;

    // Is the database connection still open?
    if (sqlite3_prepare_v2(m_database, sqlQuery.c_str(), -1, &sqlCommand, nullptr) != SQLITE_OK) {
        return false; // Abort
    }

    // Bind text for the updated course title
    sqlite3_bind_text(
        sqlCommand,
        1,
        t_courseToUpdate.getCourseTitle().c_str(),
        -1, 
        SQLITE_TRANSIENT
    );

    // Prepare the vector for prereqs
    std::ostringstream joinedCourses;

    const auto& prereqs = t_courseToUpdate.getCoursePrerequisites();

    // For each preReq,
    for (std::size_t i = 0; i < prereqs.size(); ++i) {
        // Add it
        joinedCourses << prereqs[i];
        if (i + 1 < prereqs.size()) {
            joinedCourses << ",";
        }
    }

    // Bind the PreReq vector
    sqlite3_bind_text(
        sqlCommand,
        2,
        joinedCourses.str().c_str(),
        -1, 
        SQLITE_TRANSIENT
    );

    // Bind the courseID last:
    sqlite3_bind_text(
        sqlCommand,
        3,
        t_courseToUpdate.getCourseID().c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    // Was the insertion a success?
    const bool success = (sqlite3_step(sqlCommand) == SQLITE_DONE);
    sqlite3_finalize(sqlCommand);
    return success;
}

std::vector<CourseData::Course> Data::DatabaseManager::fetchAllCourse() const {
    // Create the vector to store all courses
    std::vector<CourseData::Course> allCourses;

    // Create the skeleton statement
    const std::string sqlQuery =
    "SELECT courseID, courseName, prereqs FROM courses;";

    // Prep the SQL command; making a placeholder
    sqlite3_stmt* sqlCommand = nullptr;

        // Is the database connection still open?
    if (sqlite3_prepare_v2(m_database, sqlQuery.c_str(), -1, &sqlCommand, nullptr) != SQLITE_OK) {
        return allCourses; // Abort early; return empty
    }

    // Iterate through each row returned:

    while (sqlite3_step(sqlCommand) == SQLITE_ROW) {
        // Extract course IDs
        // Use the reinterpret_cast function to perform a unsafeish explicit conversion;
        // I should be able to control the logic, so it shouldn't be considered unsafe

        std::string id = reinterpret_cast<const char*>(
            sqlite3_column_text(sqlCommand, 0)
        );

        // Extract the course title
        std::string title = reinterpret_cast<const char*>(
            sqlite3_column_text(sqlCommand, 1)
        );

        // Extract prereqs block
        std::string prereqBlock = reinterpret_cast<const char*>(
            sqlite3_column_text(sqlCommand, 2)
        );

        // Generate the preReq vector;
        // Prepare it first
        std::vector<std::string> prereqList;
        std::stringstream stream(prereqBlock);
        std::string piece;

        // Parse comma-separated prereqs
        while (std::getline(stream, piece, ',')) {
            if (!piece.empty()) {
                prereqList.push_back(piece);
            }
        }

        // Push into results
        allCourses.emplace_back(id, title, prereqList);
    }

    sqlite3_finalize(sqlCommand);
    return allCourses;
}


std::optional<CourseData::Course> Data::DatabaseManager::searchbyID(
    const std::string& t_courseIDToFind
) const {
    // Develop the skeleton statement
    const std::string sqlQuery =
    "SELECT courseID, courseName, prereqs FROM courses WHERE courseID = ?;";

    // Prepare the sql command; making a placeholder
    sqlite3_stmt* sqlCommand = nullptr;

    // Is the database connection still open?
    if (sqlite3_prepare_v2(m_database, sqlQuery.c_str(), -1, &sqlCommand, nullptr) != SQLITE_OK) {
        return std::nullopt; // Optional let's us return "nothing"
    }

    // Bind text to prepare the course
    sqlite3_bind_text(
        sqlCommand,
        1,
        t_courseIDToFind.c_str(),
        -1, 
        SQLITE_TRANSIENT
    );

    // Verify there is in fact a result:
    if (sqlite3_step(sqlCommand) != SQLITE_ROW){
        sqlite3_finalize(sqlCommand);
        return std::nullopt; // Return nothing
    }

     // Extract the storedID
    std::string id = reinterpret_cast<const char*>(
        sqlite3_column_text(sqlCommand, 0)
    );

    // Extract the found title
    std::string title = reinterpret_cast<const char*>(
        sqlite3_column_text(sqlCommand, 1)
    );

    // Extract prereqs block; need to do text.
    std::string prereqBlock = reinterpret_cast<const char*>(
        sqlite3_column_text(sqlCommand, 2)
    );

    // Prepare the preReq vector;
    std::vector<std::string> prereqList;
    std::stringstream stream(prereqBlock);
    std::string piece;

    while (std::getline(stream, piece, ',')) {
        if (!piece.empty()) {
            prereqList.push_back(piece);
        }
    }

    sqlite3_finalize(sqlCommand);

    // Generate the final object to return 
    return CourseData::Course(id, title, prereqList);
}

std::vector<CourseData::Course> Data::DatabaseManager::searchByTitle(
    const std::string& t_courseTitleToFind
)const {
    // Create a container to store all matching results
    std::vector<CourseData::Course> matchedCourses;

    // Develop the skeleton statement
    const std::string sqlQuery =
    "SELECT courseID, courseName, prereqs FROM courses WHERE courseName = ?;";

    // Prepare the sql command; making a placeholder
    sqlite3_stmt* sqlCommand = nullptr;

    // Is the database connection still open?
    if (sqlite3_prepare_v2(m_database, sqlQuery.c_str(), -1, &sqlCommand, nullptr) != SQLITE_OK) {
        return matchedCourses; // Abort early; return empty
    }

    // Bind text for the Title we are searching for
    sqlite3_bind_text(
        sqlCommand,
        1,
        t_courseTitleToFind.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    // Step through all results matching the title
    while (sqlite3_step(sqlCommand) == SQLITE_ROW) {

        // Extract the stored ID
        std::string foundId = reinterpret_cast<const char*>(
            sqlite3_column_text(sqlCommand, 0)
        );

        // Extract the stored Title
        std::string foundTitle = reinterpret_cast<const char*>(
            sqlite3_column_text(sqlCommand, 1)
        );

        // Extract prereq block
        std::string prereqBlock = reinterpret_cast<const char*>(
            sqlite3_column_text(sqlCommand, 2)
        );

        // Prepare prereq vector
        std::vector<std::string> prereqList;
        std::stringstream stream(prereqBlock);
        std::string token;

        // Parse prereqs
        while (std::getline(stream, token, ',')) {
            if (!token.empty()) {
                prereqList.push_back(token);
            }
        }

        // Add it to our result list
        matchedCourses.emplace_back(foundId, foundTitle, prereqList);
    }

    sqlite3_finalize(sqlCommand);
    return matchedCourses;


}
