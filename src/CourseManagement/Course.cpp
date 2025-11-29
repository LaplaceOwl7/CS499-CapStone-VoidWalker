#include <algorithm>
#include <string>
#include <vector>

#include "CourseManagement/Course.hpp"

namespace CourseData {

    Course::Course(const std::string& t_id,
                const std::string& t_title,
                const std::vector<std::string>& t_reqs)
        : m_id(t_id), m_title(t_title), m_prereqs(t_reqs) {}

    // Setters and Getters for the course ID
    void Course::setCourseID(const std::string& t_set) {
        m_id = t_set;
    }
    const std::string& Course::getCourseID() const {
        return m_id;
    }

    
    // Setters and getters for the course title
    void Course::setCourseTitle(const std::string& t_newTitle) {
        m_title = t_newTitle;
    }
    const std::string& Course::getCourseTitle() const {
        return m_title;
    }

    // Setters and Getters for course PreReqs
    // Includes get, add, remove
    const std::vector<std::string>& Course::getCoursePrerequisites() const {
        return m_prereqs;
    }
    void Course::addCoursePrerequisite(const Course& t_newPreReq) {
        m_prereqs.push_back(t_newPreReq.getCourseID());
    }

    bool Course::removeCoursePrerequisites(const std::string& t_oldPreReq) {
        auto it = std::find(m_prereqs.begin(), m_prereqs.end(), t_oldPreReq);
        if (it == m_prereqs.end()){ 
            return false;
        }
        m_prereqs.erase(it);
        return true;
    }

    void Course::setCoursePrerequisites(
        const std::vector<std::string>& t_newPrereqs
    ) {
        m_prereqs = t_newPrereqs;
    }

} // ns: CourseSystem
