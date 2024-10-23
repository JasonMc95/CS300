#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

class Course {
public:
    std::string courseId;
    std::string title;
    std::vector<std::string>prerequisites;
    Course() {}
    Course(std::string id, std::string name, std::vector<std::string> prereqs)
        :courseId(id), title(name), prerequisites(prereqs) {}
};

void displayMenu();
void loadCoursesFromFile(const std::string& filename, std::vector<Course>& courses);
void printCoursesList(std::vector<Course>& courses);
void printCourse(std::vector<Course>& courses, std::string courseId);

int main() {

    std::vector<Course> courses;
    int option = 1;

    while (option != 9) {
        displayMenu();
        std::cout << "Enter option: ";
        std::cin >> option;

        if (option == 1) {
            loadCoursesFromFile("CS 300 ABCU_Advising_Program_Input.csv", courses);
        }
        else if (option == 2) {
            printCoursesList(courses);
        }
        else if (option == 3) {
            std::cout << "Enter course id to print: ";
            std::string id;
            std::cin >> id;
            printCourse(courses, id);
        }
        else if (option == 9) {
        }
        else {
            std::cout << "Invalid Option" << std::endl;
        }
    }
    return 0;
}

void displayMenu() {
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Load Data" << std::endl;
    std::cout << "2. Print Course List" << std::endl;
    std::cout << "3. Print Course" << std::endl;
    std::cout << "9. Exit" << std::endl;
}

void loadCoursesFromFile(const std::string& filename, std::vector<Course>& courses) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file" << filename << std::endl;
        return;
    }
    std::string data;
    while (std::getline(file, data)) {
        std::istringstream ss(data);
        std::string courseId, title, prereq; ///Create variables to temp store
        std::vector<std::string> prereqs;
        std::getline(ss, courseId, ','); ///Read cell by cell, separated by commas
        std::getline(ss, title, ',');
        while (std::getline(ss, prereq, ',')) {
            prereqs.push_back(prereq); ///Create a vector of prerequisites for that course
        }
        courses.push_back(Course(courseId, title, prereqs));  ///Appends all the temp variables
    }

    file.close();
}

void printCoursesList(std::vector<Course>& courses) {
    std::vector<std::string> courseIds;
    for (const auto& course : courses) {
        courseIds.push_back(course.courseId);
    }
    std::sort(courseIds.begin(), courseIds.end());
    for (const auto& id : courseIds) {
        // Find the course in the vector by courseId
        auto it = std::find_if(courses.begin(), courses.end(), [&id](const Course& course) {
            return course.courseId == id;
            });
        if (it != courses.end()) {
            std::cout << id << ": " << it->title << std::endl;
        }
    }
}

void printCourse(std::vector<Course>& courses, std::string courseId) {
    auto it = std::find_if(courses.begin(), courses.end(), [&courseId](const Course& course) {
        return course.courseId == courseId;
        });

    if (it == courses.end()) {
        std::cerr << "Error: Course " << courseId << " not found" << std::endl;
        return;
    }

    Course& course = *it;
    std::cout << "Course ID: " << course.courseId << std::endl;
    std::cout << "Title: " << course.title << std::endl;
    std::cout << "Prerequisites: ";
    for (const auto& prereq : course.prerequisites) {
        std::cout << prereq << " ";
    }
    std::cout << std::endl;
}

