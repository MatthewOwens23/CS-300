#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

// Course structure
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Binary Search Tree Node
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;

    // Insert a course into the BST
    void insertNode(Node* node, Course course) {

        if (course.courseNumber < node->course.courseNumber) {

            if (node->left == nullptr) {
                node->left = new Node(course);
            }
            else {
                insertNode(node->left, course);
            }
        }
        else {

            if (node->right == nullptr) {
                node->right = new Node(course);
            }
            else {
                insertNode(node->right, course);
            }
        }
    }
        // Traverse BST in sorted order
    void inOrder(Node* node) {

        if (node == nullptr) {
            return;
        }

        inOrder(node->left);

        cout << node->course.courseNumber
            << ", "
            << node->course.courseTitle
            << endl;

        inOrder(node->right);
    }
    

public:
    BinarySearchTree() {
        root = nullptr;
    }

    
      void Insert(Course course) {

        if (root == nullptr) {
            root = new Node(course);
        }
        else {
            insertNode(root, course);
        }
    }
        // Search BST for a specific course
        Course Search(string courseNumber) {

            for (size_t i = 0; i < courseNumber.length(); i++) {
                courseNumber[i] = toupper(courseNumber[i]);
            }

            Node* current = root;

        while (current != nullptr) {

            if (current->course.courseNumber == courseNumber) {
                return current->course;
            }

            if (courseNumber < current->course.courseNumber) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        Course emptyCourse;
        emptyCourse.courseNumber = "";

        return emptyCourse;
    }
        // Print courses in alphanumeric order
    void PrintCourseList() {
        inOrder(root);
    }
    

};

// Load courses from CSV file
void loadCourses(string fileName, BinarySearchTree& courseTree) {

    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    string line;

    while (getline(file, line)) {

        stringstream ss(line);
        string token;

        Course course;

        // Course Number
        getline(ss, token, ',');
        course.courseNumber = token;

        // Course Title
        getline(ss, token, ',');
        course.courseTitle = token;

        // Prerequisites
        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token);
        }

        courseTree.Insert(course);
    }

    file.close();

    cout << "Courses loaded successfully." << endl;

}

// Main program menu loop
int main() {
    BinarySearchTree courseTree;
    bool dataLoaded = false;

    int choice = 0;
    string courseNumber;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {

        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";

        cin >> choice;

        switch (choice) {

        case 1:

            if (!dataLoaded) {

                string fileName;

                cout << "Enter file name: ";
                cin.ignore();
                getline(cin, fileName);

                loadCourses(fileName, courseTree);
                dataLoaded = true;
            }
            else {
                cout << "Data has already been loaded." << endl;
            }

            break;

        case 2:

            if (!dataLoaded) {
                cout << "Please load the data file first." << endl;
                break;
            }

            cout << endl;
            cout << "Here is a sample schedule:" << endl;
            cout << endl;

            courseTree.PrintCourseList();

            break;

        case 3:

            if (!dataLoaded) {
                cout << "Please load the data file first." << endl;
                break;
            }

            cout << endl;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;

            {
                Course course = courseTree.Search(courseNumber);

                if (course.courseNumber != "") {

                    cout << endl;
                    cout << course.courseNumber << ", "
                        << course.courseTitle << endl;

                    cout << "Prerequisites: ";

                    if (course.prerequisites.empty()) {
                        cout << "None";
                    }
                    else {

                        for (size_t i = 0; i < course.prerequisites.size(); i++) {

                            cout << course.prerequisites[i];

                            if (i < course.prerequisites.size() - 1) {
                                cout << ", ";
                            }
                        }
                    }

                    cout << endl;
                }
                else {
                    cout << "Course not found." << endl;
                }
            }

            break;

        case 9:

            cout << "Thank you for using the course planner!" << endl;

            break;

        default:

            cout << choice
                << " is not a valid option."
                << endl;
        }
    }

    return 0;

}