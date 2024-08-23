//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Randy Phimmasen
// Version     : 1.0
// Description : Project Two
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

// Course class to hold course details
class Course {
public:
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;

    Course() {}  // Default constructor
    Course(std::string number, std::string title) : courseNumber(number), courseTitle(title) {}
};

// Function to load course data from a file
void loadCourseData(const std::string& fileName, std::map<std::string, Course>& courses) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error: Unable to open file " << fileName << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string courseNumber, courseTitle, prerequisite;
        std::getline(ss, courseNumber, ',');
        std::getline(ss, courseTitle, ',');
        Course course(courseNumber, courseTitle);
        while (std::getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }
        courses[courseNumber] = course;
    }
    file.close();
}

// Function to print the course list in alphanumeric order
void printCourseList(const std::map<std::string, Course>& courses) {
    std::vector<std::string> courseNumbers;
    for (const auto& pair : courses) {
        courseNumbers.push_back(pair.first);
    }
    std::sort(courseNumbers.begin(), courseNumbers.end());
    for (const auto& courseNumber : courseNumbers) {
        const Course& course = courses.at(courseNumber);
        std::cout << course.courseNumber << ", " << course.courseTitle << std::endl;
    }
}

// Function to print detailed information about a specific course
void printCourseInformation(const std::map<std::string, Course>& courses, const std::string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        const Course& course = it->second;
        std::cout << course.courseNumber << ", " << course.courseTitle << std::endl;
        if (!course.prerequisites.empty()) {
            std::cout << "Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                std::cout << course.prerequisites[i];
                if (i != course.prerequisites.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "Prerequisites: None" << std::endl;
        }
    }
    else {
        std::cerr << "Course not found: " << courseNumber << std::endl;
    }
}

// Main function with menu
int main() {
    std::map<std::string, Course> courses;
    int choice;
    std::string fileName;
    std::string courseNumber;

    std::cout << "Welcome to the course planner." << std::endl;
    while (true) {
        std::cout << "\n1. Load Data Structure." << std::endl;
        std::cout << "2. Print Course List." << std::endl;
        std::cout << "3. Print Course." << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter the file name to load: ";
            std::cin >> fileName;
            loadCourseData(fileName, courses);
            break;
        case 2:
            std::cout << "\nHere is a sample schedule:\n" << std::endl;
            printCourseList(courses);
            break;
        case 3:
            std::cout << "What course do you want to know about? ";
            std::cin >> courseNumber;
            printCourseInformation(courses, courseNumber);
            break;
        case 9:
            std::cout << "Thank you for using the course planner!" << std::endl;
            return 0;
        default:
            std::cerr << choice << " is not a valid option." << std::endl;
            break;
        }
    }
    return 0;
}
