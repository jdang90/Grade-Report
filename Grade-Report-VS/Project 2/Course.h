/*
	Header file for Course.cpp
*/

#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course
{
public:
	Course() : coursePrefix("N/A"), courseNumber(0), courseUnits(0) {}

	void setCourseInfo(const std::string& prefix, int num, int units);

	std::string getCoursePrefix() const;
	int getCourseNumber() const;
	int getCourseUnits() const;

	bool operator<(const Course& otherCourse) const;
	~Course() {};

private:
	std::string coursePrefix;
	int courseNumber;
	int courseUnits;
};
#endif
