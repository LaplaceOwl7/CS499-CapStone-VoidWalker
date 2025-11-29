#ifndef SORTER_MERGESORTER_HPP
#define SORTER_MERGESORTER_HPP

#include <vector>

#include "CourseManagement/Course.hpp"

namespace sorter {

std::vector<CourseData::Course>& performMergeSort(std::vector<CourseData::Course>& t_courses);

void mergeSortImpl(
    std::vector<CourseData::Course>& t_courses, 
    std::size_t t_left, 
    std::size_t t_right
);

void merge(std::vector<CourseData::Course>& t_courses,
std::size_t t_left,
std::size_t mid,
std::size_t t_right);

}

#endif // SORTER_MERGESORTER_HPP
