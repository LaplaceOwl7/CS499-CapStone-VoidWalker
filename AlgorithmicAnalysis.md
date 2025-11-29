# Algorithmic Analysis

## Algorithms

A fundamental consideration in designing any application is the algorithmic efficiency. Algorithms are broadly defined as a sequence of logical steps taken to achieve a purpose. In computer science, we have different algorithms to sort, search, name, etc.

## Big O Notation

*Big O* notation explains how functions grow in complexity as the sample size grows toward infinity. Big O usually has a positive correlation with an algorithm's running time and memory usage. Higher Big O growth rates become ineffective against large sample sizes.

Big O provides upper bounds, explaining the resource usage assuming a “worst‐case” where the output is found at the longest sequence of steps. This gives a machine-independent way to measure time and space usage.

### Interpreting Big O

Big O is often represented in mathematical growth functions where *n* is the independent variable and complexity is the dependent variable.

| Notation       | Name                | Meaning                                                                 |
|----------------|---------------------|-------------------------------------------------------------------------|
| O(1)           | Constant time       | Running time does not depend on input size.                            |
| O(log n)       | Logarithmic time    | Running time grows slowly;doubling input adds a constant extra cost.   |
| O(n)           | Linear time         | Running time grows in direct proportion to input size.                 |
| O(n log n)     | Linearithmic        | Slightly more than linear; common in efficient sorts/merge algorithms.  |
| O(n²)          | Quadratic time      | Running time grows like the square of input size—becomes expensive.    |
| O(2ⁿ)          | Exponential time    | Running time doubles with each added input element—feasible only for small n. |

---

## Average-Case Complexity

Average‐case complexity describes how quickly the expected running time grows when input size increases, under some assumed input distribution. Big O notation still applies for average case though has a different meaning. 

---

## Types

There are four sorting algorithms implemented in this project:
- Bubblesort  
- Quicksort  
- Mergesort  
- Standard sort

### Bubblesort

#### Description  
Bubblesort works by traversing an array, comparing adjacent elements, swapping them only if they’re out of order. Each pass causes the largest remaining unsorted elements (“the bubble”) to correctly move to the end.

#### Perks  
- Easy to implement and understand  
- Works in-place; does not need large copies  
- Can be augmented to abort early in the best case  
- Stable; equal elements maintain their relative order  
- Big O:  
  - Best Case: O(n)  
  - Average Case: O(n²)  
  - Worst Case: O(n²)

#### Drawbacks  
- Complexity grows rapidly as *n* increases; not suitable for large arrays  
- Rarely used in production; better alternatives exist  

#### Source Code  
Bubblesort is implemented in `Sorters/BubbleSort.cpp`

```cpp
// Check if the array is large enough to perform a sort.
if (courses.size() < 2) {
    // Aborts via a return if not
}
// Set a conditional to verify if something needs to be sorted.
bool swapped; 
    
// Begin to iterate through the array.
for (int i = 0; i < courses.size() - 1; i++) {
    swapped = false;
    for (int j = 0; j < courses.size() - i - 1; j++) {
        if (courses[j].getCourseID() > courses[j + 1].getCourseID()) {
            std::swap(courses[j], courses[j + 1]);
            swapped = true;
        }
    }
    if (!swapped) {
        break;
    }
}
```

### Quicksort

#### Description

Quicksort is a divide-and-conquer algorithm that chooses a pivot element, partitions the array into elements less than and greater than the pivot, then recursively sorts those partitions until the full array is sorted.

#### Perks

- Excellent average‐case speed

- In-place sorting (no large copies)

- Efficient for large arrays when implementation is tuned

- Big O:
  - Best Case: O(n log n)
  - Average Case: O(n log n)
  - Worst Case: O(n²)

##### Drawbacks

- Not stable (unless implemented specially)

- Poor pivot choice or adversarial input can degrade performance

##### Pseudocode

Implemented in `Sorters/Quicksort.cpp`

```
function QUICK_SORT(courses):
    if size(courses) </= 1:
        return courses
    QUICK_SORT_IMPL(courses, low = 0, high = size(courses) - 1)
    return courses

function PARTITION(courses, low, high):
    pivot = courses[high]
    pivotId = pivot.courseID
    i = low - 1
    for j from low to high - 1:
        if courses[j].courseID <= pivotId:
            i = i + 1
            swap courses[i] with courses[j]
    swap courses[i + 1] and courses[high]
    return i + 1

function QUICK_SORT_IMPL(courses, low, high):
    if low < high:
        pivotIndex = PARTITION(courses, low, high)
        QUICK_SORT_IMPL(courses, low, pivotIndex - 1)
        QUICK_SORT_IMPL(courses, pivotIndex + 1, high)
```

### Mergesort
#### Description

Mergesort also uses divide-and-conquer by splitting the array into two halves, recursively sorting each half, then merging the sorted halves into a single sorted array.

#### Perks

- Stable (preserves relative order of equal elements)
- Predictable performance: best/average/worst all ~ O(n log n)
- Good when worst‐case guarantees are important
- Big O:
  - Best Case: O(n log n)
  - Average Case: O(n log n)
  - Worst Case: O(n log n)

#### Drawbacks
- Requires additional space (O(n) auxiliary) unless specialised in-place version
- Slightly higher constant overhead than some tuned quicksorts
#### Pseudocode

Implementation in `Sorters/Mergesort.cpp`

```
function MERGE_SORT(courses):
    if size(courses) ≤ 1:
        return courses
    MERGE_SORT_IMPL(courses, left = 0, right = size(courses) − 1)
    return courses

function MERGE_SORT_IMPL(courses, left, right):
    if left ≥ right:
        return
    mid = left + (right − left) / 2
    MERGE_SORT_IMPL(courses, left, mid)
    MERGE_SORT_IMPL(courses, mid + 1, right)
    MERGE(courses, left, mid, right)

function MERGE(courses, left, mid, right):
    leftSize  = mid − left + 1
    rightSize = right − mid
    leftVec   = new array[leftSize]
    rightVec  = new array[rightSize]
    for i from 0 to leftSize − 1:
        leftVec[i] = courses[left + i]
    for j from 0 to rightSize − 1:
        rightVec[j] = courses[mid + 1 + j]
    i = 0; j = 0; k = left
    while i < leftSize and j < rightSize:
        if leftVec[i].courseID < rightVec[j].courseID:
            courses[k++] = leftVec[i++]
        else:
            courses[k++] = rightVec[j++]
    while i < leftSize:
        courses[k++] = leftVec[i++]
    while j < rightSize:
        courses[k++] = rightVec[j++]
```

### Standard Sort
#### Description

The C++ standard sorting algorithm std::sort (from <algorithm>) is usually implemented as a hybrid (often introsort) combining quicksort, heapsort and insertion sort depending on input size and recursion depth needed

#### Perks
- Highly optimized in the standard library
- Very easy to use
- Flexible (works on any random‐access iterator, custom comparators)
- Big O:
  - Average Case: O(n log n)
  - Worst Case: O(n log n) (in many implementations thanks to fallback to heapsort)

#### Drawbacks

Not stable by default (use std::stable_sort if stability required)

#### Source Code Usage:

```
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
```

### Algorithmic Analysis for this Project

The file `seedInput.csv` provides a test of 120 instances of courses that would typically be found in a university. Running each algorithmic benchmark 100 times, provides validation on the Big O notation. Below is a table exploring each algorithm's average time in miliseconds as the input size rises:

| Input Size| QuickSort | BubbleSort | MergeSort | StandardSort| 
|-|-|-|-|-|
| 10  | 19 | 53 | 10 | 12 | 
| 50  | 216 | 237 | 99 | 49 |
| 120 | 911 | 460 | 160 | 103 |
| 500 | 13396 | 2026 | 616 | 396 |

The best algorithm? The standard **C++'s Standard Sort**


#### References and Sources

[Time and Space Complexity Analysis of Bubble Sort, GeeksForGeeks](https://www.geeksforgeeks.org/dsa/time-and-space-complexity-analysis-of-bubble-sort/)

[Time Complexity of Bubble Sort, Code Academy](https://www.codecademy.com/article/time-complexity-of-bubble-sort)

[Quicksort, Wikipedia](https://en.wikipedia.org/wiki/Quicksort)

[Time and Space Complexity Analysis of Merge Sort, GeeksForGeeks](https://www.geeksforgeeks.org/dsa/time-and-space-complexity-analysis-of-merge-sort/)

[std::sort - C++ Reference, CPP Reference](https://en.cppreference.com/w/cpp/algorithm/sort.html)