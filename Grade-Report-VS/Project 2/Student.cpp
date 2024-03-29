/*
	Creates the info for a student
*/

#include "Student.h"
#include "Course.h"

#include <iostream>
#include <iomanip>

using namespace std;

void Student::getName(string& aFirstName, std::string& aLastName) const
{
	aFirstName = firstName;
	aLastName = lastName;
}

void Student::setStudent(const Student& aStudent)
{
	studentID = aStudent.studentID;
	firstName = aStudent.firstName;
	lastName = aStudent.lastName;
	numberOfCourses = aStudent.numberOfCourses;
	tuitionWasPaid = aStudent.tuitionWasPaid;
	coursesCompleted = aStudent.coursesCompleted;
}

void Student::setStudentInfo(int newID, const string& newFirstName, 
	const string& newLastName, bool ifPaid, 
	const multimap<Course, char>& newCoursesCompleted)
{
	studentID = newID;
	firstName = newFirstName;
	lastName = newLastName;
	tuitionWasPaid = ifPaid;
	coursesCompleted = newCoursesCompleted;

	numberOfCourses = static_cast<int>(newCoursesCompleted.size());
}

string Student::getFirstName() const
{
	return firstName;
}

string Student::getLastName() const
{
	return lastName;
}

int Student::getID() const
{
	return studentID;
}

int Student::getNumberOfCourses() const
{
	return numberOfCourses;
}

int Student::getUnitsCompleted() const
{
	int totalUnits = 0;

	for (const auto& pair : coursesCompleted)
	{
		totalUnits += pair.first.getCourseUnits();
	}

	return totalUnits;
}

multimap<Course, char>Student::getCoursesCompleted() const
{
	return coursesCompleted;
}

char Student::getGrade(const string& aPrefix, int aCourseNum) const
{
	for (const auto& pair : coursesCompleted)
	{
		const Course& course = pair.first;
		if (course.getCoursePrefix() == aPrefix
			&& course.getCourseNumber() == aCourseNum)
		{
			return pair.second;
		}
	}
}

bool Student::isTuitionPaid() const
{
	return tuitionWasPaid;
}

bool Student::isCourseCompleted(const string& aPrefix, int aCourseNum) const
{
	for (const auto& pair : coursesCompleted)
	{
		const Course& course = pair.first;
		if (course.getCoursePrefix() == aPrefix 
			&& course.getCourseNumber() == aCourseNum)
		{
			return true;
		}
	}

	return false;
}

double Student::calculateGPA() const
{
	double totalGradePoints = 0.0;
	int totalCreditHours = 0;

	for (const auto& courseGradePair : coursesCompleted)
	{
		char grade = courseGradePair.second;
		int creditHours = courseGradePair.first.getCourseUnits();

		double gradePoints = 0.0;

		switch (grade)
		{
			case 'A':
				gradePoints = 4.0;
				break;
			case 'B':
				gradePoints = 3.0;
				break;
			case 'C':
				gradePoints = 2.0;
				break;
			case 'D':
				gradePoints = 1.0;
				break;
			case 'F':
				gradePoints = 0.0;
				break;
			default:
				break;
		}

		totalGradePoints += gradePoints * creditHours;
		totalCreditHours += creditHours;
	}

	if (totalCreditHours == 0)
	{
		return 0.0; // To avoid division by zero
	}

	double gpa = totalGradePoints / totalCreditHours;

	return gpa;
}

double Student::billingAmount(double tuitionRate) const
{
	return static_cast<double>(getNumberOfCourses()) * tuitionRate;
}

void Student::printStudent() const
{
	cout << studentID << " - " << lastName << ", " << firstName << endl;
}

void Student::printStudentInfo(double tuitionRate) const
{
	cout << "\nStudent Name: " << lastName << ", " << firstName << endl;
	cout << "Student ID: " << studentID << endl;
	cout << "Number of courses completed: " << numberOfCourses << endl;
	cout << endl;
	cout << left << setw(10) << "CourseNo" << setw(8) 
		<< "Units" << setw(8) << "Grade" << endl;

	for (const auto& pair : coursesCompleted)
	{
		const Course& course = pair.first;
		char grade = pair.second;

		cout.precision(3);
		cout << setprecision(2) << fixed;

		cout << left << setw(12) 
			<< (course.getCoursePrefix() + " " 
				+ to_string(course.getCourseNumber()))
			<< setw(8) << course.getCourseUnits() << setw(8) << grade << endl;
	}

	cout << endl;
	cout << "Total number of credit hours: " << getUnitsCompleted() << endl;

	if (isTuitionPaid())
	{
		cout << "Current Term GPA: " << calculateGPA() << endl;
	}
	else
	{
		cout << "*** Grades are being held for not paying the tuition. ***\n";
		cout << "Amount Due: $" << billingAmount(tuitionRate) << endl;
	}

	cout << "\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n";
}
