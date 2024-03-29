/*
	Nguyen, An (Team Leader)
	Nguyen, Justin
	Chen, Shanqin
	Dang, Justin

	Project: Grade Report
	CS A250
	Fall 2023
*/

#ifndef STUDENT_H
#define STUDENT_H

#include "Course.h"

#include <string>
#include <map>

class Student
{
public:
	Student() : studentID(0), firstName("N/A"), lastName("N/A"), 
		numberOfCourses(0), tuitionWasPaid(false) {}

	void setStudent(const Student& aStudent);
	void setStudentInfo(int newID, const std::string& newFirstName, 
		const std::string& newLastName, bool ifPaid, 
		const std::multimap<Course, char>& newCoursesCompleted);

	std::string getFirstName() const;
	std::string getLastName() const;
	void getName(std::string& aFirstName, std::string& aLastName) const;
	int getID() const;
	int getNumberOfCourses() const;
	int getUnitsCompleted() const;
	char getGrade(const std::string& aPrefix, int aCourseNum) const;
	std::multimap<Course, char>getCoursesCompleted() const;

	bool isTuitionPaid() const;
	bool isCourseCompleted(const std::string& aPrefix, int aCourseNum) const;

	double calculateGPA() const;
	double billingAmount(double tuitionRate) const;

	void printStudent() const;
	void printStudentInfo(double tuitionRate) const;

	~Student() {};

private:
	int studentID;
	std::string firstName;
	std::string lastName;
	int numberOfCourses;
	bool tuitionWasPaid;
	std::multimap<Course, char>coursesCompleted;
};
#endif