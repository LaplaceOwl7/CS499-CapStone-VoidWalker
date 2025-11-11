#pragma once

#include "BubbleSorter.hpp"
#include "Course.hpp"
#include <vector>
#include <algorithm>

namespace sorter {

    std::vector<CourseSystem::Course> bubbleSort(std::vector<CourseSystem::Course> courses) {
        // Perform a bubblesort
        bool swapped; // Has something been swapped?
        for (int i = 0; i < courses.size() - 1; i++) {
            swapped = false;
            // Iterate through each course:
            for (int j = 0; j < courses.size() - i - 1; j++) { // Courses remaining
                if (courses[j].m_courseID > courses[j + 1].courseId) { // Swap?
                    std::swap(courses[j], courses[j + 1]);
                    swapped = true;
                }
            }
            
            if (!swapped) {
                break;
            }
        }
        return courses;
    }
}