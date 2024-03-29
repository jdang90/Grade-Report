/*
	Creates output for a student's information.
*/

#include "StudentList.h"
#include "Course.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

using namespace std;

void StudentList::addStudent(const Student& newStudent)
{
	Node* newNode = new Node(newStudent, nullptr);

	if (!first)
	{
		first = last = newNode;
	}
	else
	{
		last->setNext(newNode);
		last = newNode;
	}

	count++;
}

int StudentList::getNoOfStudents() const
{
	return count;
}

void StudentList::printStudentByID(int id, double tuitionRate) const
{
	Node* current = first;
	bool found = false;

	while (current)
	{
		if (current->getStudent().getID() == id && !found)
		{
			found = true;
			current->getStudent().printStudentInfo(tuitionRate);
		}
		current = current->getNext();
	}

	if (!found)
	{
		cout << "\nNo students with ID " << id << " found in the list.\n";
	}
}

void StudentList::printStudentByName(const string& lastName) const 
{
	Node* current = first;
	bool found = false;

	while (current)
	{
		if (current->getStudent().getLastName() == lastName)
		{
			found = true;
			current->getStudent().printStudent();
		}
		current = current->getNext();
	}

    if (!found)
    {
        cout << "No student with last name " << lastName 
			<< " is on the list." << endl;
    }
}

void StudentList::printStudentsByCourse(const string& coursePrefix, 
	int courseNumber) const 
{
	Node* current = first;
	bool found = false;

	while (current)
	{
		if (current->getStudent().isCourseCompleted(coursePrefix,
			courseNumber))
		{
			found = true;
			current->getStudent().printStudent();
		}
		current = current->getNext();
	}

	if (!found)
	{
		cout << "No students enrolled in " << coursePrefix << " " 
			<< courseNumber << "." << endl;
	}
}

void StudentList::printStudentsByGrade(const string& coursePrefix,
	int courseNumber, char grade) const 
{
	if (grade < 'A' || grade > 'F')
	{
		cerr << "Error: Invalid grade entered. Grade should be between A and F.\n";
	}
	else
	{
		const int MAX_STUDENTS = 100; 
		Student studentsWithGrade[MAX_STUDENTS];
		int count = 0;

		Node* current = first;
		while (current && count < MAX_STUDENTS) 
		{
			if (current->getStudent().getGrade(coursePrefix, 
					courseNumber) == grade) 
			{
				studentsWithGrade[count++] = current->getStudent();
			}
			current = current->getNext();
		}

		if (count > 0)
		{
			for (int i = 0; i < count - 1; ++i) 
			{
				for (int j = 0; j < count - i - 1; ++j) 
				{
					if (studentsWithGrade[j].calculateGPA() < 
							studentsWithGrade[j + 1].calculateGPA()) 
					{
						Student temp = studentsWithGrade[j];
						studentsWithGrade[j] = studentsWithGrade[j + 1];
						studentsWithGrade[j + 1] = temp;
					}
				}
			}

			for (int i = 0; i < count; ++i) 
			{
				studentsWithGrade[i].printStudent();
			}
		}
		else 
		{
			cout << "No students have received grade " << grade << " in "
				<< coursePrefix << " " << courseNumber << ".\n";
		}
	}
}

void StudentList::printAllStudents(double tuitionRate) const 
{
	Node* current = first;

	while (current)
	{
		current->getStudent().printStudentInfo(tuitionRate);
		current = current->getNext();
	}
}

void StudentList::printStudentsOnHold(double tuitionRate) const 
{
	Node* current = first;
	bool found = false;

	while (current) 
	{
		if (!current->getStudent().isTuitionPaid())
		{
			found = true;
			current->getStudent().printStudent();
			cout << setprecision(2) << fixed;
			cout << "    Amount Due: $" <<
				current->getStudent().billingAmount(tuitionRate) << endl;
		}

		current = current->getNext();
	}

	if (!found)
	{
		cout << "There are no students on hold.";
	}
}

void StudentList::printStudentsToFile(ofstream& outputFile,
	double tuitionRate) const
{
	Node* current = first;

	while (current != nullptr)
	{
		outputFile << "Student Name: " << current->getStudent().getLastName()
			<< ", " << current->getStudent().getFirstName() << endl;
		outputFile << "Student ID: " << current->getStudent().getID() << endl;
		outputFile << "Number of courses enrolled: "
			<< current->getStudent().getNumberOfCourses() << endl;
		outputFile << endl;
		outputFile << left << setw(10) << "CourseNo" << setw(8)
			<< "Units" << setw(8) << "Grade" << endl;
		
		for (const auto& pair : current->getStudent().getCoursesCompleted())
		{
			const Course& course = pair.first;
			char grade = pair.second;

			outputFile << left << setw(12)
				<< (course.getCoursePrefix() + " "
					+ to_string(course.getCourseNumber()))
				<< setw(8) << course.getCourseUnits() << setw(8) 
				<< grade << endl;
		}

		outputFile << "\nTotal number of credit hours: "
			<< current->getStudent().getUnitsCompleted() << endl;

		if (current->getStudent().isTuitionPaid())
		{
			outputFile << "Current Term GPA: "
				<< fixed << setprecision(2)
				<< current->getStudent().calculateGPA() << endl;
		}
		else
		{
			outputFile 
				<< "*** Grades are being held for not paying the tuition. ***\n";
			outputFile << "Amount Due: $"
				<< current->getStudent().getNumberOfCourses()
				* tuitionRate << endl;
		}

		outputFile 
			<< "\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n\n";

		current = current->getNext();
	}
}

void StudentList::clearStudentList()
{
	while (first != nullptr)
	{
		Node* temp = first;
		first = first->getNext();
		delete temp;
	}

	last = nullptr;
	count = 0;
}

StudentList::~StudentList()
{
	if (first == last)
		clearStudentList();
}
