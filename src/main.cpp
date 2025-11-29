#include <iostream>
#include<string>
#include<vector>

#include <algorithm>
#include <fstream>
#include <cctype>  
#include <sstream>
#include <limits>

#include "CourseManagement/CourseManager.hpp"
#include "Sorters/Sorter.hpp"
#include "FileManagement/Benchmarker.hpp"
#include "Database/User.hpp"

int main(int argc, char* argv[]) {
    CourseManager manager; // Call a course manager to handle this.
    Sorter<CourseData::Course> sorter; // To sort objects
    std::vector<CourseData::Course> testCourses; // For CSV
    std::string userQuery; // For user search
    ErrLog error;
    Benchmarker benchmarker;

   Auth::User currentUser;

    auto loginResult = Auth::promptLogin(
        manager.getDatabaseManager().getRawDB()
    );

    if (!loginResult.has_value()) {
        std::cout << "Login failed. Exiting.\n";
        return 0;
    }

        currentUser = loginResult.value();

    if (currentUser.is_admin) {
        std::cout << "Welcome, Admin " << currentUser.username << "\n";
    } else {
        std::cout << "Welcome, " << currentUser.username << " (read-only)\n";
    }


    // As of Category 3, the SQLite database is now 'owned' by CourseManager
    try {
        std::cout << "Loading Courses from database...\n";
        // Ran Once: testCourses = manager.loadCoursesFromDBWithSeed("seedInput.csv");
        testCourses = manager.loadCoursesFromDB();

        if (testCourses.empty()){
            std::cout << "Database failed to load\nDefaulting to seeded database\n";
            testCourses = manager.loadCourses("seedInput.csv");
        }
    } catch (std::ios_base::failure) { // Typically "file not found"
        error.genLogFile("Failed to load CSV database; aborting\n");
        return 0;
    };

    int userChoice = 0;

    manager.displayMenu();

    std::vector<CourseData::Course> unsortedCourses = testCourses;

    do {
        std::cout << "What would you like to do?\n";

        userChoice = VarLoader::getIntFromCin();

        switch (userChoice)
        {
            case 1:
                std::cout << "Printing all courses...\n";
                // Refresh the entire database:
                testCourses = manager.loadCoursesFromDB(); 

                // Actually print The courses
                manager.printAllCourses(testCourses);
                break;
            case 2:
                
                std::cout << "Course Search Selected\nCourse Query: ";

                std::getline(std::cin, userQuery);

                // Search for the course.
                manager.searchCourse(testCourses, userQuery);
            
                break;
            case 3:  // Sort Via Algorithms
            std::cout << "\nWhich Algorithm would you like to use?\n";

            sorter.printChoices(sorter.getChoices());

            userChoice = VarLoader::getIntFromCin();

            switch (userChoice)
                {
                    case 1:  // Use Quick Sort
                        std::cout << "Sorting with QuickSort...\n";
                        sorter.quickSort(testCourses);
                        manager.printAllCourses(testCourses);
                        break;

                    case 2:  // Use MergeSort
                        std::cout << "Sorting with MergeSort...\n";
                        sorter.mergeSort(testCourses);
                        manager.printAllCourses(testCourses);
                        break;

                    case 3:  // Use BubbleSort
                        std::cout << "Sorting with BubbleSort...\n";
                        sorter.bubbleSort(testCourses);
                        manager.printAllCourses(testCourses);
                        break;

                    case 4: // Use Standard sort
                        std::cout << "Sorting with Standard Sort...\n";
                        sorter.standardSort(testCourses);
                        manager.printAllCourses(testCourses);

                    case 0:
                        std::cout << "Cancelled.\n";
                        break;

                    default:
                        std::cout << "Invalid option. Try again.\n";
                        break;
                }
                break;

            case 4: //Print dynamics, algorithmic efficiency to the console via std::cout
                std::cout << "Benchmarking Algorithms...\n";
                testCourses = unsortedCourses;
                benchmarker.performBenchMark(testCourses);
                benchmarker.printBenchmarkResults();
                break;

            case 5:
                // print markdown of the algorithm's stats, database, comparsion
                benchmarker.generateMarkdownReport();
                break;

            case 6: // Display optimized algorithm
                benchmarker.printMostOptimized();
                break;
            case 7: // Modify Database
                std::cout << "=== === === ===\nModify Database:";
                manager.takeCRUDOperation(
                    manager,
                    currentUser);
                break;

            case 0: // Quit
                break;

            default:
                std::cout << "\nInvalid option\n";
        }

    } while (userChoice != 0);

    return 0;
}
