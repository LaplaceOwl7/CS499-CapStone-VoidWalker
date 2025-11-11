# CS-499 Project Enhancement Checklist

---

## General / Global Improvements

- [ ] Refactor spaghetti code into modular, class-based design  
- [ ] Split code into multiple header (`.h`) and source (`.cpp`) files  
- [ ] Enforce consistent naming conventions across all files  
- [ ] Add detailed in-line comments and external documentation  
- [ ] Implement structured error handling and input validation  
- [ ] Integrate logging for runtime errors and user actions  
- [ ] Apply input sanitization to all user-facing operations  
- [ ] Implement defensive programming and secure coding practices  
- [ ] Create UML class and flow diagrams for clarity  
- [ ] Include pseudocode and flowcharts for each major process  
- [ ] Add benchmarking for performance analysis  
- [ ] Maintain code readability and scalability  
- [ ] Use GitHub for version control and professional documentation  
- [ ] Demonstrate code review and reflective design practices  

---

## Category One: Software Engineering & Design

### Object-Oriented Refactoring
- [X] Create a `Course` class for course objects  
- [ ] Create a `CourseManager` class to handle CSV/database operations  
- [ ] Add a main controller or menu system to manage program flow  
- [ ] Separate UI/menu logic from data and backend logic  

### Architecture & Maintainability
- [ ] Modularize project into logical components  
- [ ] Implement encapsulation and abstraction (hide internal data, expose clear interfaces)  
- [ ] Use design patterns where appropriate (factory, strategy, etc.)  
- [ ] Add UML diagrams for design validation and communication  

### Security & Stability
- [ ] Add input sanitization for course input data  
- [ ] Catch malformed CSV input and handle gracefully  
- [ ] Implement file validation and format checking  
- [ ] Add error logging class to write to file  

### Professional Practices
- [ ] Document design rationale and class responsibilities  
- [ ] Justify architectural trade-offs and pattern choices  
- [ ] Ensure maintainability and scalability are demonstrated 

### Journal
- Briefly describe the artifact. 
	- What is it? 
	- When was it created?
- Justify the inclusion of the artifact in your ePortfolio. 
	- Why did you select this item? 
	- What specific components of the artifact showcase your skills and abilities in software development?
	- How was the artifact improved?
- Did you meet the course outcomes you planned to meet with this enhancement in Module One? 
	- Do you have any updates to your outcome-coverage plans?
- Reflect on the process of enhancing and modifying the artifact. 	- What did you learn as you were creating it and improving it? 	
	- What challenges did you face?

---

## Category Two: Algorithms & Data Structures

### Algorithm Implementation
- [ ] Implement multiple sorting algorithms:
  - [ ] Bubble Sort (refactored)
  - [ ] Merge Sort
  - [ ] Quick Sort
  - [ ] Insertion Sort *(optional)*
  - [ ] Bucket Sort *(optional)*
  - [ ] Radix Sort *(optional)*
- [ ] Add abstraction layer: base `Sorter` class with polymorphism  

### Performance & Benchmarking
- [ ] Add benchmarking module:
  - [ ] Record execution time in milliseconds  
  - [ ] Compare runtime across algorithms  
  - [ ] Generate formatted summary report  
- [ ] Analyze time and space complexity for each algorithm  
- [ ] Document O-complexity (best, average, worst case)  

### Data Management
- [ ] Move all course data into a vector for dynamic resizing  
- [ ] Maintain consistent data handling between algorithms  

### Documentation
- [ ] Include Markdown reports on algorithm performance and use cases  
- [ ] Clearly explain algorithm choice and trade-offs  

---

## Category Three: Databases

### Transition to Database
- [ ] Replace CSV with a SQLite relational database  
- [ ] Define relational schema with constraints:
  - [ ] `courseID` as `PRIMARY KEY`
  - [ ] `courseName` as `NOT NULL`
- [ ] Parameterize all SQL queries (prevent injection attacks)  

### CRUD Implementation
- [ ] Implement full CRUD operations:
  - [ ] `addCourse()`
  - [ ] `removeCourse()`
  - [ ] `updateCourse()`
  - [ ] `fetchAllCourses()`
  - [ ] `searchCourseById()`
  - [ ] `searchCourseByName()`
- [ ] Integrate CRUD into the `CourseManager` class  

### Database Management
- [ ] Add database connection and disconnection handling  
- [ ] Log all user actions into separate log files  
- [ ] Include schema creation on first connection  

### User Interface / Interaction
- [ ] Add user menu options:
  - [ ] “Load Courses”
  - [ ] “Add Course”
  - [ ] “Delete Course”
  - [ ] “Display Course”
  - [ ] “Export Sorted Courses”  

### Security & Design
- [ ] Enforce unique course IDs  
- [ ] Use parameterized queries for injection prevention  
- [ ] Separate SQL logic from main application logic (data access layer abstraction)  

---

## ePortfolio / Professional Demonstration

- [ ] Document reasoning for each enhancement (design, performance, or security-based)  
- [ ] Include diagrams and pseudocode for professional presentation  
- [ ] Reflect on design decisions and trade-offs  
- [ ] Present algorithm performance results in visual/graph form  
- [ ] Include a short self-assessment explaining development growth  
- [ ] Ensure GitHub Pages portfolio clearly links to all artifacts  
- [ ] Maintain project with public access for employer review  

---

