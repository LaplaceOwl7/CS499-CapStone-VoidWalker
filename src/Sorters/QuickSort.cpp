#include <vector>
#include <string>
#include "CourseManagement/Course.hpp"
#include "Sorters/QuickSort.hpp"

namespace sorter {

// Forward declarations; c++ doesn't see anything that is after declarations
static int partition(std::vector<CourseData::Course>& 
    t_courses,
    int t_low,
    int t_high
);
static void quickSortImpl(
    std::vector<CourseData::Course>& t_courses,
    int t_low,
    int t_high
);

std::vector<CourseData::Course>& performQuickSort(
    std::vector<CourseData::Course>& t_courses)
{   // Is there enough to sort?
    int courseSize = static_cast<int>(t_courses.size()) - 1;
    
    if (t_courses.size() <= 1) {
        return t_courses;
    }

    quickSortImpl(t_courses, 0, courseSize);

    return t_courses;
}
// Helper function for partitioning courses; used in QuickSorting
static int partition(
    std::vector<CourseData::Course>& t_courses,
    int t_low,
    int t_high)
{
    CourseData::Course& pivot = t_courses[t_high];
    const std::string& pivotId = pivot.getCourseID(); // can not convert

    int i = t_low - 1; // Get index

    // Iterate through and sort
    for (int j = t_low; j < t_high; ++j) {
        if (t_courses[j].getCourseID() <= pivotId) {
            ++i;
            std::swap(t_courses[i], t_courses[j]);
        }
    }
    // Swap the vars
    std::swap(t_courses[i + 1], t_courses[t_high]);
    return i + 1;
}


// Helper function designed to clean up quickSort
static void quickSortImpl(
    std::vector<CourseData::Course>& t_courses,
    int t_low,
    int t_high)
{
    if (t_low < t_high) {
        int pivotIndex = partition(t_courses, t_low, t_high);

        quickSortImpl(t_courses, t_low, pivotIndex - 1);
        quickSortImpl(t_courses, pivotIndex + 1, t_high);
    }
}

} // ns: sorter
