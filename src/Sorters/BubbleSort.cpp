
#include "Sorters/BubbleSort.hpp"
#include "CourseManagement/Course.hpp"
#include "Sorters/Timer.hpp"
#include "ValidationTools/Err.hpp"

#include <vector>
#include <algorithm>

namespace sorter {
void performBubbleSort(std::vector<CourseData::Course>& courses) {

    // Is the vector large enough? Seg Fault can happen if not:
    if (courses.size() < 2){
        ErrLog err;
        err.genLogFile("BubbleSort received a size < 2");
    }
    // Perform a bubblesort
    bool swapped; // Has something been swapped?
    for (int i = 0; i < courses.size() - 1; i++) {
        swapped = false;
        // Iterate through each course:
        for (int j = 0; j < courses.size() - i - 1; j++) { // Courses remaining
            if (courses[j].getCourseID() > courses[j + 1].getCourseID()) { // Swap?
                std::swap(courses[j], courses[j + 1]);
                swapped = true;
            }
        }
        
        if (!swapped) {
            break;
        }
    }
    // return courses;
}
};