#pragma once

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cctype>  // for toupper
#include <sstream>
#include <string>

using namespace std;

struct Course {
    string courseId; // unique 
    string m_title;
    vector<Course> preReqs;

    Course() {
        courseId = "Null";
        m_title = "Null";
    }

    // Constructor
    Course(string courseId, const string title, const vector<Course>& reqs)
        : courseId(courseId), m_title(title), preReqs(reqs) {}
};

// Only for debugging
void whisper(string wisp);

// Show Course info for a specific course.
void printCourseInformation(const vector<Course>& courses, const string& courseNumber);

/*
* Uses a bubble sort to reorganize the given vector.
* @param courses the unordered vector
* @return the alphanumerically ordered vector.
*/
vector<Course> bubbleSort(vector<Course> courses);

/*
* Helper function for orderCoruses
*@ param vector to list courses; reqs is if you want the preReqs listed.
*/
void print_all_courses(const vector<Course>& allCourses, bool reqs);

/*
    Load a csv to the vector
 * @param path to the csv.
 * @return The master vector to hold all the courses.
 */
vector<Course> mountCSV(const string& csvPath);

#endif 
