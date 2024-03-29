/*
	Header file for StudnetList.cpp
*/

#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include "Student.h"

#include <string>
#include <iostream>
#include <fstream>

class Node
{
public:
	Node() : student(), next(nullptr) {}
	Node(const Student& theStudent, Node* newNext)
		: student(theStudent), next(newNext) {}
	Node* getNext() const { return next; }
	const Student& getStudent() const { return student; }
	void setStudent(const Student& theStudent) { student = theStudent; }
	void setNext(Node* newNext) { next = newNext; }
	~Node() {}
private:
	Student student;
	Node* next; 
};

class StudentList
{
public:
	StudentList() : first(nullptr), last(nullptr), count(0) {}
	StudentList(const StudentList& construct); 

	StudentList& operator=(const StudentList& assign); 

	void addStudent(const Student& newStudent);

	int getNoOfStudents() const;

	void printStudentByID(int id, double tuitionRate) const; 
	void printStudentByName(const std::string& lastName) const; 
	void printStudentsByCourse(const std::string& coursePrefix, 
		int courseNumber) const; 
	void printStudentsByGrade(const std::string& coursePrefix,
		int courseNumber, char grade) const;
	void printAllStudents(double tuitionRate) const; 
	void printStudentsOnHold(double tuitionRate) const;
	void printStudentsToFile(std::ofstream& outputFile,
		double tuitionRate) const;

	void clearStudentList();
	~StudentList();

private:
	void copyCallingObjShorter(const StudentList& shorter); 
	void copyCallingObjLonger(const StudentList& longer); 
	void copyObjectsSameLength(const StudentList& sameLength);
	void copyCallingObjIsEmpty(const StudentList& isEmpty); 

	Node* first;
	Node* last;
	int count;
};
#endif
