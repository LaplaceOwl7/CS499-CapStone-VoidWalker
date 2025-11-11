#pragma once
#include <string>
#include <vector>

namespace CourseSystem {

class Course {
    public:
        Course(const std::string& t_id, const std::string& t_title);
        void setCourseTitle(const std::string& t_title);
        const std::string& getCourseTitle() const;
    private:
        std::string m_id;
        std::string m_title;
    };

} 
