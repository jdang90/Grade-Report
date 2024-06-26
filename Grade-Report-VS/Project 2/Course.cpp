/*
	Handles course methods
*/

#include "Course.h"

using namespace std;

void Course::setCourseInfo(const string& prefix, int num, int units)
{
	coursePrefix = prefix;
	courseNumber = num;
	courseUnits = units;
}

string Course::getCoursePrefix() const
{
	return coursePrefix;
}
int Course::getCourseNumber() const
{
	return courseNumber;
}
int Course::getCourseUnits() const
{
	return courseUnits;
}

bool Course::operator<(const Course& otherCourse) const
{
	return (coursePrefix < otherCourse.coursePrefix) 
		|| (coursePrefix == otherCourse.coursePrefix 
			&& courseNumber < otherCourse.courseNumber);
}
