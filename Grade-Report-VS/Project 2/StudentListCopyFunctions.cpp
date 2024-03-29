/*
    Nguyen, An (Team Leader)
    Nguyen, Justin
    Chen, Shanqin
    Dang, Justin

    Project: Grade Report
    CS A250
    Fall 2023
*/

#include "StudentList.h" 

#include <iostream>

using namespace std; 

StudentList::StudentList(const StudentList& construct)
    : first(nullptr), last(nullptr), count(0)
{
    Node* current = construct.first;

    while (current != nullptr)
    {
        Student newStudent = current->getStudent();
        Node* newNode = new Node(newStudent, nullptr);

        if (first == nullptr)
        {
            first = newNode;
            last = newNode;
        }
        else
        {
            last->setNext(newNode);
            last = newNode;
        }

        count++;
        current = current->getNext();
    }
}

StudentList& StudentList::operator=(const StudentList& assign)
{
    if (this == &assign)
    {
        cerr << "Attempted assignment to itself.";
        return *this;
    }

    if (assign.first == nullptr)
    {
        clearStudentList();
    }
    else if (first == nullptr)
    {
        copyCallingObjIsEmpty(assign);
    }
    else if (count == assign.count)
    {
        copyObjectsSameLength(assign);
    }
    else if (count > assign.count)
    {
        copyCallingObjLonger(assign);
    }
    else
    {
        copyCallingObjShorter(assign);
    }
    
    return *this;
}

void StudentList::copyCallingObjIsEmpty(const StudentList& isEmpty)
{
    Node* current = isEmpty.first;

    while (current != nullptr)
    {
        Student newStudent = current->getStudent();
        Node* newNode = new Node(newStudent, nullptr);

        if (first == nullptr)
        {
            first = newNode;
            last = newNode;
        }
        else
        {
            last->setNext(newNode);
            last = newNode;
        }

        count++;
        current = current->getNext();
    }
}

void StudentList::copyObjectsSameLength(const StudentList& sameLength)
{
    Node* currentThis = first;
    Node* currentOther = sameLength.first;

    while (currentThis != nullptr && currentOther != nullptr)
    {
        currentThis->setStudent(currentOther->getStudent());

        currentThis = currentThis->getNext();
        currentOther = currentOther->getNext();
    }
}

void StudentList::copyCallingObjLonger(const StudentList& longer)
{
    first->setStudent(longer.first->getStudent());

    Node* currentOther = longer.first->getNext();
    Node* currentThis = first;

    while (currentOther != nullptr)
    {
        currentThis->getNext()->setStudent(currentOther->getStudent());
        currentOther = currentOther->getNext();
        currentThis = currentThis->getNext();
    } 

    Node* prevNode = currentThis;
    currentThis = currentThis->getNext();

    while (currentThis != nullptr)
    {
        prevNode->setNext(currentThis->getNext());
        delete currentThis;
        currentThis = prevNode->getNext();
    }

    last = prevNode;
    count = longer.count;
}

void StudentList::copyCallingObjShorter(const StudentList& shorter)
{
    Node* currentThis = first;
    Node* currentOther = shorter.first;
    Node* prevNode = nullptr;

    while (currentThis != nullptr && currentOther != nullptr)
    {
        currentThis->setStudent(currentOther->getStudent());
        prevNode = currentThis;
        currentThis = currentThis->getNext();
        currentOther = currentOther->getNext();
    }

    while (currentOther != nullptr)
    {
        Student newStudent = currentOther->getStudent();
        Node* newNode = new Node(newStudent, nullptr);

        if (prevNode == nullptr)
        {
            first = newNode;
        }
        else
        {
            prevNode->setNext(newNode);
        }

        prevNode = newNode;
        last = newNode;
        count++;

        currentOther = currentOther->getNext();
    }
}