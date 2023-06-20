#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <sstream>

using namespace std;

char HOST[] = "localhost";
char USER[] = "root";
char PASS[] = "*souvenir#";

MYSQL* obj; // MySQL object to manage the session

string intToString(int value) {
    stringstream ss;
    ss << value;
    return ss.str();
}

// Function to initialize the database connection
bool connectToDatabase() {
    obj = mysql_init(0);
    if (!mysql_real_connect(obj, HOST, USER, PASS, "school", 3306, NULL, 0)) {
        cout << "Failed to connect to the database." << endl;
        cout << mysql_error(obj) << endl;
        return false;
    }
    cout << "Connected to the database successfully!" << endl;
    return true;
}

// Function to close the database connection
void closeDatabaseConnection() {
    mysql_close(obj);
}

// Function to add a new student
void addStudent() {
    string id, name, email;
    cout << "Enter student details: " << endl;
    cout << "ID: ";
    cin.ignore();
    getline(cin, id);

    cout << "Name: ";
    getline(cin, name);
    cout << "Email: ";
    getline(cin, email);

    string query = "INSERT INTO students (id, name, email) VALUES ('" + id + "', '" + name + "', '" + email + "')";
    if (mysql_query(obj, query.c_str())) {
        cout << "Failed to add student: " << mysql_error(obj) << endl;
    } else {
        cout << "Student added successfully!" << endl;
    }
}

// Function to update an existing student
void updateStudent() {
    int id;
    cout << "Enter the ID of the student to update: ";
    cin >> id;

    // Check if the student exists
    string checkQuery = "SELECT * FROM students WHERE id = " + intToString(id);
    if (mysql_query(obj, checkQuery.c_str())) {
        cout << "Failed to execute query: " << mysql_error(obj) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(obj);
    int numFields = mysql_num_fields(result);

    if (mysql_num_rows(result) == 0) {
        cout << "Student not found!" << endl;
    } else {
        MYSQL_ROW row = mysql_fetch_row(result);

        // Display the current student information
        cout << "Current student details:" << endl;
        cout << "ID: " << row[0] << endl;
        cout << "Name: " << row[1] << endl;
        cout << "Email: " << row[2] << endl;

        // Prompt for new student details
        string name, email;
        cout << "Enter new student details: " << endl;
        cout << "Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Email: ";
        getline(cin, email);

        // Update the student information in the database
        string updateQuery = "UPDATE students SET name = '" + name + "', email = '" + email + "' WHERE id = " + intToString(id);
        if (mysql_query(obj, updateQuery.c_str())) {
            cout << "Failed to update student: " << mysql_error(obj) << endl;
        } else {
            cout << "Student updated successfully!" << endl;
        }
    }

    mysql_free_result(result);
}

// Function to delete a student by ID
void deleteStudent() {
    int id;
    cout << "Enter the ID of the student to delete: ";
    cin >> id;

    // Check if the student exists
    string checkQuery = "SELECT * FROM students WHERE id = " + intToString(id);
    if (mysql_query(obj, checkQuery.c_str())) {
        cout << "Failed to execute query: " << mysql_error(obj) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(obj);
    int numFields = mysql_num_fields(result);

    if (mysql_num_rows(result) == 0) {
        cout << "Student not found!" << endl;
    } else {
        // Delete the student from the database
        string deleteQuery = "DELETE FROM students WHERE id = " + intToString(id);
        if (mysql_query(obj, deleteQuery.c_str())) {
            cout << "Failed to delete student: " << mysql_error(obj) << endl;
        } else {
            cout << "Student deleted successfully!" << endl;
        }
    }

    mysql_free_result(result);
}

// Function to get all students' names
void getAllStudents() {
    string query = "SELECT name FROM students";
    if (mysql_query(obj, query.c_str())) {
        cout << "Failed to execute query: " << mysql_error(obj) << endl;
        return;
    }

    MYSQL_RES* result = mysql_store_result(obj);
    int numFields = mysql_num_fields(result);

    cout << "List of students:" << endl;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        cout << row[0] << endl;
    }

    mysql_free_result(result);
}

// Function to display the menu and perform actions based on user choice
void displayMenu() {
    int choice;
    bool exit = false;

    while (!exit) {
        cout << "------ Student Management System ------" << endl;
        cout << "1. Add student" << endl;
        cout << "2. Update existing student" << endl;
        cout << "3. Delete student by ID" << endl;
        cout << "4. Get all students" << endl;
        cout << "5. Exit" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                updateStudent();
                break;
            case 3:
                deleteStudent();
                break;
            case 4:
                getAllStudents();
                break;
            case 5:
                exit = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;
    }
}

int main() {
    if (connectToDatabase()) {
        displayMenu();
        closeDatabaseConnection();
    }

    return 0;
}

