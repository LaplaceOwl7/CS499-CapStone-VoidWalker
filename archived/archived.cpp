#include <iostream>
#include<string>
#include<vector>

#include <algorithm>
#include <fstream>
#include <cctype>  
#include <sstream>
#include <limits>

#include "../src/Course.cpp"

// #include "Functions.h" 

/* 
* Show Course info for a specific course.
* @ param course vectors and search courseNumber (id) to find. 
*/
void printCourseInformation(vector<Course>& courses, string courseNumber) {

    // Begin search
    for (int z = 0; z < courses.size(); z++) {   // Iterate through all courses.
        if (courseNumber == courses[z].courseId) {  // Is there a match?
            cout << courses[z].courseId << ",   " << courses[z].m_title << '\n'; // Run preReqs
            cout << "Prerequisites: ";
            // Iterate through each req.
            for (size_t i = 0; i < courses[z].preReqs.size(); i++) {
                cout << courses[z].preReqs[i].courseId; // Print courses ID.
                if (i < courses[z].preReqs.size() - 1) { // if it is a last one.
                    cout << ", ";
                }
            }
            cout << '\n';
            break;  // Break after finding the match
        }
    }
} // End prCInfo

/*
* Helper function for orderCourses
*@ param vector to list courses; reqs is if you want the preReqs listed.
*/
void printAllCourses(vector<Course> allCourses, bool reqs) {
    // Print all courses.
    for (const auto& course : allCourses) { // Iterate through allCOurses.
        cout << course.courseId << ",  " << course.m_title << '\n'; // Print basics.
        // List preReqs; This is a fragement of the past that stayed in.
        if (reqs) {
            cout << "Prerequisites: ";
            if (!course.preReqs.empty()) {
                for (int i = 0; i < course.preReqs.size() - 1; i++) {
                    cout << course.preReqs[i].courseId << ", ";
                }
                cout << course.preReqs.back().courseId << endl; // For the final part
            }
            else {
                cout << "None" << '\n';
            }
        }
    }
    cout << '\n';
}



/* 
    Load a csv to the vector
 * @param path to the csv.
 * @return The master vector to hold all the courses.
 */
vector<Course> mountCSV(string csvPath) {
    cout << "Attempting to mount CSV file " << csvPath << '\n';

    // Define a vector data structure to hold a collection of courses.
    vector<Course> allCourses;
    string line; // For lines in the file.

    // Attempt to open the file
    fstream file(csvPath);
    
    // Is the file actually open?
    if (!file) {
        cerr << "Error: File not open" << '\n';
        return allCourses; // Return blank vector.
    }
    else {
        string courseId, courseTitle, preReqs_string;
        vector<string> preReqs;

        while (getline(file, line)) { //Read each line from the file
            istringstream i_s_s(line); // Take the line for partitioning

            // Grab each line ending at the ",'s // These should get the min requirements.
            // If not ran, the file is incorrectly configured.
            if (getline(i_s_s, courseId, ',') && getline(i_s_s, courseTitle, ',') ) {

                // Get the preRews as a string.
                getline(i_s_s, preReqs_string);

                // Create course object with empty preReqs. We can add them later.
                Course newCourse(courseId, courseTitle, {});

                if (!preReqs_string.empty()) { // Only if the string isn't empty.
                    // Prepare to segment the preReq
                    istringstream preReqs_stream(preReqs_string);
                    string preReq; // To add it.

                    while (getline(preReqs_stream, preReq, ',')) { // Segment the preReqs.

                        for (const auto& x : allCourses ){ // X = current iterated course
                            if (preReq == x.courseId) { // Is it a valid course? Then add it the courses preReqs
                                preReqs.push_back(x.courseId);
                                newCourse.preReqs.push_back(x);
                                break; // Save some data.
                            } // End if prereq
                        } 
                    } 
                } // end if prereq is empty
                // Add the course.
                allCourses.push_back(newCourse);
            } // End if
        } // End while line
    } // End file open
    cout << '\n';
    return allCourses;
} // End function.

static void displayMenu(){
    cout << "Welcome to the course planner." << endl;
    cout << "  1. Load Data Structure" << endl;
    cout << "  2. Print Course List" << endl;
    cout << "  3. Print Course" << endl;
    cout << "  4. Exit" << endl;
}

// Lifed from CS410: Reverse Engineering
// I'm the dev, so I figured I can use it.
int getIntFromCin(){
    // The purpose is to read a string, convert it to int.
    std::string userInput; 
    long long tempNumber = 0; // A long long will add more resistance for buffer overflows
    int intOutput = 0; // Define this variable.

    // Create a endless loop only exitable by a valid int
    while (true){
        if (!(std::getline(std::cin, userInput))){ // A trigger for any break of cin. If tripped, it will clear it.
            std::cerr << "Invalid Input\nEnter a valid number:\n";
            std::cin.clear(); // Clear CIN
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Purge bad input.
            continue;
        } else { 
            try {
                // Strings are rejected and prompted to input them again
                // Floats and long long are valid, they lose their decimal places.

                tempNumber = std::stoll(userInput); // Turn it to a long long for a second.

                // Test if the converted long long is valid the int data type
                // Without this check, integer wraps can occur, leading to undefined behavior.
                if (tempNumber > std::numeric_limits<int>::max() || tempNumber < std::numeric_limits<int>::min()) {
                    throw std::out_of_range("Value too large!\n");
                }

                // Explicit conversion
                intOutput = static_cast<int>(tempNumber);

                break;
                // May or may not be triggered.
            } catch (std::out_of_range&) { 
                std::cerr << "Invalid Number! Please Try Again\n";
            } catch (std::invalid_argument&){
                std::cerr << "Invalid Number!\n";
            }
        }
    }
    return intOutput; // Return an int.
}

int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    //csvPath = "Base_Input.csv";
    csvPath = "My_Input.csv";

    // Define a vector to hold all the courses.
    vector<Course> allCourses;
    string query;

    int choice = 0;
    while (choice != 4) {
        displayMenu();

        cout << "What would you like to do? ";

        cin >> choice;

        cout << '\n';

        choice = getIntFromCin();        switch (choice) {

        case 1: // Load Data Strucutre
            cout << "Loading courses..." << endl;

            allCourses = mountCSV(csvPath);

            cout << "Courses successfully loaded." << '\n';
            break;

        case 2: // Print Course LIst
            printAllCourses(bubbleSort(allCourses), false);
            break;

        case 3: // Print specific course.
            cout << "What course do you want to know about?";
            cin >> query;

            // Quickly throw a loop to turn it to upper case.
            for (char& x : query) {
                x = toupper(x);
            }
            
            printCourseInformation(allCourses, query);
            break;

        default:
            if (choice != 4) {
                cout << choice << " isn't a valid option." << '\n';
            }
            break;
        }
    }

    cout << "Thank you for using the course planner!" << '\n';

    return 0;
}
