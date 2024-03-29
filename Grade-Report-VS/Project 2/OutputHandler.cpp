/*
	Handles the output for Main.cpp
 	and creates the txt file for student information
*/

#include "OutputHandler.h"
#include "Course.h"
#include "Student.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

void printAllStudentsToFile(
	const StudentList& studentList, double tuitionRate)
{
	std::ofstream outfile;

	std::string nameOfFile;
	std::cout << "Enter a name for a new file to write on "
		<< "(include extension.txt) : \n";
	std::cin >> nameOfFile;

	outfile.open(nameOfFile);

	if (outfile.fail())
	{
		std::cerr << "Output file opening failed.\n";
	}
	else
	{
		outfile
			<< "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n"
			<< "            UNOFFICIAL TRANSCRIPTS\n"
			<< "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n\n";
		studentList.printStudentsToFile(outfile, tuitionRate);
	}
}
