#include <vector>
#include <string>
#include <algorithm>
#include "CourseManagement/Course.hpp"

namespace sorter {

// Forward declarations to allow recursion.
// C++ doesn't see implementations until  afterwards
static void mergeSortImpl(
    std::vector<CourseData::Course>& t_courses, 
    std::size_t t_left,
    std::size_t t_right
);

static void merge(
    std::vector<CourseData::Course>& t_courses,
    std::size_t t_left,
    std::size_t mid,
    std::size_t t_right
);

std::vector<CourseData::Course>& performMergeSort(
    std::vector<CourseData::Course>& t_courses) 
    {
    if (t_courses.size() <= 1) {
        return t_courses;
    }

    mergeSortImpl(t_courses, 0, t_courses.size() - 1);
    return t_courses;
}

static void mergeSortImpl(std::vector<CourseData::Course>& t_courses, std::size_t t_left, std::size_t t_right) {
    if (t_left >= t_right) {
        return;
    }

    const std::size_t mid = t_left + (t_right - t_left) / 2;

    mergeSortImpl(t_courses, t_left, mid);
    mergeSortImpl(t_courses, mid + 1, t_right);

    merge(t_courses, t_left, mid, t_right);
}

static void merge(std::vector<CourseData::Course>& t_courses,
    std::size_t t_left,
    std::size_t mid,
    std::size_t t_right) 
{
    const std::size_t leftSize  = mid - t_left + 1;
    const std::size_t rightSize = t_right - mid;

    std::vector<CourseData::Course> leftVec(leftSize);
    std::vector<CourseData::Course> rightVec(rightSize);

    for (std::size_t i = 0; i < leftSize; ++i) {
        leftVec[i] = t_courses[t_left + i];
    }
    for (std::size_t j = 0; j < rightSize; ++j) {
        rightVec[j] = t_courses[mid + 1 + j];
    }

    std::size_t i = 0;
    std::size_t j = 0;
    std::size_t k = t_left;

    while (i < leftSize && j < rightSize) {
        const std::string& leftId  = leftVec[i].getCourseID();
        const std::string& rightId = rightVec[j].getCourseID();

        if (leftId < rightId) {
            t_courses[k] = leftVec[i];
            ++i;
        } else {
            t_courses[k] = rightVec[j];
            ++j;
        }
        ++k;
    }

    while (i < leftSize) {
        t_courses[k] = leftVec[i];
        ++i;
        ++k;
    }

    while (j < rightSize) {
        t_courses[k] = rightVec[j];
        ++j;
        ++k;
    }
}

}