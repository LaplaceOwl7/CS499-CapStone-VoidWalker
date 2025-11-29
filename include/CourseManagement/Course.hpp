#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>
#include <vector>

namespace CourseData {
class Course {
public:
    Course(
        const std::string& t_id,
        const std::string& t_title,
        const std::vector<std::string>& t_reqs = {}
    );

    Course()
        : m_id(""),
        m_title(""),
        m_prereqs({})
    {}


    // Sets Course object's ID
    void setCourseID(const std::string& t_set);
    // Gets Object's course ID
    const std::string& getCourseID() const;
    
    // Sets the course object's title
    void setCourseTitle(const std::string& t_title);
    // Gets the course object's title
    const std::string& getCourseTitle() const;

    // Gets the course object's preReqs vector
    const std::vector<std::string>& getCoursePrerequisites() const;

    // adds the preReq to a course object
    void addCoursePrerequisite(const Course& t_newPreReq);
    // removes preReq to a course object given its course
    bool removeCoursePrerequisites(const Course& t_oldPreReq);
    // removes the preReq given the course object's string
    bool removeCoursePrerequisites(const std::string& t_oldPreReq);
    // Sets the WHOLE preReq given a vector of strings
    void setCoursePrerequisites(
        const std::vector<std::string>& t_NewPreReqs
    );

private:
    std::string m_id;
    std::string m_title;
    std::vector<std::string> m_prereqs;
};

}

#endif // COURSE_HPP

/*
https://cplusplus.com/forum/beginner/4915/
*/