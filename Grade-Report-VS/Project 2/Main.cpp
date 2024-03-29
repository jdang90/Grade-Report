/*
    Nguyen, An (Team Leader)
    Nguyen, Justin
    Chen, Shanqin
    Dang, Justin

    Project: Grade Report
    CS A250
    Fall 2023
*/

#include "Course.h"
#include "Student.h"
#include "StudentList.h"
#include "InputHandler.h"
#include "OutputHandler.h"

#include <iostream>
#include <fstream>

using namespace std;

const string FILE_NAME = "student_data.txt";

void displayMenu();
void processChoice(const StudentList& aObject, double tuitionRate);

int main()
{
    StudentList newStudentList;

    double tuitionRate = 0.0;

    readStudentData(FILE_NAME, newStudentList, tuitionRate);

    processChoice(newStudentList, tuitionRate);

    cout << endl;
    system("Pause");
    return 0;
}

void displayMenu()
{
    cout << "\n*** MAIN MENU ***" << endl;
    cout << "\nSelect one of the following:\n" << endl;
    cout << "   1: Print all students" << endl;
    cout << "   2: Print student information" << endl;
    cout << "   3: Search student by last name" << endl;
    cout << "   4: Print students by course" << endl;
    cout << "   5: Print students on hold" << endl;
    cout << "   6: Print students to file" << endl;
    cout << "   7: Print students by grade" << endl;
    cout << "   8: To exit\n" << endl;
}

void processChoice(const StudentList& aObject, double tuitionRate)
{
    bool finish = false;

    while (!finish)
    {
        displayMenu();

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                aObject.printAllStudents(tuitionRate);
                break;
            }
            case 2:
            {
                int studentID;
                cout << "\nPlease enter student's ID: ";
                cin >> studentID;
                aObject.printStudentByID(studentID, tuitionRate);
                break;
            }
            case 3:
            {
                string lastName;
                cout << "\nPlease enter the student's last name: ";
                cin >> lastName;
                cout << endl;
                aObject.printStudentByName(lastName);
                break;
            }
            case 4:
            {
                string coursePrefix;
                cout << "\nPlease enter the course prefix: ";
                cin >> coursePrefix;

                int courseNumber;
                cout << "Please enter the course number: ";
                cin >> courseNumber;
                cout << endl;

                aObject.printStudentsByCourse(coursePrefix, courseNumber);
                break;
            }
            case 5:
            {
                cout << endl;
                aObject.printStudentsOnHold(tuitionRate);
                break;
            }
            case 6:
            {
                string newFileName;
                cout << "\nEnter a name for a new file to write on (include extension.txt) :\n";
                cin >> newFileName;

                ofstream newFile(newFileName, ios::out);
                aObject.printStudentsToFile(newFile, tuitionRate);
                break;
            }
            case 7:
            {
                string coursePrefix;
                cout << "\nPlease enter the course prefix: ";
                cin >> coursePrefix;

                int courseNumber;
                cout << "\nPlease enter the course number: ";
                cin >> courseNumber;

                char grade;
                cout << "\nPlease enter the grade (A-F): ";
                cin >> grade;

                aObject.printStudentsByGrade(coursePrefix,
                    courseNumber, grade);

                break;
            }
            case 8:
            {
                finish = true;
                cout << "\nThank you for using the OCC Gradebook. Good-bye!\n";
                break;
            }
            default:
            {
                cout << "\nSorry. That is not a selection." << endl;
                break;
            }
        }

        cout << endl;

        system("pause");
    }
}
