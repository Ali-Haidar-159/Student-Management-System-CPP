#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

struct Student {
    string id;
    string password;
    vector<string> courses;
    float cgpa;

    void display() {
        cout << "ID: " << id << "\nCourses: ";
        for (const string& course : courses) {
            cout << course << " ";
        }
        cout << "\nCGPA: " << cgpa << endl;
    }
};

// Function prototypes
void saveStudents(const vector<Student>& students);
void loadStudents(vector<Student>& students);
bool login(const vector<Student>& students, string& id);
void addCourse(Student& student, const string& course);
void dropCourse(Student& student, const string& course);
void displayCGPA(const Student& student);
void quickSort(vector<string>& courses, int low, int high);
int binarySearch(const vector<string>& courses, const string& course);
void teacherAddCourse(Student& student, const string& course);
void teacherDropCourse(Student& student, const string& course);

// Quick Sort algorithm
void quickSort(vector<string>& courses, int low, int high) {
    if (low < high) {
        string pivot = courses[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (courses[j] < pivot) {
                i++;
                swap(courses[i], courses[j]);
            }
        }
        swap(courses[i + 1], courses[high]);
        int pi = i + 1;

        quickSort(courses, low, pi - 1);
        quickSort(courses, pi + 1, high);
    }
}

// Binary Search algorithm
int binarySearch(const vector<string>& courses, const string& course) {
    int left = 0;
    int right = courses.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (courses[mid] == course)
            return mid;
        else if (courses[mid] < course)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Main function
int main() {
    // Create and write initial data to students.txt
    ofstream outFile("students.txt");
    outFile << "123 password123 3.5 CS101 END\n";
    outFile << "456 password456 3.7 CS102 END\n";
    outFile << "789 password789 3.8 CS103 END\n";
    outFile.close();

    vector<Student> students;
    loadStudents(students);

    string id, password;
    if (!login(students, id)) {
        cout << "Login failed!" << endl;
        return 1;
    }

    // Simulated student actions
    for (Student& student : students) {
        if (student.id == id) {
            string action;
            while (true) {
                cout << "1. Add Course\n2. Drop Course\n3. View CGPA\n4. Exit\n";
                cin >> action;

                if (action == "1") {
                    string course;
                    cout << "Enter course to add: ";
                    cin >> course;
                    addCourse(student, course);
                } else if (action == "2") {
                    string course;
                    cout << "Enter course to drop: ";
                    cin >> course;
                    dropCourse(student, course);
                } else if (action == "3") {
                    displayCGPA(student);
                } else {
                    break;
                }
            }
            break;
        }
    }

    saveStudents(students);
    return 0;
}

// Function implementations
void saveStudents(const vector<Student>& students) {
    ofstream outFile("students.txt");
    for (const Student& student : students) {
        outFile << student.id << " " << student.password << " " << student.cgpa << " ";
        for (const auto& course : student.courses) {
            outFile << course << " ";
        }
        outFile << "END" << endl;
    }
    outFile.close();
}

void loadStudents(vector<Student>& students) {
    ifstream inFile("students.txt");
    if (!inFile) return;

    Student student;
    while (inFile >> student.id >> student.password >> student.cgpa) {
        string course;
        while (inFile >> course && course != "END") {
            student.courses.push_back(course);
        }
        students.push_back(student);
    }
    inFile.close();
}

bool login(const vector<Student>& students, string& id) {
    cout << "Enter ID: ";
    cin >> id;
    string password;
    cout << "Enter Password: ";
    cin >> password;

    for (const Student& student : students) {
        if (student.id == id && student.password == password) {
            return true;
        }
    }
    return false;
}

void addCourse(Student& student, const string& course) {
    student.courses.push_back(course);
    quickSort(student.courses, 0, student.courses.size() - 1);
}

void dropCourse(Student& student, const string& course) {
    int index = binarySearch(student.courses, course);
    if (index != -1) {
        student.courses.erase(student.courses.begin() + index);
    } else {
        cout << "Course not found!" << endl;
    }
}

void displayCGPA(const Student& student) {
    cout << "Current CGPA: " << student.cgpa << endl;
}

void teacherAddCourse(Student& student, const string& course) {
    addCourse(student, course);
}

void teacherDropCourse(Student& student, const string& course) {
    dropCourse(student, course);
}
