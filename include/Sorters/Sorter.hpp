#ifndef SORTER_HPP
#define SORTER_HPP

#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

// Fetch all sorting algorithm headers
#include "Sorters/BubbleSort.hpp"
#include "Sorters/QuickSort.hpp"
#include "Sorters/MergeSort.hpp"
#include "Sorters/Timer.hpp"

// Structure to hold the results of the time
struct SortTimingResults {
    long long bubbleSortTime = 0;
    long long mergeSortTime = 0;
    long long quickSortTime = 0;
    long long standardSortTime = 0;
};


template<typename T>

class Sorter {
public:

    /**
     * @brief calls the recorded benchmarks times.
     * @return nothing
     */
    SortTimingResults getResults() const {
        return m_results; 
    }

    /**
     * @brief Sorts a vector in place using the bubble sort algorithm
     * @param t_toSort the vector of Course objects to sort
     * @return nothing; sorts in place
     * @pre Needs a vector of Course objects with CourseIDs
     * @post Sorts in place
     */
    void bubbleSort(std::vector<T>& t_toSort) {
        Timer timer;
        timer.startTimer();

        sorter::performBubbleSort(t_toSort);

        m_results.bubbleSortTime = timer.stopTimer();
    }

    /**
    * @brief Sorts a vector in place using the quickSort algorithm
    * @param t_toSort the vector of Course objects to sort
    * @return nothing; sorts in place
    * @pre Needs a vector of course objects with courseIDs
    * @post sorts in place
    */
    void quickSort(std::vector<T>& t_toSort) {
        Timer timer;
        timer.startTimer();

        sorter::performQuickSort(t_toSort);

        m_results.quickSortTime = timer.stopTimer();
    }

    /**
    * @brief Sorts a vector in place using the mergeSort algorithm
    * @param t_toSort the vector of Course objects to sort
    * @return nothing; sorts in place
    * @pre Needs a vector of course objects with courseIDs
    * @post sorts in place
    */
    void mergeSort(std::vector<T>& t_toSort) {
        Timer timer;
        timer.startTimer();

        sorter::performMergeSort(t_toSort);

        m_results.mergeSortTime = timer.stopTimer();
    }

    /**
    * @brief Sorts a vector in place using c++'s std::sort algorithm
    * @param t_toSort the vector of Course objects to sort
    * @return nothing; sorts in place
    * @pre Needs a vector of course objects with courseIDs
    * @post sorts in place
    */
    void standardSort(std::vector<T>& t_toSort){
        Timer timer;
        timer.startTimer();

        std::sort(
            t_toSort.begin(),
            t_toSort.end(),
            [] (
                const CourseData::Course& course1,
                const CourseData::Course& course2
            ) {
                return course1.getCourseID() < course2.getCourseID();
            }
        );
        m_results.mergeSortTime = timer.stopTimer();
    };

    /**
    * @brief returns a vector of the sorting algorithm choices
    * @return t_sortingChoices a vector with strings of each algortih,
    * @pre needs a private vector inside the sorter header
    */
    std::vector<std::string> getChoices() {
        return t_sortingChoices;
    }

    /**
     * @brief Takes vector of choices and prints them with newlines
     * @param vector with strings of each algorithm supported
     * @return nothing; prints via std::cout
     * @pre needs a vector to print
     * @post prints to std::cout
     */
    void printChoices(const std::vector<std::string>& t_choices){
        for (int i = 0; i < t_choices.size(); i++) {
            std::cout << t_choices[i] << std::endl;
        }
    }

    private:
        SortTimingResults m_results;

        /// @brief A list of algorithms supported
        std::vector<std::string> t_sortingChoices = {
            "1. QuickSort",
            "2. MergeSort",
            "3. BubbleSort",
            "4. Standard Sort"
        };
};

#endif // SORTER_HPP
