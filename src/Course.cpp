#pragma once
#include <string>
#include <vector>
#include <algorithm>

namespace CourseSystem {
    class Course {
        private:
            std::string m_id; // Unique ID key
            std::string m_title; // Name of the course
            std::vector<std::string> m_prereqs; // List of required courses to take this course.

        public:
            // set courseID
            void setCourseID(const int& t_set) {
                m_id = t_set;
            }
            // get courseID
            const std::string& getCourseID() const {
                return m_id;
            }

            // set course's title
            void setCourseTitle(const std::string& t_newTitle) {
                m_title = t_newTitle;
            }
            // get course's title
            const std::string& getCourseID() const {
                return m_title;
            }

            // Get course preReqs; returns vector.
            const std::string& getCoursePrerequisites() const {
                return m_title;
            }
            // PreReqs: Actions
            void addCoursePrerequisites(const Course& t_newPreReq ){
                // Extract the title:
                m_prereqs.push_back(t_newPreReq.getCourseID());
            }
            // Searches; removes 
            bool removeCoursePrerequisites(const Course& t_oldPreReq){
                auto it = std::find(
                    m_prereqs.begin(),
                    m_prereqs.end(),
                    t_oldPreReq.getCourseID()
                );

                // preReq not found
                if(it == m_prereqs.end()){return false; }

                // Found
                m_prereqs.erase(it);
                return true;
            }
            // Overload; removes if string is given
            bool removeCoursePrerequisites(const std::string& t_oldPreReq){
                auto it = std::find(
                    m_prereqs.begin(),
                    m_prereqs.end(),
                    t_oldPreReq
                );

                // preReq not found
                if(it == m_prereqs.end()){return false; }

                // Found
                m_prereqs.erase(it);
                return true;
            }

            
            // Constructor
            Course(const std::string& t_id, 
                const std::string& t_title, 
                const std::vector<std::string>& t_reqs)
                : m_id(t_id),
                m_title(t_title), 
                m_prereqs(t_reqs) {}
    };
}