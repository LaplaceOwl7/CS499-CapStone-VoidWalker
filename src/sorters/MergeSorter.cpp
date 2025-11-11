#include <iostream>
#include <vector>
#include "Course.hpp"

/*
@brief: sorts vector provided by using Merge Sorting
@
*/
std::vector<CourseSystem::Course> merge(std::vector<int>& t_vectorToSort, int t_left, int t_mid, int t_right) {
    // Temp values to split the vectors
    int x = t_mid - t_left + 1;
    int y = t_right - t_mid;

    // Temporary Vectors
    std::vector<int> t_leftVector(x), t_rightVector(y);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < x; i++) {t_leftVector[i] = t_vectorToSort[t_left + i];}
    for (int j = 0; j < y; j++) { t_rightVector[j] = t_vectorToSort[t_mid + 1 + j];}

    int i = 0, j = 0; // Reset iterators
    int k = t_left; // Save t_left into K

    // "Merge" the vectors back.
    while (i < x && j < y) {
        if (t_leftVector[i] <= t_rightVector[j]) {
            t_vectorToSort[k] = t_leftVector[i];
            i++;
        }
        else {
            t_vectorToSort[k] = t_rightVector[j];
            j++;
        }
        k++;
    }

    // Copy the left elements of the vector
    while (i < x) {
        t_vectorToSort[k] = t_leftVector[i];
        i++;
        k++;
    }
    // Copy any and all remaining
    while (j < y) {
        t_vectorToSort[k] = t_rightVector[j];
        j++;
        k++;
    }
}

/* 
void mergeSort()

*/