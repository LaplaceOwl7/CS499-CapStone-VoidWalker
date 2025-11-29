#ifndef SORTER_QUICKSORT_HPP
#define SORTER_QUICKSORT_HPP

#include <vector>
#include "CourseManagement/Course.hpp"

namespace sorter {

std::vector<CourseData::Course>& performQuickSort(
    std::vector<CourseData::Course>& t_courses);

}

#endif // SORTER_QUICKSORT_HPP