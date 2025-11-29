#ifndef RECORDER_HPP
#define RECORDER_HPP

#include <string>

class Recorder {

public:
    /**
     * @brief Logs CRUD Operations for the database
     * @param t_username Who the user is modifying these actions
     * @param t_action Action type: CREATE, UPDATE, DELETE.
     * @param t_courseId ID of the course involved.
     * @param t_courseTitle Optional title of the course.
     */

    void logChange(
        const std::string& t_username,
        const std::string& t_action,
        const std::string& t_courseId,
        const std::string& t_courseTitle = ""
    );

private:
    /**
     * @brief Generates a formatted timestamp string.
     * @return A UTC timestamp string: YYYY-MM-DD HH:MM:SS
     */
    std::string genTimeStamp();
};

#endif // RECORDER_HPP
