cmake_minimum_required(VERSION 3.10)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add all .cpp files in src/
file(GLOB SOURCES "src/*.cpp")

add_executable(MyProject
    src/main.cpp
    src/CourseManagement/Course.cpp
    src/CourseManagement/CourseManager.cpp
    src/ValidationTools/Err.cpp
    src/ValidationTools/Validator.cpp
    src/Sorters/BubbleSort.cpp
    src/Sorters/MergeSort.cpp
    src/Sorters/Sorter.cpp
    src/Sorters/QuickSort.cpp
    src/Sorters/Timer.cpp
    src/FileManagement/Benchmarker.cpp
    src/Database/DataManager.cpp
    src/Database/User.cpp
    src/Database/Recorder.cpp
)

# Add include folder
target_include_directories(MyProject PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(MyProject PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

configure_file(seedInput.csv seedInput.csv COPYONLY)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set_property(TARGET MyProject PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries(MyProject PRIVATE sqlite3)
