#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Define the Course structure
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Function to read and store courses from the file
vector<Course> readAndStoreCourses(const string& filename) {
    vector<Course> coursesVector;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open or read file." << endl;
        return coursesVector;
    }

    string line;
    while (getline(file, line)) {
        vector<string> tokens;
        string token;
        stringstream ss(line);
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {
            cout << "Error: Insufficient parameters on line: " << line << endl;
            continue;
        }

        string courseNumber = tokens[0];
        string courseTitle = tokens[1];
        vector<string> prerequisites;
        for (size_t i = 2; i < tokens.size(); ++i) {
            prerequisites.push_back(tokens[i]);
        }

        Course course = { courseNumber, courseTitle, prerequisites };
        coursesVector.push_back(course);
    }

    file.close();
    return coursesVector;
}

// Function to print the list of courses in alphanumeric order
void printCourseList(const vector<Course>& courses) {
    vector<Course> sortedCourses = courses;
    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    for (const auto& course : sortedCourses) {
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}

// Function to print course information given the course number
void printCourseInformation(const vector<Course>& courses, const string& courseNumber) {
    // Search for the course with the given course number
    for (const auto& course : courses) {
        if (course.courseNumber == courseNumber) {
            cout << "Course Number: " << course.courseNumber << endl;
            cout << "Course Title: " << course.courseTitle << endl;
            cout << "Prerequisites: ";
            if (course.prerequisites.empty()) {
                cout << "None";
            }
            else {
                for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                    cout << course.prerequisites[i];
                    if (i != course.prerequisites.size() - 1) {
                        cout << ", ";
                    }
                }
            }
            cout << endl;
            return; // Exit the function after printing course information
        }
    }
    // If the course number is not found, print an error message
    cout << "Error: Course not found." << endl;
}

// Function to display the menu options
void displayMenu() {
    cout << "Menu Options:" << endl;
    cout << "1. Load Data Structure" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course" << endl;
    cout << "4. Exit" << endl;
}

int main() {
    vector<Course> courses;

    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
        {
            string filename;
            cout << "\nFor this example Use filename: courseData.csv" << endl;
            cout << "Enter the name of the file: ";
            cin >> filename;
            courses = readAndStoreCourses(filename);
            cout << "\nData loaded successfully!\n" << endl;
            break;
        }
        case 2:
            if (courses.empty()) {
                cout << "Error: Data structure is empty. Load data first." << endl;
            }
            else {
                cout << "List of Courses:" << endl;
                printCourseList(courses);
            }
            break;
        case 3:
            if (courses.empty()) {
                cout << "Error: Data structure is empty. Load data first." << endl;
            }
            else {
                string courseNumber;
                cout << "Enter the course number: ";
                cin >> courseNumber;
                printCourseInformation(courses, courseNumber); // Call the function to print course information
            }
            break;
        case 4:
            cout << "Exiting the program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
    }

    return 0;
}

